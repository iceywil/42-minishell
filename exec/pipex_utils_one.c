/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:35:26 by codespace         #+#    #+#             */
/*   Updated: 2024/11/07 18:09:26 by a                ###   ########.fr       */
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
	if (pipe(shell->fds[shell->x]) == -1)
		error_exit(shell, "Pipe Error", errno);
}

void	close_own_pipes(t_shell *shell)
{
	close(shell->fds[shell->x][0]);
	close(shell->fds[shell->x][1]);
}

void	close_last_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	/* while (i < shell->args)
	{
		if (shell->fds[shell->x - 1][0] > 0)
			close(shell->fds[shell->x - 1][0]);
		if (shell->fds[shell->x - 1][1] > 0)
			close(shell->fds[shell->x - 1][1]);
		i++;
	} */
}

void	wait_childrens(void)
{
	int	status;

	while (errno != ECHILD)
		waitpid(-1, &status, 0);
}

