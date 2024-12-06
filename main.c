/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/12/06 22:08:49 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell g_shell;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	while (1)
	{
		init_all(&shell);
		copy_env(&shell, envp);
		shell.cwd = create_buffer();
		if (!shell.cwd)
			return (free_shell(&shell), 1);
		shell.line = readline(shell.cwd);
		if (!shell.line)
			break ;
		check_exit(&shell);
		if (!parsing(&shell))
		{
			add_history(shell.line);
			//
			tmp = shell.f_head;
			node_count = 0;
			while (tmp)
			{
				// printf("Node %d:\n", node_count++);
				// printf("  cmd: '%d'\n", tmp->cmd);
				// printf("  line: '%s'\n", tmp->line);
				tmp = tmp->next;
			}
			tmp2 = shell.s_head;
			node_count = 0;
			i = 0;
			while (tmp2)
			{
				// printf("Node %d:\n", node_count++);
				// printf("  cmd: '%s'\n", tmp2->cmd);
				tmp2->redir_current = tmp2->redir_head;
				while (tmp2->redir_current)
				{
					printf("  redir : '%s' '%s'\n", tmp2->redir_current->token,
						tmp2->redir_current->line);
					tmp2->redir_current = tmp2->redir_current->next;
				}
				while (tmp2->args && tmp2->args[i])
				{
					// printf("  args[%d]: '%s'\n", i, tmp2->args[i]);
					i++;
				}
				tmp2 = tmp2->next;
			}
			execute(&shell);
			tmp2 = shell.s_head;
			node_count = 0;
			while (tmp2)
			{
				// printf("Node %d:\n", node_count++);
				// printf("  cmd: '%s'\n", tmp2->cmd);
				// printf("  path: '%s'\n", tmp2->cmd_path);
				tmp2 = tmp2->next;
			}
		}
		if (!check_empty_line(&shell) && !parsing(&shell))
			execute(&shell);
		add_history(shell.line);
		if (shell.line)
			(free(shell.line), shell.line = NULL);
	}
	(ft_putstr_fd("exit\n", 1), free_shell(&shell));
	return (0);
}

int	check_empty_line(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

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

void	execute(t_shell *shell)
{
	get_paths(shell);
	parse_paths(shell);
	handle_heredoc(shell, shell->s_head);
	if (shell->cmd_nbr == 1)
		one_command(shell, shell->env);
	else
		exec(shell);
}

void	init_all(t_shell *shell)
{
	shell->i = 0;
	shell->x = 0;
	shell->env = NULL;
	shell->unset = 0;
	shell->err = 0;
	shell->fds = NULL;
	shell->pids = NULL;
	shell->paths = NULL;
	shell->excode = 0;
	shell->line = NULL;
	shell->s_head = NULL;
	shell->s_current = NULL;
	shell->cwd = NULL;
	shell->f_head = NULL;
	shell->f_current = NULL;
}

void	copy_env(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	if (!envp || !envp[0])
		return ;
	while (envp[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		malloc_error(shell);
	shell->env[i] = NULL;
	i = 0;
	while (envp[i])
	{
		shell->env[i] = NULL;
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			malloc_error(shell);
		i++;
	}
}
