/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:59:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 13:29:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool conf_second_env(t_shell *shell)
{
    char *temps;
    char path[PATH_MAX];

    temps = ft_strdup("OLDPWD");
    if (!temps)
        return (0);
    temps = ft_strjoin("PWD", path);
    if (!temps)
        return (0);
    free(temps);
    return (1);
}

int conf_env(t_shell *shell, char **env)
{
    t_env_list *envp;
    int i;
    char *temps;

    if (!(*env))
        return (conf_second_env(shell));
    i = -1;
    envp = NULL;
    while (env[++i])
    {
        temps = ft_strdup(env[i]);
        if (!temps)
            return (free_list(&envp));
        if (!add_back_env(&envp, temps))
            return (free_list(&envp));
    }
    shell->env_head = envp;
    return (1);
}