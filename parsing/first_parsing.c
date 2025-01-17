/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:16:14 by codespace         #+#    #+#             */
/*   Updated: 2025/01/17 16:52:23 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	f_parse(t_shell *shell)
{
	int		inquotes;
	char	quote_char;
	int		start;

	shell->i = 0;
	inquotes = 0;
	quote_char = 0;
	start = -1;
	while (shell->line[shell->i])
	{
		if (start == -1 && !ft_isspace(shell->line[shell->i]))
			start = shell->i;
		f_quotes(shell, &inquotes, &quote_char);
		f_if(shell, &start, inquotes);
		shell->i++;
	}
}

void	f_quotes(t_shell *shell, int *inquotes, char *quote_char)
{
	int	quote;

	if (shell->line[shell->i] == '"' || shell->line[shell->i] == '\'')
	{
		if (*inquotes == 0)
		{
			*quote_char = shell->line[shell->i];
			quote = shell->i;
			while (shell->line[++quote])
			{
				if (shell->line[quote] == *quote_char)
					break ;
			}
			if (shell->line[quote] == '\0')
				*inquotes = 0;
			else
				*inquotes = 1;
		}
		else if (*inquotes == 1 && shell->line[shell->i] == *quote_char)
		{
			*inquotes = 0;
			*quote_char = 0;
		}
	}
}

void	f_if(t_shell *shell, int *start, int inquotes)
{
	if (ft_isspace(shell->line[shell->i]) && inquotes == 0 && *start != -1)
	{
		f_add_node(shell, ft_substr(shell->line, *start, shell->i - *start), 1);
		*start = -1;
	}
	else if (!is_token(shell->line[shell->i]) && is_token(shell->line[shell->i
				+ 1]) && inquotes == 0)
	{
		f_add_node(shell, ft_substr(shell->line, *start, shell->i - *start + 1),
			1);
		*start = -1;
	}
	else if (is_token(shell->line[shell->i]) && inquotes == 0)
	{
		shell->i = f_handle_token(shell, shell->line, shell->i);
		*start = -1;
	}
	else if (shell->line[shell->i + 1] == '\0' && *start != -1)
		f_add_node(shell, ft_substr(shell->line, *start, shell->i - *start + 1),
			1);
}

int	f_handle_token(t_shell *shell, char *input, int i)
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
	return (i - 1);
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
	new_node->line = content;
	new_node->prev = NULL;
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
