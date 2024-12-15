/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/12/15 21:25:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.excode = 0;
	shell.switch_signal = 0;
	set_signal_action();
	while (1)
	{
		init_all(&shell);
		if (!conf_env(&shell, envp))
			return (free_shell(&shell), 1);
		shell.cwd = create_buffer();
		if (!shell.cwd)
			return (free_shell(&shell), 1);
		shell.line = readline(shell.cwd);
		if (!shell.line)
			break ;
		check_exit(&shell);
		if (!check_empty_line(&shell) && !parsing(&shell))
			execute(&shell);
		add_history(shell.line);
		if (shell.line)
			(free(shell.line), shell.line = NULL);
		free_shell(&shell);
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
	shell->s_current = shell->s_head;
	if (shell->cmd_nbr == 1)
		one_command(shell, shell->env);
	else
		exec(shell);
}

void	init_all(t_shell *shell)
{
	shell->i = 0;
	shell->env = NULL;
	shell->unset = 0;
	shell->fds = NULL;
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
