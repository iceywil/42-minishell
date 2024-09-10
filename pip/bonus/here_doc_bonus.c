/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:32 by wscherre          #+#    #+#             */
/*   Updated: 2024/04/24 15:22:44 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	here_doc(t_main *pipex, char **envp, char **argv)
{
	malloc_fds(pipex);
	malloc_pids(pipex);
	pipex->x = 0;
	doc_pipe(pipex, argv);
	first_cmd(pipex, envp, argv);
	if (pipex->filein != -1)
		close(pipex->filein);
	pipex->x++;
	while (pipex->x < pipex->argc - 5)
		(mid_cmd(pipex, envp), pipex->x++);
	last_cmd(pipex, envp, argv);
	wait_childrens();
	if (pipex->filein)
		close(pipex->filein);
	close_last_pipes(pipex);
	close_own_pipes(pipex);
}

void	doc_pipe(t_main *pipex, char **argv)
{
	char	*line;
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit(pipex, "Pipe Error", errno);
	pid = fork();
	if (pid == -1)
		error_exit(pipex, "Fork Error", errno);
	if (pid == 0)
	{
		(close(fd[0]), ft_printf("pipe heredoc> "), line = get_next_line(0));
		while (line)
		{
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
				break ;
			(ft_printf("pipe heredoc> "), ft_putstr_fd(line, fd[1]));
			(free(line), line = NULL, line = get_next_line(0));
		}
		if (line)
			free(line);
		(free_all(pipex), close(fd[0]), close(fd[1]), exit(0));
	}
	else
		(waitpid(pid, NULL, 0), close(fd[1]), pipex->filein = fd[0]);
}

/* void	doc_pipe(t_main *pipex, char **argv)
{
	char	*line;
	int		fd;

	fd = get_heredoc(pipex);
	ft_printf("pipe heredoc> ");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		(ft_printf("pipe heredoc> "), ft_putstr_fd(line, fd));
		(free(line), line = get_next_line(0));
	}
	free(line);
	close(fd);
} */

/* int	get_heredoc(t_main *pipex)
{
	int		fd;
	int		i;
	char	*file;

	i = 2;
	file = ft_calloc(i, sizeof(char));
	if (!file)
		error_exit(pipex, "Malloc Error", 1);
	ft_memset(file, 'a', i - 1);
	while (access(file, F_OK) == 0 && errno != ENOENT)
	{
		(free(file), file = ft_calloc(++i, sizeof(char)));
		if (!file)
			error_exit(pipex, "Malloc Error", 1);
		ft_memset(file, 'a', i - 1);
	}
	fd = -1;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	pipex->filein = -1;
	pipex->filein = open(file, O_RDONLY);
	(unlink(file), free(file));
	if (pipex->filein == -1 || fd == -1)
		error_exit(pipex, "Open Error", 1);
	return (fd);
} */
