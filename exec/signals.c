/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:00:43 by a                 #+#    #+#             */
/*   Updated: 2024/12/16 16:09:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	g_shell;

/* void	ctrl_c(int var)
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
	exit(130);
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
	//ft_free_tab(shell->env);
	//ft_free_tab(shell->env_export);
	rl_clear_history();
	exit(0);
} */
void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		return ;
	// printf("\nIntercepted SIGINT!\n");
}

void	set_signal_action(void)
{
	struct sigaction	act;

	// Déclaration de la structure sigaction
	// Met à 0 tous les bits dans la structure,
	// sinon on aura de mauvaises surprises de valeurs
	// non-initialisées...
	ft_bzero(&act, sizeof(act));
	// On voudrait invoquer la routine sigint_handler
	// quand on reçoit le signal :
	act.sa_handler = &sigint_handler;
	// Applique cette structure avec la fonction à invoquer
	// au signal SIGINT (ctrl-c)
	sigaction(SIGINT, &act, NULL);
}
