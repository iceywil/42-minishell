/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 02:02:33 by codespace         #+#    #+#             */
/*   Updated: 2025/01/16 02:02:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_fd(t_shell *shell, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error_exit(shell, "Dup2 Error", errno);
}

void	create_own_pipes(t_shell *shell)
{
	if (pipe(shell->fds[shell->i]) == -1)
		error_exit(shell, "Pipe Error", errno);
}

void	close_own_pipes(t_shell *shell)
{
	if (shell->fds[shell->i][0] != -1)
		close(shell->fds[shell->i][0]);
	if (shell->fds[shell->i][1] != 0)
		close(shell->fds[shell->i][1]);
}

void	close_last_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_nbr)
	{
		if (shell->fds[shell->i - 1][0] != -1)
			close(shell->fds[shell->i - 1][0]);
		if (shell->fds[shell->i - 1][1] != -1)
			close(shell->fds[shell->i - 1][1]);
		i++;
	}
}

void	wait_childrens(t_shell *shell)
{
	int		status;
	pid_t	pid;
	int		exit_code;

	status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				if (pid == shell->last_pid)
					shell->excode = exit_code;
			}
		}
		else if (pid == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				perror("waitpid");
		}
	}
}
