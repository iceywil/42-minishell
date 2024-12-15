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

    char *path_value = getenv("PATH");
    if (path_value)
    {
        shell->paths = ft_split(path_value, ':');
        if (!shell->paths)
            return (free_list(&envp));
    }
    else
    {
        shell->paths = NULL;
    }

    return (1);
}\

//ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAACAQDEhooDn7YggxfWCGguYx/h4AMKXh8vhRy8VrT6b2wMZCIVb74yovXVTgLpL/KI669bJ4NFq1isPUB7Ip904Ld7A1bfT1zYGxR+lfX0EtwaFbtdxO6Yosm5fuPI99Nehre2zYtK78pFxGWFUVwyoaBCPZ6Cd8x2pKy7u4SI7+vGDnbTcyYlfRRnY9+dVwVQhkh14wviCh8TYl0B6uPHYxLbRz3ELhJy+Zvv+P4iJYVbsf0UwyYWTOHU4dtAs4KIJSK4f8L+FnsAVrG8kP2RNZfsVb/KCRO6dAJfXjz28jhO85oRasVEyYWBqT0gPqaN4WTSbr0URqpiLEz+6cmzcJAuRebPLaiUBc//SVPAw6qLTQCm4W7y5bFw1Fvkmp0afWoSIwD1u9uKztsdr/TUzhxQrV2kmu6g2g6WnEKndZSCX87zX6+d65YhoEfykdtiAMo9TJxjACr7Ac7zLG50jUWWc/Lmiav2len3J4Hm8QOJzPKCt3ov1bdRGAR4P1nyDwEmkLxCvlxYT7xj5/emKGHszVYEbjNyorbnAhp42Ot7GSNuR8uhGzs6N+smv9aUVqqEICH9I+2BiMLypY4c+pq/ba9yZ8EQLaQEzWa2+HMJA3/YiBa94623dQBL2al8hDxTDGC6/uibK9gTedcBlE4txoHFCRpceogsZKrjwa0IcQ== sachamorin65@gmail.com