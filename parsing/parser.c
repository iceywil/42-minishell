/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:26 by a                 #+#    #+#             */
/*   Updated: 2024/10/24 18:54:58 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_shell *shell)
{
	check_open_quotes(shell, shell->line, 0);
	f_split_input(shell, shell->line);
	clean_empty_and_quotes(shell, shell->f_head);
	// clean_first(shell);
	s_parsing(shell);
	check_token_legit(shell);
	check_token_fill(shell);
	return (0);
}

void	check_token_legit(t_shell *shell)
{
	t_second	*current;
	t_second	*prev;

	current = shell->s_head;
	prev = NULL;
	while (current)
	{
		if (current->prev_token)
			ft_strcmp(current->prev_token)
				if (current->next_token)
	}
	return ;
}

void	check_token_fill(t_shell *shell)
{
	t_second	*current;
	t_second	*prev;

	current = shell->s_head;
	prev = NULL;
	while (current)
	{
		if (current->delim == NULL || current->cmd == NULL)
		{
			if (prev == NULL)
				printf("syntax error near unexpected token `newline'\n");
			else
				printf("syntax error near unexpected token `%s'\n",
					current->next_token);
		}
		prev = current;
		current = current->next;
	}
}
