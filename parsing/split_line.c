/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:08:15 by a                 #+#    #+#             */
/*   Updated: 2024/10/20 03:23:52 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_loop(char **result, char *cmd, int i, int x)
{
	int		start;
	char	quote_char;

	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		if (cmd[i])
		{
			start = i;
			quote_char = 0;
			while (cmd[i] && (quote_char || (cmd[i] != ' ' && cmd[i] != '\t')))
			{
				if ((cmd[i] == '\'' || cmd[i] == '\"') && !quote_char)
					quote_char = cmd[i];
				else if (cmd[i] == quote_char)
					quote_char = 0;
				i++;
			}
			result[x++] = ft_substr(cmd, start, i - start);
			if (!result[x - 1])
				return (ft_free_double_tab(&result), NULL);
		}
	}
	return (result);
}

void	split_line(t_shell *shell, t_command *current, char *line)
{
	int		count;
	char	**result;

	result = NULL;
	if (!line)
		return ;
	line = ft_strtrim(line, " \t");
	if (!line)
		return (free(line), malloc_error(shell));
	count = count_args(line);
	result = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!result)
		return (free(line), malloc_error(shell));
	if (!split_loop(result, line, 0, 0))
		return (free(line), malloc_error(shell));
	free(line);
	check_split(shell, current, result, count);
}

void	check_split(t_shell *shell, t_command *current, char **result,
		int count)
{
	if (!ft_strcmp(current->prev_token, "<<"))
	{
		current->args = (char **)ft_calloc(count - 1, sizeof(char *));
		if (!current->args)
			return (ft_free_double_tab(&result), malloc_error(shell));
		split_delim(shell, result);
	}
	else
	{
		current->args = (char **)ft_calloc(count, sizeof(char *));
		if (!current->args)
			return (ft_free_double_tab(&result), malloc_error(shell));
		split_normal(shell, result);
	}
	ft_free_double_tab(&result);
}

void	split_delim(t_shell *shell, char **result)
{
	int		i;

	i = 0;
	if (!result[0])
		return ;
	remove_quotes(result[0]);
	shell->current->delim = ft_strtrim(result[0], " \t");
	if (!shell->current->delim)
		return (ft_free_double_tab(&result), malloc_error(shell));
	if (!result[1])
		return ;
	remove_quotes(result[1]);
	shell->current->cmd = ft_strtrim(result[1], " \t");
	if (!shell->current->cmd)
		return (ft_free_double_tab(&result), malloc_error(shell));
	if (!result[2])
		return ;
	while (result[i + 2])
	{
		shell->current->args[i] = ft_strdup(result[i + 2]);
		if (!shell->current->args[i])
			return (ft_free_double_tab(&result), malloc_error(shell));
		i++;
	}
}

void	split_normal(t_shell *shell, char **result)
{
	int	i;

	i = 0;
	if (!result[0])
		return ;
	remove_quotes(result[0]);
	shell->current->cmd = ft_strtrim(result[0], " \t");
	if (!shell->current->cmd)
		return (ft_free_double_tab(&result), malloc_error(shell));
	if (!result[1])
		return ;
	while (result[i + 1])
	{
		shell->current->args[i] = ft_strdup(result[i + 1]);
		if (!shell->current->args[i])
			return (ft_free_double_tab(&result), malloc_error(shell));
		i++;
	}

}
