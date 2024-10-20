/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/20 02:59:08 by a                ###   ########.fr       */
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
	char		*line;
	t_shell		shell;
	t_command	*tmp;
	int			i;

	i = 0;
	line = NULL;
	while (1)
	{
		init_all(&shell);
		shell.cwd = create_buffer();
		if (!shell.cwd)
			return (free_shell(&shell), 1);
		line = readline(shell.cwd);
		if (!line)
			break ;
		shell.line = line;
		check_exit(&shell);
		if (!parsing(&shell))
			add_history(line);
		tmp = shell.head;
		while (tmp)
		{
			if (tmp->prev_token)
				printf("prev_token: '%s'\n", tmp->prev_token);
			if (tmp->delim)
				printf("delim: '%s'\n", tmp->delim);
			if (tmp->cmd)
				printf("cmd: '%s'\n", tmp->cmd);
			if (tmp->args)
			{
				i = 0;
				while (tmp->args[i])
					printf("args: '%s'\n", tmp->args[i++]);		
			}

			if (tmp->next_token)
				printf("next_token: '%s'\n", tmp->next_token);
			tmp = tmp->next;
		}
		if (line)
			free(line);
	}
	(ft_putstr_fd("exit\n", 1), free_shell(&shell));
	return (0);
}

void	init_all(t_shell *shell)
{
	shell->i = 0;
	shell->x = 0;
	shell->unset = 0;
	shell->err = 0;
	shell->fds = NULL;
	shell->pids = NULL;
	shell->here = 0;
	shell->filein = 0;
	shell->fileout = 0;
	shell->paths = NULL;
	shell->cmd_paths = NULL;
	shell->cmd_args = NULL;
	shell->excode = 0;
	shell->line = NULL;
	shell->head = NULL;
	shell->current = NULL;
	shell->cwd = NULL;
	shell->env = NULL;
}

void	pipex(t_shell *shell, int argc, char **argv, char **envp)
{
	get_paths(shell, envp);
	(parse_args(shell, argv, argc, 3), parse_paths(shell));
	(here_doc(shell, envp, argv), free_shell(shell));
}
