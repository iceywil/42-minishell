/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 02:03:49 by codespace         #+#    #+#             */
/*   Updated: 2025/01/16 02:09:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*f_handle_env_cmd(t_shell *shell, char *line)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	shell->i = 0;
	while (line[shell->i])
	{
		if (line[shell->i] == '$' && !single_quote && ((double_quote
					&& (ft_isalnum(line[shell->i + 1]) || (line[shell->i
								+ 1] == '_' || line[shell->i + 1] == '?')))
				|| (!double_quote && (ft_isalnum(line[shell->i + 1])
						|| line[shell->i + 1] == '_' || line[shell->i
							+ 1] == '?' || line[shell->i + 1] == '"'
						|| line[shell->i + 1] == '\''))))
			line = f_set_shard(shell, line);
		else if (line[shell->i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[shell->i] == '"' && !single_quote)
			double_quote = !double_quote;
		shell->i++;
	}
	return (line);
}

char	*f_set_shard(t_shell *shell, char *line)
{
	int		start;
	char	*var_value;
	char	*new_line;

	start = shell->i;
	if (line[shell->i + 1] == '?')
		return (f_handle_err(shell, line, start));
	else
	{
		shell->x = 0;
		while (line[++shell->i])
		{
			if (ft_isdigit(line[shell->i]))
				shell->x = 1;
			if ((!ft_isalnum(line[shell->i]) && line[shell->i] != '_')
				|| (ft_isalpha(line[shell->i]) && shell->x == 1))
				break ;
		}
		shell->i--;
		var_value = f_find_var_value(shell, line + start + 1, shell->i - start);
	}
	new_line = f_replace_line(shell, line, var_value, start);
	free(line);
	return (new_line);
}

char	*f_handle_err(t_shell *shell, char *line, int start)
{
	char	*var_value;
	char	*new_line;

	var_value = ft_itoa(shell->excode);
	if (!var_value)
		malloc_error(shell);
	shell->i++;
	new_line = f_replace_line(shell, line, var_value, start);
	free(var_value);
	free(line);
	return (new_line);
}

char	*f_find_var_value(t_shell *shell, char *var_start, int var_len)
{
	t_env_list	*current;

	current = shell->env_head;
	while (current)
	{
		if (!ft_strncmp(current->key, var_start, var_len)
			&& current->key[var_len] == '=')
			return (current->key + var_len + 1);
		current = current->next;
	}
	return (NULL);
}

char	*f_replace_line(t_shell *shell, char *line, char *var_value, int start)
{
	char	*new_line;

	new_line = NULL;
	if (!var_value)
	{
		new_line = malloc(ft_strlen(line) - (shell->i - start + 1) + 1);
		if (!new_line)
			(free(var_value), free(line), malloc_error(shell));
		ft_strncpy(new_line, line, start);
		ft_strcpy(new_line + start, line + shell->i + 1);
		shell->i = start - 1;
	}
	else
	{
		new_line = malloc(ft_strlen(line) - (shell->i - start + 1)
				+ ft_strlen(var_value) + 1);
		if (!new_line)
			(free(var_value), free(line), malloc_error(shell));
		ft_strncpy(new_line, line, start);
		ft_strcpy(new_line + start, var_value);
		ft_strcpy(new_line + start + ft_strlen(var_value), line + shell->i + 1);
		shell->i = start + ft_strlen(var_value) - 1;
	}
	return (new_line);
}
