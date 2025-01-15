/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 17:34:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	if (c == PIPE || c == LEFT || c == RIGHT)
		return (1);
	return (0);
}

void	clean_empty_and_quotes(t_shell *shell, t_first *current)
{
	int i;

	i = 0;
	while (current)
	{
		if (!current->cmd)
		{
			while (current->line[i] && ft_isspace(current->line[i]))
			{
				ft_memmove(current->line, current->line + 1,
					ft_strlen(current->line));
				i++;
			}
		}
		remove_quotes(shell, current);
		current = current->next;
	}
}

void	remove_quotes(t_shell *shell, t_first *cur)
{
	char quote_char;
	int pos;

	shell->i = 0;
	pos = 0;
	quote_char = 0;
	while (cur->line[shell->i])
	{
		if ((cur->line[shell->i] == '\'' || cur->line[shell->i] == '\"'))
		{
			pos = shell->i;
			quote_char = cur->line[shell->i++];
			while (cur->line[shell->i] && cur->line[shell->i] != quote_char)
				shell->i++;
			if (cur->line[shell->i])
				remove_quotes_two(shell, cur, pos);
			else
				shell->i = pos + 1;
		}
		else
			shell->i++;
	}
}

void	remove_quotes_two(t_shell *shell, t_first *cur, int pos)
{
	ft_memmove(cur->line + pos, cur->line + pos + 1, ft_strlen(cur->line
			+ pos));
	ft_memmove(cur->line + shell->i - 1, cur->line + shell->i,
		ft_strlen(cur->line + shell->i - 1));
	shell->i = shell->i - pos - 1;
}
