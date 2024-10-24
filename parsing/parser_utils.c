/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/24 03:10:59 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_open_quotes(t_shell *shell, char *input, int flag)
{
	int	i;
	int	single;
	int	doublee;

	single = 0;
	doublee = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"')
			doublee++;
		else if (input[i] == '\'')
			single++;
	}
	if (single % 2 != 0 || doublee % 2 != 0)
	{
		shell->excode = 2;
		print_err("syntax error quotes not closed", 0, 0, 0);
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
	t_first	*prev;
	t_first	*next;

	prev = NULL;
	while (current)
	{
		remove_side_quotes(current->line);
		if (current->line[0] == '\0')
		{
			next = current->next;
			free(current->line);
			free(current);
			if (prev)
				prev->next = next;
			else
				shell->f_head = next;
			current = next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	clean_first(t_shell *shell)
{
	t_first	*current;
	t_first	*next;

	current = shell->f_head;
	while (current)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
	shell->f_head = NULL;
	shell->f_current = NULL;
}
