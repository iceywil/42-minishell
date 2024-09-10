/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:20:19 by wscherre          #+#    #+#             */
/*   Updated: 2024/04/19 20:57:54 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	dup_fd(t_main *pipex, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error_exit(pipex, "Dup2 Error", errno);
}

void	create_own_pipes(t_main *pipex)
{
	if (pipe(pipex->fds[pipex->x]) == -1)
		error_exit(pipex, "Pipe Error", errno);
}

void	close_own_pipes(t_main *pipex)
{
	close(pipex->fds[pipex->x][0]);
	close(pipex->fds[pipex->x][1]);
}

void	close_last_pipes(t_main *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->args)
	{
		if (pipex->fds[pipex->x - 1][0] > 0)
			close(pipex->fds[pipex->x - 1][0]);
		if (pipex->fds[pipex->x - 1][1] > 0)
			close(pipex->fds[pipex->x - 1][1]);
		i++;
	}
}

void	wait_childrens(void)
{
	int	status;

	while (errno != ECHILD)
		waitpid(-1, &status, 0);
}

// int	i;
// int	status;
// i = 0;
/* 	if (waitpid(pipex->pids[pipex->args], &status, 0) < 0)
	{
		if (errno == ECHILD)
			return ;
		else
			perror("waitpid Error\n");
	} */
// return (code);
/* 	{
		if (errno == ECHILD)
			return ;
		e (i < pipex->cmds)
	{
		if (pipex->pids[i] == 0)
			i++;
		else if (waitpid(pipex->pids[i], &status, 0) < 0)
		{
			if (errno == ECHILD)
				i++;
			else
				perror("waitpid Error\n");
		}
	}  */

/* int wstatus;
		int i;

		i = 0;
		while (errno != ECHILD)
			wait(&wstatus); */

/* 	i = 0;
		while (i < pipex->args)
		{
			if (waitpid(pipex->pids[i], &status, 0) < 0)
			{
				if (errno == ECHILD)
					i++;
				else
					perror("waitpid Error\n");
			}
		} */

/* 			int status;
	int code;

	code = EXIT_FAILURE;
	while (errno != ECHILD)
	{
		if (wait(&status) == pid && WIFEXITED(status))
			code = WEXITSTATUS(status);
		if (errno == EACCES)
			return (126);
		if (pid == -1)
			return (127);
	} */