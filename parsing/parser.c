/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:26 by a                 #+#    #+#             */
/*   Updated: 2025/01/12 17:34:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_shell *shell)
{
	shell->line = f_handle_env_cmd(shell, shell->line);
	f_parsing(shell, shell->line);
	fix_quotes_space(shell, shell->f_head);
	clean_empty_and_quotes(shell->f_head);
	if (check_token_legit(shell, shell->f_head))
		return (1);
	s_parsing(shell);
	shell->s_current = shell->s_head;
	shell->cmd_nbr = 0;
	while (shell->s_current)
	{
		shell->cmd_nbr++;
		shell->s_current = shell->s_current->next;
	}
	return (0);
}

int	check_token_legit(t_shell *shell, t_first *current)
{
	while (current)
	{
		if ((!current->cmd && !ft_strcmp(current->line, "|")
				&& (current == shell->f_head || !current->next || (current->prev
						&& !current->prev->cmd))) || (!current->cmd
				&& ft_strcmp(current->line, "|") && (current->prev
					&& !current->prev->cmd && ft_strcmp(current->prev->line,
						"|"))))
		{
			printf("minishell : syntax error near unexpected token `%s'\n",
				current->line);
			shell->excode = 2;
			return (1);
		}
		else if (!current->next && !current->cmd)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			shell->excode = 2;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	s_set_arg_zero(t_shell *shell, t_second *second)
{
	int	i;
	int	start;

	i = 0;
	start = -1;
	if (second->cmd[0] == '/')
	{
		while (second->cmd[i])
		{
			if (second->cmd[i] == '/')
				start = i + 1;
			i++;
		}
		second->args[0] = ft_strdup(second->cmd + start);
	}
	else
		second->args[0] = ft_strdup(second->cmd);
	if (!second->args[0])
		malloc_error(shell);
}

void	fix_quotes_space(t_shell *shell, t_first *current)
{
	while (current)
	{
		if (current != shell->f_head && current->prev)
		{
			shell->x = 0;
			shell->i = 0;
			while (current->prev->line[shell->x])
			{
				if (current->prev->line[shell->x] == '\''
					|| current->prev->line[shell->x] == '"')
					shell->i = -1;
				if (current->prev->line[shell->x] != ' '
					&& current->prev->line[shell->x] != '\''
					&& current->prev->line[shell->x] != '"')
				{
					shell->x = -1;
					break ;
				}
				shell->x++;
			}
			if (shell->x != -1 && shell->i == -1)
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
