/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 16:58:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	if (c == PIPE || c == LEFT || c == RIGHT)
		return (1);
	return (0);
}

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

void	clean_empty_and_quotes(t_first *current)
{
	int		i;

	i = 0;
	while (current)
	{
		if(!current->cmd)
		{
			while(current->line[i] == ' ' || current->line[i] == '\t')
			{
				ft_memmove(current->line, current->line + 1, ft_strlen(current->line));
				i++;
			}
		}
		remove_quotes(current->line);
		current = current->next;
	}
}

void	remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote_char;

	i = 0;
	j = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (!quote_char)
				quote_char = str[i];
			else if (str[i] == quote_char)
				quote_char = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	if (quote_char)
		str[j++] = quote_char;
	str[j] = '\0';
}

void	handle_quotes(char input, int *in_quotes,
		char *quote_char)
{
	if (!*in_quotes)
	{
		*in_quotes = 1;
		*quote_char = input;
	}
	else if (input == *quote_char)
	{
		*in_quotes = 0;
		*quote_char = 0;
	}
}
