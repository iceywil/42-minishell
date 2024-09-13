/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/09/12 18:47:19 by codespace        ###   ########.fr       */
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
		check_exit(line, &shell);
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
	get_paths(&pipex, envp);
	(parse_args(&pipex, argv, argc, 3), parse_paths(&pipex));
	(here_doc(&pipex, envp, argv), free_all_exit(&pipex));
}
