/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:25:08 by codespace         #+#    #+#             */
/*   Updated: 2024/11/27 13:03:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	nothin(int	signal)
{
	(void)signal;
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
	}
	else if (signal == SIGQUIT)
	{
		ft_printf("Quit: 3\n");
	}
}

