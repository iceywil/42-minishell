/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/24 17:28:42 by a                ###   ########.fr       */
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
	t_first		*tmp;
	t_second	*tmp2;
	int			i;
	int			node_count;

	i = 0;
	line = NULL;
	while (1)
	{
		shell.env = envp;
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
		tmp = shell.f_head;
		node_count = 0;
		while (tmp)
		{
			printf("Node %d:\n", node_count++);
			printf("  cmd: '%d'\n", tmp->cmd);
			printf("  line: '%s'\n", tmp->line);
			tmp = tmp->next;
		}
		tmp2 = shell.s_head;
		node_count = 0;
		i = 0;
		while (tmp2)
		{
			printf("Node %d:\n", node_count++);
			printf("  prev_token: '%s'\n", tmp2->prev_token);
			printf("  delim: '%s'\n", tmp2->delim);
			printf("  cmd: '%s'\n", tmp2->cmd);
			while (tmp2->args && tmp2->args[i])
			{
				printf("  args[%d]: '%s'\n", i, tmp2->args[i]);
				i++;
			}
			printf("  next_token: '%s'\n", tmp2->next_token);
			tmp2 = tmp2->next;
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
	shell->s_head = NULL;
	shell->s_current = NULL;
	shell->cwd = NULL;
	shell->f_head = NULL;
	shell->f_current = NULL;
}

void	pipex(t_shell *shell, int argc, char **argv, char **envp)
{
	get_paths(shell, envp);
	(parse_args(shell, argv, argc, 3), parse_paths(shell));
	(here_doc(shell, envp, argv), free_shell(shell));
}
