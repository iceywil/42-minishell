/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/08 18:33:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_open_quotes(t_shell *shell, char *input)
{
	int	i;
	int	single;
	int	doublee;

	single = 0;
	doublee = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"' && doublee == 0 && single == 0)
			doublee = 1;
		else if (input[i] == '\"' && doublee == 1)
			doublee = 0;
		else if (input[i] == '\'' && single == 0 && doublee == 0)
			single = 1;
		else if (input[i] == '\'' && single == 1)
			single = 0;
	}
	if (single || doublee)
	{
		shell->excode = 2;
		ft_putstr_fd("minishell: syntax error quotes not closed\n", 2);
		return (1);
	}
	return (0);
}

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

void	clean_empty_and_quotes(t_shell *shell, t_first *current)
{
	t_first	*next_node;

	while (current)
	{
		remove_quotes(current->line);
		if (current->line[0] == '\0')
		{
			next_node = current->next;
			if (current != shell->f_head)
			{
				current->prev->next = current->next;
				if (current->next)
					current->next->prev = current->prev;
			}
			else
				shell->f_head = current->next;
			(free(current->line), free(current));
			current = next_node;
		}
		else
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
		if ((str[i] == '\'' || str[i] == '\"') && (!quote_char
				|| quote_char == str[i]))
		{
			if (!quote_char)
				quote_char = str[i];
			else if (str[i] == quote_char)
				quote_char = 0;
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

void	fix_quotes_space(t_shell *shell, t_first *current)
{
	while (current)
	{
		if (current != shell->f_head && current->prev)
		{
			shell->x = 0;
			while (current->prev->line[shell->x])
			{
				if (current->prev->line[shell->x] != ' '
					&& current->prev->line[shell->x] != '\''
					&& current->prev->line[shell->x] != '"')
				{
					shell->x = -1;
					break ;
				}
				shell->x++;
			}
			if (shell->x != -1)
				fix_current(shell, current);
		}
		current = current->next;
	}
}

void	fix_current(t_shell *shell, t_first *current)
{
	char	*tmp;

	tmp = malloc(ft_strlen(current->line) + 2);
	if (!current->line)
		malloc_error(shell);
	tmp[0] = ' ';
	(ft_strcpy(tmp + 1, current->line), free(current->line));
	current->line = tmp;
}
