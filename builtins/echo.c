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

int	check_newline(char **tab, int *flag)
{
	int	n;
	int	i;

	n = 1;
	while (tab[n] && tab[n][0] == '-' && tab[n][1] == 'n')
	{
		i = 1;
		if (tab[n][0] == '-' && tab[n][1] == 'n')
		{
			while (tab[n][i] == 'n')
				i++;
			if (tab[n][i] != '\0')
				return (n);
		}
		*flag = 1;
		n++;
	}
	return (n);
}

void	bl_echo(t_shell *shell)
{
	int	i;
	int	flag;
	int	ext;

	flag = 0;
	i = check_newline(shell->s_current->args, &flag);
	if (shell->s_current->args[1])
	{
		while (shell->s_current->args[i])
		{
			if (shell->s_current->args[i] && !shell->s_current->args[i + 1])
				printf("%s", shell->s_current->args[i++]);
			else if (shell->s_current->args[i])
				printf("%s ", shell->s_current->args[i++]);
		}
	}
	if (!flag)
		printf("\n");
	if (shell->s_current->next)
		ext = shell->excode;
	else
		ext = shell->unset;
	free_shell(shell);
	exit(ext);
}

