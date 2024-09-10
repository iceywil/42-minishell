/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:11:52 by wscherre          #+#    #+#             */
/*   Updated: 2024/04/24 15:30:34 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	pipex;

	pipex.cmd_paths = NULL;
	pipex.cmd_args = NULL;
	pipex.paths = NULL;
	pipex.fds = NULL;
	pipex.pids = NULL;
	if (argc > 4)
	{
		pipex.argc = argc;
		get_paths(&pipex, envp);
		if (argc > 5 && !ft_strncmp(argv[1], "here_doc", 8))
		{
			pipex.here = 1;
			(parse_args(&pipex, argv, argc, 3), parse_paths(&pipex));
			(here_doc(&pipex, envp, argv), free_all_exit(&pipex));
		}
		if (argc > 4 && ft_strncmp(argv[1], "here_doc", 8))
		{
			pipex.here = 0;
			(parse_args(&pipex, argv, argc, 2), parse_paths(&pipex));
			(exec(&pipex, envp, argv), free_all_exit(&pipex));
		}
	}
	error_exit(&pipex, "Need at least 4 arguments", 1);
}

void	exec(t_main *pipex, char **envp, char **argv)
{
	malloc_fds(pipex);
	malloc_pids(pipex);
	pipex->x = 0;
	first_cmd(pipex, envp, argv);
	pipex->x++;
	while (pipex->x < pipex->argc - 4)
		(mid_cmd(pipex, envp), pipex->x++);
	last_cmd(pipex, envp, argv);
	wait_childrens();
	close_last_pipes(pipex);
	close_own_pipes(pipex);
}

void	first_cmd(t_main *pipex, char **envp, char **argv)
{
	pid_t	pid;

	create_own_pipes(pipex);
	check_access(pipex);
	pid = fork();
	pipex->pids[pipex->x] = pid;
	if (pid == -1)
		error_exit(pipex, "Fork Error", errno);
	if (pid == 0)
	{
		if (!pipex->here)
			open_infile(pipex, argv);
		if (pipex->filein != -1)
		{
			dup_fd(pipex, pipex->filein, STDIN_FILENO);
			close(pipex->filein);
		}
		else
			(close_own_pipes(pipex), free_all_exit(pipex));
		dup_fd(pipex, pipex->fds[0][1], STDOUT_FILENO);
		close_own_pipes(pipex);
		exev(pipex, envp);
	}
	close(pipex->fds[0][1]);
}

void	mid_cmd(t_main *pipex, char **envp)
{
	pid_t	pid;

	create_own_pipes(pipex);
	check_access(pipex);
	pid = fork();
	pipex->pids[pipex->x] = pid;
	if (pid == -1)
		error_exit(pipex, "Fork Error", errno);
	if (pid == 0)
	{
		dup_fd(pipex, pipex->fds[pipex->x - 1][0], STDIN_FILENO);
		dup_fd(pipex, pipex->fds[pipex->x][1], STDOUT_FILENO);
		close_own_pipes(pipex);
		close_last_pipes(pipex);
		exev(pipex, envp);
	}
	close(pipex->fds[pipex->x][1]);
	close(pipex->fds[pipex->x - 1][0]);
}

void	last_cmd(t_main *pipex, char **envp, char **argv)
{
	pid_t	pid;

	create_own_pipes(pipex);
	check_access(pipex);
	check_outfile(pipex, argv);
	pid = fork();
	pipex->pids[pipex->x] = pid;
	if (pid == -1)
		error_exit(pipex, "Fork Error", errno);
	if (pid == 0)
	{
		if (pipex->here)
			open_outfile_here(pipex, argv);
		else
			open_outfile(pipex, argv);
		dup_fd(pipex, pipex->fds[pipex->x - 1][0], STDIN_FILENO);
		(close_own_pipes(pipex), close_last_pipes(pipex));
		if (pipex->fileout != -1)
		{
			dup_fd(pipex, pipex->fileout, STDOUT_FILENO);
			(close(pipex->fileout), exev(pipex, envp));
		}
	}
	close(pipex->fds[pipex->x - 1][0]);
}
