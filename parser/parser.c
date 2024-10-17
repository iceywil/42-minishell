/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:26 by a                 #+#    #+#             */
/*   Updated: 2024/10/17 22:02:05 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_shell *shell)
{
	if (check_open_quotes(shell, shell->line, 0))
		return (1);
	replace_quotes(shell->line);
	if (parse_input(shell, shell->line))
		return (1);
	return (0);
}

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
	}
	return (0);
}

void	replace_quotes(char *input)
{
	int		i;
	char	*result;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] != '\'')
			result[i] = ' ';
		i++;
	}
}

int	is_token(char c)
{
	if (c == PIPE || c == LEFT || c == RIGHT)
		return (1);
	return (0);
}


t_command	*create_node(t_shell *shell, t_command *current)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_command));
	if (!new_node)
		return (malloc_error(shell), 1);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->args = NULL;
	new_node->cmd = NULL;
	new_node->next_token = NULL;
	if (!shell->head)
		shell->head = new_node;
	else
	{
		new_node->prev = current;
		current->next = new_node;
	}
	current = new_node;
	if (current->prev && current->prev->next_token)
		new_node->prev_token = current->prev->next_token;
	return (current);
}

char	*get_cmd(t_shell *shell, char *input, char **cmd, int i)
{
	int	x;

	x = 0;
	if (!is_token(input[i]) && input[i] != ' ')
	{
		x = i;
		while (input[i] && !is_token(input[i]))
			i++;
		cmd = ft_substr(input, x, i - x);
		if (!cmd)
			return (malloc_error(shell), 1);
		cmd = split_cmd(cmd);
		if (!cmd)
			return (malloc_error(shell), 1);
	}
}

int	handle_tokens(t_shell *shell, char *input, int flag, int i)
{
	int	x;

	if (is_token(input[i]))
	{
		x = i;
		while (is_token(input[i]))
			i++;
		if (flag)
		{
			shell->current->next = ft_substr(input, x, i - x);
			if (!shell->current->next)
				return (malloc_error(shell), 1);
		}
		else
		{
			shell->current->prev = ft_substr(input, x, i - x);
			if (!shell->current->prev)
				return (malloc_error(shell), 1);
		}
	}
	return (0);
}

int	parse_input(t_shell *shell, char *input)
{
	t_command	*current;
	char		**args;
	int			arg_count;
	char		**args;
	int			index;
	char		*cmd;
	int			i;
	int			x;
	int			flag;

	i = 0;
	x = 0;
	flag = 0;
	// check first token
	while (input[i])
	{
		// handle spaces
		while (input[i] == ' ')
			i++;
		// handle flag
		if (!is_token(input[i]))
			flag = 1;
		current = create_node(shell, current);
		if (!current)
			return (1);
		cmd = get_cmd(shell, input, cmd, i);
		if (!cmd)
			return (1);
		handle_tokens(shell, input, current, i);
	}
}

