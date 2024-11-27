/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:48:33 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 12:28:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int bl_check_exit(char *ag)
{
	int	i;
	long long	bn_exit;

	i = 0;
	while (ag[i] == ' ')
		i++;
	if (ag[i] && ((ag[i] == '-' || ag[i] == '+')))
		i++;
	while (ft_isdigit(ag[i]) == 0 || ft_isal(ag[i]) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", ag);
		g_shell.re_exit = 255;
		return (1);
	}
	bn_exit = ft_atol(ag);
	g_shell.re_exit = bn_exit % 256;
	if (g_shell.re_exit < 0 || g_shell.re_exit > 255)
		g_shell.re_exit = 255;
	return (0);
}

void	bl_exit(char **arg)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (arg[0])
	{
		i = bl_check_exit(arg[0]);
		if (arg[1] && i == 0)
		{
			printf("minishell: exit : too many arguments\n");
			g_shell.re_exit = 1;
			return ;
		}
	}
	exit(g_shell.re_exit);
}
