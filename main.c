/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 14:19:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc == 1 && (argv || !argv))
	{
		(init_all_start(&shell), ft_signals()), (conf_env(&shell, envp));
		while (1)
		{
			init_all(&shell);
			shell.cwd = create_buffer(&shell);
			if (!shell.cwd)
				return (free_shell(&shell), 1);
			shell.line = readline(shell.cwd);
			if (!shell.line)
				break ;
			catchsignals(&shell);
			if (!check_empty_line(&shell))
				add_history(shell.line);
			if (!parsing(&shell))
				execute(&shell);
			loop_free_shell(&shell);
		}
		return (ft_putstr_fd("exit\n", 1), free_shell(&shell), 0);
	}
}

int	check_empty_line(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] != ' ' && shell->line[i] != '\t'
			&& shell->line[i] != '\r' && shell->line[i] != '\v'
			&& shell->line[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}

char	*create_buffer(t_shell *shell)
{
	char	*str;
	char	*buffer;

	buffer = NULL;
	buffer = ft_calloc(PATH_MAX, sizeof(char *));
	if (!buffer)
		return (malloc_error(shell), NULL);
	buffer = getcwd(buffer, PATH_MAX);
	str = ft_strjoin(buffer, "> ");
	if (!str)
		return (free(buffer), malloc_error(shell), NULL);
	free(buffer);
	return (str);
}

void	init_all_start(t_shell *shell)
{
	shell->excode = 0;
	shell->tmpexcode = 0;
	shell->switch_signal = 0;
	shell->env_head = NULL;
	shell->env_current = NULL;
	shell->cwd = NULL;
	shell->fds = NULL;
	shell->paths = NULL;
	shell->line = NULL;
	shell->f_head = NULL;
	shell->f_current = NULL;
	shell->s_head = NULL;
	shell->s_current = NULL;
	shell->env_tab = NULL;
	shell->g_sig = 0;
}

void	init_all(t_shell *shell)
{
	shell->i = 0;
	shell->unset = 0;
	shell->fds = NULL;
	shell->paths = NULL;
	shell->line = NULL;
	shell->cwd = NULL;
	shell->f_head = NULL;
	shell->f_current = NULL;
	shell->s_head = NULL;
	shell->s_current = NULL;
	shell->env_tab = NULL;
	shell->tmpexcode = 0;
}
