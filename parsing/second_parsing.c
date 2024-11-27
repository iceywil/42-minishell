/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/11/27 21:51:02 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s_create_node(t_shell *shell, t_second *new_node)
{
	new_node = malloc(sizeof(t_second));
	if (!new_node)
		malloc_error(shell);
	new_node->prev = NULL;
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->next = NULL;
	new_node->args_head = NULL;
	new_node->args_current = NULL;
	new_node->redir_head = NULL;
	new_node->redir_current = NULL;
	new_node->cmd_path = NULL;
	new_node->heredoc = NULL;
	if (!shell->s_head)
	{
		new_node->i = 0;
		shell->s_head = new_node;
	}
	else
	{
		new_node->prev = shell->s_current;
		new_node->i = new_node->prev->i + 1;
		shell->s_current->next = new_node;
	}
	shell->s_current = new_node;
}

void	s_parsing(t_shell *shell)
{
	shell->f_current = shell->f_head;
	s_create_node(shell, NULL);
	while (shell->f_current)
	{
		if (shell->f_current->cmd)
		{
			if (shell->f_current->prev && !shell->f_current->prev->cmd
				&& ft_strcmp("|", shell->f_current->prev->line))
				s_add_redir(shell, shell->s_current);
			else if (!shell->s_current->cmd)
			{
				shell->s_current->cmd = ft_strdup(shell->f_current->line);
				if (!shell->s_current->cmd)
					malloc_error(shell);
			}
			else
				s_add_arg(shell, shell->s_current);
		}
		if (!shell->f_current->next || !ft_strcmp(shell->f_current->line, "|"))
			s_save_args(shell, shell->s_current);
		if (!ft_strcmp(shell->f_current->line, "|"))
			s_create_node(shell, NULL);
		shell->f_current = shell->f_current->next;
	}
}

void	s_add_redir(t_shell *shell, t_second *second)
{
	t_first	*new_node;

	new_node = malloc(sizeof(t_first));
	if (!new_node)
		malloc_error(shell);
	new_node->token = ft_strdup(shell->f_current->prev->line);
	if (!new_node->token)
		malloc_error(shell);
	new_node->line = ft_strdup(shell->f_current->line);
	if (!new_node->line)
		malloc_error(shell);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->outfile = 0;
	new_node->cmd = 0;
	if (!second->redir_head)
		second->redir_head = new_node;
	else
	{
		new_node->prev = second->redir_current;
		second->redir_current->next = new_node;
	}
	second->redir_current = new_node;
}

void	s_add_arg(t_shell *shell, t_second *second)
{
	t_first	*new_node;

	new_node = malloc(sizeof(t_first));
	if (!new_node)
		malloc_error(shell);
	new_node->line = ft_strdup(shell->f_current->line);
	if (!new_node->line)
		malloc_error(shell);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->cmd = 0;
	if (!second->args_head)
		second->args_head = new_node;
	else
	{
		new_node->prev = second->args_current;
		second->args_current->next = new_node;
	}
	second->args_current = new_node;
}

void	s_save_args(t_shell *shell, t_second *second)
{
	shell->i = 0;
	second->args_current = second->args_head;
	while (second->args_current)
	{
		second->args_current = second->args_current->next;
		shell->i++;
	}
	second->args = ft_calloc(shell->i + 2, sizeof(char *));
	if (!second->args)
		malloc_error(shell);
	second->args[0] = ft_strdup(second->cmd);
	if (!second->args[0])
		malloc_error(shell);
	second->args_current = second->args_head;
	shell->i = 1;
	while (second->args_current)
	{
		second->args[shell->i] = ft_strdup(second->args_current->line);
		if (!second->args[shell->i])
			malloc_error(shell);
		second->args_current = second->args_current->next;
		shell->i++;
	}
	second->args[shell->i] = NULL;
}
