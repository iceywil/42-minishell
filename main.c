/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 15:13:05 by codespace        ###   ########.fr       */
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
		pipex(&shell, argc, argv, envp);
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

void	pipex(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->cmd_paths = NULL;
	shell->cmd_args = NULL;
	shell->paths = NULL;
	shell->fds = NULL;
	shell->pids = NULL;
	shell->argc = argc;
	get_paths(shell, envp);
	(parse_args(shell, argv, argc, 3), parse_paths(shell));
	(here_doc(shell, envp, argv), free_shell(shell));
}
