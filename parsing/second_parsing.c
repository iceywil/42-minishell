/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/24 18:36:55 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_side_quotes(char *str)
{
	int		len;
	char	quote_type;

	if (!str || !*str)
		return ;
	len = ft_strlen(str);
	if (len < 2)
		return ;
	quote_type = '\0';
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len
			- 1] == '\"'))
	{
		quote_type = str[0];
	}
	if (quote_type)
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
}

t_second	*s_create_node(t_shell *shell)
{
	t_second	*new_node;

	new_node = malloc(sizeof(t_second));
	if (!new_node)
		malloc_error(shell);
	new_node->prev_token = NULL;
	new_node->prev = NULL;
	new_node->delim = NULL;
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->next = NULL;
	new_node->next_token = NULL;
	if (!shell->s_head)
		shell->s_head = new_node;
	else
	{
		new_node->prev = shell->s_current;
		shell->s_current->next = new_node;
	}
	shell->s_current = new_node;
	if (shell->s_current->prev && shell->s_current->prev->next_token)
		new_node->prev_token = shell->s_current->prev->next_token;
	return (new_node);
}

void	s_parsing(t_shell *shell)
{
	t_second	*second;
	char		*line;

	shell->f_current = shell->f_head;
	second = s_create_node(shell);
	while (shell->f_current)
	{
		line = ft_strdup(shell->f_current->line);
		if (!line)
			return (malloc_error(shell));
		if (shell->f_current->cmd)
		{
			if (!second->delim && !ft_strcmp(second->prev_token, "<<"))
				second->delim = line;
			else if (!second->cmd)
				second->cmd = line;
			else
				s_args_loop(shell);
		}
		else
			s_parsing_token(shell, second, line);
		if (shell->f_current)
			shell->f_current = shell->f_current->next;
	}
}

void	s_parsing_token(t_shell *shell, t_second *second, char *line)
{
	if (!second->cmd && !second->prev_token)
		second->prev_token = line;
	else
	{
		second->next_token = line;
		second->next = s_create_node(shell);
		second = second->next;
	}
}

void	s_args_loop(t_shell *shell)
{
	t_first	*current;
	char	**args;
	int		count;
	int		i;

	current = shell->f_current;
	count = 0;
	while (current && current->cmd)
		(current = current->next, count++);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		malloc_error(shell);
	i = 0;
	while (shell->f_current && shell->f_current->cmd)
	{
		args[i] = ft_strdup(shell->f_current->line);
		if (!args[i])
			(ft_free_double_tab(&args), malloc_error(shell));
		shell->f_current = shell->f_current->next;
		i++;
	}
	args[i] = NULL;
	shell->s_current->args = args;
}

