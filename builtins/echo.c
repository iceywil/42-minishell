/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:54:14 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 00:52:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_newline(char **args, int *flag)
{
	int	n;
	int	i;

	n = 1;
	while (args[n] && args[n][0] == '-' && args[n][1] == 'n')
	{
		i = 1;
		while (args[n][i] == 'n')
			i++;
		if (args[n][i] != '\0')
			break ;
		*flag = 1;
		n++;
	}
	return (n);
}

void	bl_echo(t_shell *shell)
{
	int	i;
	int	flag;

	flag = 0;
	i = check_newline(shell->s_current->args, &flag);
	if (shell->s_current->args[1])
	{
		while (shell->s_current->args[i])
		{
			if (i > check_newline(shell->s_current->args, &flag))
				ft_printf(" ");
			ft_printf("%s", shell->s_current->args[i++]);
		}
	}
	if (!flag)
		ft_printf("\n");
}
