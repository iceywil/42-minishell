/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:06:04 by codespace         #+#    #+#             */
/*   Updated: 2024/12/03 15:58:59 by marvin           ###   ########.fr       */
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

void bl_echo(void)
{
	int i;
	int flag = 0;
	char **args = g_shell.env;

	// Vérifier si des arguments sont fournis
	if (!args || !args[0])
	{
		ft_printf("\n");
		return;
	}
	i = check_newline(args, &flag);
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!flag)
		ft_printf("\n");
}

