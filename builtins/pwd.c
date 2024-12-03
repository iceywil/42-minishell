/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:27:29 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 12:19:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void bl_pwd(void)
{
    char *pwd;

    // Vérifier les options invalides
    if (g_shell.builtin_path[1] && g_shell.builtin_path[1][0] == '-')
    {
        ft_putstr_fd("minishell: pwd: invalid option\n", 2);
        g_shell.excode = 2;
        return;
    }

    // Obtenir le répertoire de travail actuel
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories\n", 2);
        g_shell.excode = 1;
        return;
    }

    // Afficher le répertoire de travail actuel
    ft_putstr_fd(pwd, 1);
    ft_putstr_fd("\n", 1);

    // Libérer la mémoire
    free(pwd);
}
