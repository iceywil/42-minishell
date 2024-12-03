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

static void	check_args(void)
{
    if (!ft_is_numeric(g_shell.builtin_path[0]))
    {
        g_shell.excode = 255;
        ft_printf("exit\n");
        ft_printf(NUMERIC_M);
        exit(g_shell.excode);
    }
    else if (g_shell.builtin_path[1])
    {
        g_shell.excode = 1;
        ft_printf(EXIT_M);
        exit(g_shell.excode);
    }
    else
    {
        ft_printf("exit\n");
        g_shell.excode = ft_atoi(g_shell.builtin_path[0]);
        exit(g_shell.excode);
    }
}

void	bl_exit()
{
    if (g_shell.builtin_path[0])
        check_args();
    else
    {
        ft_printf("exit\n");
        g_shell.excode = g_shell.excode % 256;
        exit(g_shell.excode);
    }
    free_shell(&g_shell);
}
