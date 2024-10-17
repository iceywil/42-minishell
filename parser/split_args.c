/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:08:15 by a                 #+#    #+#             */
/*   Updated: 2024/10/17 20:09:22 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char *cmd)
{
	char	quote_char;
	int		count;
	int		i;

	count = 0;
	i = 0;
	quote_char = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		if (cmd[i])
		{
			count++;
			while (cmd[i] && (quote_char || (cmd[i] != ' ' && cmd[i] != '\t')))
			{
				if ((cmd[i] == '\'' || cmd[i] == '\"') && !quote_char)
					quote_char = cmd[i];
				else if (cmd[i] == quote_char)
					quote_char = 0;
				i++;
			}
		}
	}
	return (count);
}

char	**split_loop(char **result, char *cmd, int i, int count)
{
	int		start;
	char	quote_char;

	i = 0;
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
			if (result[count])
				printf("start: %p \n", result[count]);
			result[count++] = ft_substr(cmd, start, i - start);
			if (!result[count - 1])
				return (NULL);
		}
	}
	return (result);
}

char	**split_cmd(char *cmd)
{
	char	**result;
	int		count;

	if (!cmd)
		return (NULL);
	cmd = ft_strtrim(cmd, " \t");
	if (!cmd)
		return (NULL);
	count = count_args(cmd);
	result = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (!split_loop(result, cmd, 0, count))
		return (ft_free_double_tab(result), free(cmd), NULL);
	free(cmd);
	return (result);
}
