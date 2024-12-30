/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:06:04 by codespace         #+#    #+#             */
/*   Updated: 2024/12/19 01:40:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_newline(char **args, int *flag)
{
	int n = 1;
	while (args[n] && args[n][0] == '-' && args[n][1] == 'n')
	{
		int i = 1;
		while (args[n][i] == 'n')
			i++;
		if (args[n][i] != '\0')
			break;
		*flag = 1;
		n++;
	}
	return n;
}

void	bl_echo(t_shell *shell)
{
	int	i;
	int	flag;
	int	x;
	

	flag = 0;
	i = check_newline(shell->s_current->args, &flag);
	if (shell->s_current->args[1])
	{
		while (shell->s_current->args[i])
		{
			if (i > 1)
				ft_printf(" ");
			ft_printf("%s", shell->s_current->args[i++]);
		}
	}
	if (!flag)
		ft_printf("\n");
	if (shell->s_current->next)
		x = shell->excode;
	else
		x = shell->unset;
}

