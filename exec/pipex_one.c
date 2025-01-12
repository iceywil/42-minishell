/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:29:59 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 17:07:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_command(t_shell *shell, char **envp)
{
	pid_t	pid;

	(check_access(shell), check_files(shell));
	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (handle_redirs(shell))
			return (close_own_pipes(shell), free_shell(shell), exit(1));
		if (shell->s_current->infile != -1)
		{
			dup_fd(shell, shell->s_current->infile, STDIN_FILENO);
			close(shell->s_current->infile);
		}
		if (shell->s_current->outfile != -1)
		{
			dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO);
			close(shell->s_current->outfile);
		}
		(builtin_cmd(shell), exev(shell, envp));
	}
	wait_childrens(shell);
}

void	exec(t_shell *shell)
{
	malloc_fds(shell);
	shell->i = 0;
	first_cmd(shell, shell->env_tab);
	shell->i++;
	shell->s_current = shell->s_current->next;
	while (shell->i != shell->cmd_nbr - 1)
	{
		mid_cmd(shell, shell->env_tab);
		shell->i++;
		shell->s_current = shell->s_current->next;
	}
	last_cmd(shell, shell->env_tab);
	wait_childrens(shell);
	close_last_pipes(shell);
	close_own_pipes(shell);
}

void	first_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	(create_own_pipes(shell), check_access(shell), check_files(shell));
	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (handle_redirs(shell))
			return (close_own_pipes(shell), free_shell(shell), exit(1));
		if (shell->s_current->infile != -1)
		{
			dup_fd(shell, shell->s_current->infile, STDIN_FILENO);
			close(shell->s_current->infile);
		}
		if (shell->s_current->outfile != -1)
		{
			dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO);
			close(shell->s_current->outfile);
		}
		else
			dup_fd(shell, shell->fds[shell->i][1], STDOUT_FILENO);
		(close_own_pipes(shell), builtin_cmd(shell), exev(shell, envp));
	}
	close(shell->fds[0][1]);
}

void	mid_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	(create_own_pipes(shell), check_access(shell), check_files(shell));
	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (handle_redirs(shell))
			return (close_own_pipes(shell), close_last_pipes(shell),
				free_shell(shell), exit(1));
		if (shell->s_current->infile != -1)
			(dup_fd(shell, shell->s_current->infile, STDIN_FILENO),
				close(shell->s_current->infile));
		else
			dup_fd(shell, shell->fds[shell->i - 1][0], STDIN_FILENO);
		if (shell->s_current->outfile != -1)
			(dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO),
				close(shell->s_current->outfile));
		else
			dup_fd(shell, shell->fds[shell->i][1], STDOUT_FILENO);
		(close_own_pipes(shell), close_last_pipes(shell));
		(builtin_cmd(shell), exev(shell, envp));
	}
	(close(shell->fds[shell->i][1]), close(shell->fds[shell->i - 1][0]));
}

void	last_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	(create_own_pipes(shell), check_access(shell), check_files(shell));
	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (handle_redirs(shell))
			return (close_own_pipes(shell), close_last_pipes(shell),
				free_shell(shell), exit(1));
		if (shell->s_current->infile != -1)
			(dup_fd(shell, shell->s_current->infile, STDIN_FILENO),
				close(shell->s_current->infile));
		else
			dup_fd(shell, shell->fds[shell->i - 1][0], STDIN_FILENO);
		if (shell->s_current->outfile != -1)
		{
			dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO);
			close(shell->s_current->outfile);
		}
		(close_own_pipes(shell), close_last_pipes(shell));
		(builtin_cmd(shell), exev(shell, envp));
	}
	(close(shell->fds[shell->i][1]), close(shell->fds[shell->i - 1][0]));
}
