/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/10 17:41:48 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_buffer(void)
{
	char	*buffer;
	char	*str;

	buffer = ft_calloc(PATH_MAX, sizeof(char *));
	buffer = getcwd(buffer, PATH_MAX);
	str = ft_strjoin(buffer, "> ");
	if (!buffer)
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
		shell.cwd = NULL;
		shell.cwd = create_buffer();
		if (!shell.cwd)
			return (free_shell(&shell), 1);
		line = readline(shell.cwd);
		if (!line)
			break ;
		shell.line = line;
		check_exit(&shell);
		if (!parsing(&shell))
			// pipex(&shell, argc, argv, envp);
			add_history(line);
		if (line)
			free(line);
	}
	(ft_putstr_fd("exit\n", 1), free_shell(&shell));
	return (0);
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
