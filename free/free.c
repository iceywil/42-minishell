/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:10:56 by codespace         #+#    #+#             */
/*   Updated: 2024/12/18 03:54:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_shell(t_shell *shell)
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
	if (shell->cwd)
		free(shell->cwd);
	if (shell->env_head)
		free_list(shell);
	if (shell->env_tab)
		ft_free_double_tab(&shell->env_tab);
}

void	check_exit(t_shell *shell)
{
	if (ft_strncmp(shell->line, "exit", 4) == 0)
	{
		shell->excode = 0;
		free_shell(shell);
		exit(0);
	}
}

void	error_exit(t_shell *shell, char *msg, int error)
{
	ft_putendl_fd(msg, 2);
	free_shell(shell);
	exit(error);
}

void	malloc_error(t_shell *shell)
{
	ft_putendl_fd("Malloc error", 2);
	free_shell(shell);
	exit(1);
}

void	print_err(char *word, char *msg, char redir, int flag)
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
	t_first	*current;
	t_first	*next;

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
	t_second	*current;
	t_second	*next;

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
