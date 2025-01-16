/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/10 14:10:56 by codespace         #+#    #+#             */
/*   Updated: 2025/01/13 03:43:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	loop_free_shell(t_shell *shell)
{
	if (shell->paths)
		ft_free_double_tab(&shell->paths);
	if (shell->fds)
	{
		shell->i = 0;
		while (shell->fds[shell->i])
			free(shell->fds[shell->i++]);
		free(shell->fds);
	}
	if (shell->line)
		free(shell->line);
	if (shell->f_head)
		free_first(shell->f_head);
	if (shell->s_head)
		free_second(shell);
	if (shell->env_tab)
		ft_free_double_tab(&shell->env_tab);
	if (shell->fd2 != -1)
		close(shell->fd2);
}

void	free_shell(t_shell *shell)
{
	loop_free_shell(shell);
	if (shell->env_head)
		free_list(shell);
	if (shell->fd0 != -1)
		close(shell->fd0);
}

void	print_err(char *word, char *msg, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(word, 2);
		ft_putendl_fd(msg, 2);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(msg, 2);
	}
}

void	free_first(t_first *head)
{
	t_first *current;
	t_first *next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		if (current->line)
			free(current->line);
		free(current);
		current = next;
	}
}

void	free_second(t_shell *shell)
{
	t_second *current;
	t_second *next;

	current = shell->s_head;
	while (current)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->cmd_path)
			free(current->cmd_path);
		if (current->args)
			ft_free_double_tab(&current->args);
		if (current->args_head)
			free_first(current->args_head);
		if (current->redir_head)
			free_first(current->redir_head);
		if (current->heredoc)
			free(current->heredoc);
		free(current);
		current = next;
	}
	shell->s_head = NULL;
}
