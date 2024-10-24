/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/24 16:34:48 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	f_split_input(t_shell *shell, char *input)
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
	int	token_start;

	if (is_token(input[i]))
	{
		if (i > start)
			f_add_node(shell, ft_substr(input, start, i - start), 1);
		token_start = i;
		while (input[i] && is_token(input[i]))
			i++;
		f_add_node(shell, ft_substr(input, token_start, i - token_start), 0);
		return (i);
	}
	else if (input[i] == ' ')
	{
		if (i > start)
			f_add_node(shell, ft_substr(input, start, i - start), 1);
		return (i + 1);
	}
	return (i);
}

void	f_add_node(t_shell *shell, char *content, int cmd)
{
	t_first	*new_node;

	new_node = malloc(sizeof(t_first));
	if (!new_node)
		(free(content), malloc_error(shell));
	new_node->cmd = cmd;
	new_node->line = f_handle_env_cmd(shell, content);
	new_node->next = NULL;
	if (!shell->f_head)
	{
		shell->f_head = new_node;
		shell->f_current = new_node;
	}
	else
	{
		shell->f_current->next = new_node;
		shell->f_current = new_node;
	}
}

char	*f_handle_env_cmd(t_shell *shell, char *line)
{
	char	*dollar_pos;
	char	*var_start;
	char	*var_end;
	char	*var_name;
	char	*env_value;
	char	*new_line;
	size_t	var_len;
	size_t	prefix_len;
	size_t	suffix_len;
	int		i;

	i = 0;
	if (!line || !*line || line[0] == '\'' || line[ft_strlen(line) - 1] == '\'')
		return (line);
	dollar_pos = ft_strchr(line, '$');
	if (!dollar_pos)
		return (line);
	var_start = dollar_pos + 1;
	var_end = var_start;
	while (*var_end && *var_end != ' ' && *var_end != '\'' && *var_end != '\"')
		var_end++;
	var_len = var_end - var_start;
	if (var_len == 0)
		return (line);
	var_name = strndup(var_start, var_len);
	if (!var_name)
		return (NULL);
	env_value = NULL;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var_name, var_len)
			&& shell->env[i][var_len] == '=')
		{
			env_value = shell->env[i] + var_len + 1;
			break ;
		}
		i++;
	}
	free(var_name);
	if (!env_value)
		return (line);
	prefix_len = dollar_pos - line;
	suffix_len = ft_strlen(var_end);
	new_line = malloc(prefix_len + ft_strlen(env_value) + suffix_len + 1);
	if (!new_line)
		return (NULL);
	ft_strncpy(new_line, line, prefix_len);
	ft_strcpy(new_line + prefix_len, env_value);
	ft_strcpy(new_line + prefix_len + ft_strlen(env_value), var_end);
	free(line);
	return (new_line);
}
