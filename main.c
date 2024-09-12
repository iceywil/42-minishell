/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/09/12 12:59:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_buffer(void)
{
	char	*buffer;
	char	*str;

	buffer = ft_calloc(PATH_MAX, sizeof(char *));
	buffer = getcwd(buffer, PATH_MAX);
	str = ft_strjoin(buffer, "> ");
	free(buffer);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	line = NULL;
	while (1)
	{
		shell.cwd = create_buffer();
		line = readline(shell.cwd);
		if (!line)
			break ;
		parsing();
		exec(argc, argv, envp);
		add_history(line);
		if (line)
			free(line);
	}
	(ft_putstr_fd("exit\n", 1), free_shell(&shell));
	return (0);
}

void	parsing(void)
{
	// parsing
	return ;
}

void	exec(int argc, char **argv, char **envp)
{
	t_main	pipex;

	pipex.cmd_paths = NULL;
	pipex.cmd_args = NULL;
	pipex.paths = NULL;
	pipex.fds = NULL;
	pipex.pids = NULL;
	pipex.argc = argc;
	// get_paths(&pipex, envp);
	envp = envp;
	//(parse_args(&pipex, argv, argc, 3), parse_paths(&pipex));
	//(here_doc(&pipex, envp, argv), free_all_exit(&pipex));
	doc_pipe(&pipex, argv);
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
		(close(fd[0]), ft_printf("minishell> "), line = get_next_line(0));
		while (line)
		{
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
				break ;
			(ft_printf("minishell> "), ft_putstr_fd(line, fd[1]));
			(free(line), line = NULL, line = get_next_line(0));
		}
		if (line)
			free(line);
		(free_all(pipex), close(fd[0]), close(fd[1]), exit(0));
	}
	else
		(waitpid(pid, NULL, 0), close(fd[1]), pipex->filein = fd[0]);
}
