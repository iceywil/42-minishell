/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:32:32 by marvin            #+#    #+#             */
/*   Updated: 2024/11/29 12:32:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_checkdir()
{
    DIR *dir;
	dir = opendir(g_shell.builtin_path[1]);
    if (!dir)
    {
        ft_putstr_fd("minishell: cd: %s: ", 2);
		ft_putstr_fd(g_shell.builtin_path[1], 2);
        perror(NULL);
        g_shell.excode = 1;
        return 0;
    }
    closedir(dir);
    return 1;
}