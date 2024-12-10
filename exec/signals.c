/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:00:43 by a                 #+#    #+#             */
/*   Updated: 2024/12/11 01:26:44 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int var)
{
	(void) var;
	if (g_shell.switch_signal == 0)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_shell.switch_signal == 0)
		rl_redisplay();
}

void	nothing(int signal)
{
	(void)signal;
}

void	stop_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(131);
}

void	newline(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell.excode = 130;
}

void	ctrl_d(char *line)
{
	free(line);
	//free (shell->user);
	//ft_free_double_tab(shell->env);
	//ft_free_double_tab(shell->env_export);
	rl_clear_history();
	exit(0);
}