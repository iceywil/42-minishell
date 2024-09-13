/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:44:23 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 13:43:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_shell *shell, char **envp, char **argv)
{
	malloc_fds(shell);
	malloc_pids(shell);
	shell->x = 0;
	first_cmd(shell, envp, argv);
	shell->x++;
	while (shell->x < shell->argc - 4)
		(mid_cmd(shell, envp), shell->x++);
	last_cmd(shell, envp, argv);
	wait_childrens();
	close_last_pipes(shell);
	close_own_pipes(shell);
}

void	first_cmd(t_shell *shell, char **envp, char **argv)
{
	pid_t	pid;

	create_own_pipes(shell);
	check_access(shell);
	pid = fork();
	shell->pids[shell->x] = pid;
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (!shell->here)
			open_infile(shell, argv);
		if (shell->filein != -1)
		{
			dup_fd(shell, shell->filein, STDIN_FILENO);
			close(shell->filein);
		}
		else
			(close_own_pipes(shell), free_shell(shell));
		dup_fd(shell, shell->fds[0][1], STDOUT_FILENO);
		close_own_pipes(shell);
		exev(shell, envp);
	}
	close(shell->fds[0][1]);
}

void	mid_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	create_own_pipes(shell);
	check_access(shell);
	pid = fork();
	shell->pids[shell->x] = pid;
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		dup_fd(shell, shell->fds[shell->x - 1][0], STDIN_FILENO);
		dup_fd(shell, shell->fds[shell->x][1], STDOUT_FILENO);
		close_own_pipes(shell);
		close_last_pipes(shell);
		exev(shell, envp);
	}
	close(shell->fds[shell->x][1]);
	close(shell->fds[shell->x - 1][0]);
}

void	last_cmd(t_shell *shell, char **envp, char **argv)
{
	pid_t	pid;

	create_own_pipes(shell);
	check_access(shell);
	check_outfile(shell, argv);
	pid = fork();
	shell->pids[shell->x] = pid;
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (shell->here)
			open_outfile_here(shell, argv);
		else
			open_outfile(shell, argv);
		dup_fd(shell, shell->fds[shell->x - 1][0], STDIN_FILENO);
		(close_own_pipes(shell), close_last_pipes(shell));
		if (shell->fileout != -1)
		{
			dup_fd(shell, shell->fileout, STDOUT_FILENO);
			(close(shell->fileout), exev(shell, envp));
		}
	}
	close(shell->fds[shell->x - 1][0]);
}
