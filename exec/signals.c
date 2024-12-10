/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:00:43 by a                 #+#    #+#             */
/*   Updated: 2024/12/11 00:30:12 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(t_shell *shell, int var)
{
	(void) var;
	if (shell->switch_signal == 0)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (shell->switch_signal == 0)
		rl_redisplay();
}

void	nothing(t_shell *shell, int signal)
{
	(void)signal;
}

void	stop_heredoc(t_shell *shell, int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(130);
}

void	newline(t_shell *shell, int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	shell->excode = 130;
}

void	ctrl_d(t_shell *shell, char *line)
{
	free(line);
	//free (shell->user);
	ft_free_tab(shell->env);
	//ft_free_tab(shell->env_export);
	rl_clear_history();
	exit(0);
}