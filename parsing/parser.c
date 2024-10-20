/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:26 by a                 #+#    #+#             */
/*   Updated: 2024/10/20 03:24:12 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_shell *shell)
{
	if (check_open_quotes(shell, shell->line, 0))
		return (1);
	parse_input(shell, shell->line);
	return (0);
}

void	parse_input(t_shell *shell, char *input)
{
	shell->i = 0;
	while (input[shell->i])
	{
		create_node(shell);
		get_line(shell, input);
		handle_tokens(shell, input);
	}

}

void	create_node(t_shell *shell)
{
	t_command	*new_node;

	if (shell->current && !shell->current->cmd && shell->current->prev_token)
		return ;
	new_node = malloc(sizeof(t_command));
	if (!new_node)
		return (malloc_error(shell));
	new_node->prev_token = NULL;
	new_node->prev = NULL;
	new_node->delim = NULL;
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->next = NULL;
	new_node->next_token = NULL;
	if (!shell->head)
		shell->head = new_node;
	else
	{
		new_node->prev = shell->current;
		shell->current->next = new_node;
	}
	shell->current = new_node;
	if (shell->current->prev && shell->current->prev->next_token)
		new_node->prev_token = shell->current->prev->next_token;
}

void	get_line(t_shell *shell, char *input)
{
	int		x;
	char	*line;

	line = NULL;
	x = shell->i;
	while (input[x] && !is_token(input[x]))
	{
		if (input[x] != ' ')
		{
			x = shell->i;
			while (input[shell->i] && !is_token(input[shell->i]))
				shell->i++;
			line = ft_substr(input, x, shell->i - x);
			if (!line)
				return (malloc_error(shell));
			split_line(shell, shell->current, line);
			return ;
		}
		x++;
	}

}

void	handle_tokens(t_shell *shell, char *input)
{
	int	x;

	while (input[shell->i] && input[shell->i] == ' ')
		shell->i++;
	if (is_token(input[shell->i]))
	{
		x = shell->i;
		while (is_token(input[shell->i]))
			shell->i++;
		if (shell->current->cmd)
		{
			shell->current->next_token = ft_substr(input, x, shell->i - x);
			if (!shell->current->next_token)
				return (malloc_error(shell));
		}
		else
		{
			shell->current->prev_token = ft_substr(input, x, shell->i - x);
			if (!shell->current->prev_token)
				return (malloc_error(shell));
		}
	}			


}
