/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:26 by a                 #+#    #+#             */
/*   Updated: 2024/12/10 23:58:07 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_shell *shell)
{
	if (check_open_quotes(shell, shell->line, 0))
		return (1);
	f_parsing(shell, shell->line);

	clean_empty_and_quotes(shell, shell->f_head);

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
					&& !current->prev->cmd)))
		{
			printf("minishell : syntax error near unexpected token `%s'\n",
				current->line);
			return (1);
		}
		else if (!current->next && !current->cmd)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
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
