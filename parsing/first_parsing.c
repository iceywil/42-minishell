/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/11/10 23:53:35 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	f_parsing(t_shell *shell, char *input)
{
	int	i;
	int	start;
	int	new_start;

	i = 0;
	start = 0;
	f_split_loop(shell, "", 0, 0);
	while (input[i])
	{
		new_start = f_split_loop(shell, input, start, i);
		if (new_start > i)
		{
			i = new_start;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		f_add_node(shell, ft_substr(input, start, i - start), 1);
}

int	f_split_loop(t_shell *shell, char *input, int start, int i)
{
	static int	in_quotes = 0;
	static char	quote_char = 0;

	if (input[i] == '"' || input[i] == '\'')
	{
		if (!in_quotes)
		{
			in_quotes = 1;
			quote_char = input[i];
		}
		else if (input[i] == quote_char)
		{
			in_quotes = 0;
			quote_char = 0;
		}
	}
	else if (!in_quotes)
		return (f_no_quotes(shell, input, start, i));
	return (i);
}

int	f_no_quotes(t_shell *shell, char *input, int start, int i)
{
	char	current_token;
	char	prev_token;

	if (is_token(input[i]))
	{
		if (i > start)
			f_add_node(shell, ft_substr(input, start, i - start), 1);
		return (f_handle_token(shell, input, start, i));
	}
	else if (input[i] == ' ')
	{
		if (i > start)
			f_add_node(shell, ft_substr(input, start, i - start), 1);
		return (i + 1);
	}
	return (i);
}

int	f_handle_token(t_shell *shell, char *input, int start, int i)
{
	int		token_start;
	int		token_count;
	char	prev_token;

	token_start = i;
	token_count = 0;
	prev_token = input[i];
	while (input[i] && is_token(input[i]))
	{
		if (input[i] != prev_token || ((prev_token == '>' || prev_token == '<')
				&& token_count == 2) || (prev_token == '|' && token_count == 1))
		{
			f_add_node(shell, ft_substr(input, token_start, token_count), 0);
			token_start = i;
			token_count = 0;
		}
		prev_token = input[i];
		token_count++;
		i++;
	}
	if (token_count > 0)
		f_add_node(shell, ft_substr(input, token_start, token_count), 0);
	return (i);
}

void	f_add_node(t_shell *shell, char *content, int cmd)
{
	t_first	*new_node;

	if (!content)
		malloc_error(shell);
	new_node = malloc(sizeof(t_first));
	if (!new_node)
		(free(content), malloc_error(shell));
	new_node->cmd = cmd;
	new_node->line = f_handle_env_cmd(shell, content);
	new_node->prev = shell->f_current;
	new_node->next = NULL;
	new_node->token = NULL;
	if (!shell->f_head)
		shell->f_head = new_node;
	else
	{
		new_node->prev = shell->f_current;
		shell->f_current->next = new_node;
	}
	shell->f_current = new_node;
}
