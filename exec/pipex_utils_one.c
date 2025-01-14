/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:35:26 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 19:37:46 by codespace        ###   ########.fr       */
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
	int	status;
	int	tmp;

	status = 0;
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			if (errno == ECHILD && WIFEXITED(status))
			{
				tmp = WEXITSTATUS(status);
				if (tmp != 0)
					shell->excode = tmp;
				break ;
			}
		}
	}
}
