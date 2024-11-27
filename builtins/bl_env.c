/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:17:03 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 12:18:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bl_env(void)
{
	int	i;
	t_shell	*shell;
	
	i = 0;
	while (shell->env[i])
		printf("%s\n", shell->env[i++]);
	return (0);
}
