/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:12:09 by codespace         #+#    #+#             */
/*   Updated: 2024/11/27 22:59:23 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int update_env(t_shell *shell, const char *key, const char *value, int append)
{
    for (int i = 0; shell->env[i]; i++)
    {
        char *env_key = strtok(shell->env[i], "=");
        if (strcmp(env_key, key) == 0)
        {
            char *new_value;
            if (append)
            {
                new_value = malloc(strlen(shell->env[i]) + strlen(value) + 1);
                if (!new_value)
                    return -1;
                sprintf(new_value, "%s%s", shell->env[i], value);
            }
            else
            {
                new_value = malloc(strlen(key) + strlen(value) + 2);
                if (!new_value)
                    return -1;
                sprintf(new_value, "%s=%s", key, value);
            }
            free(shell->env[i]);
            shell->env[i] = new_value;
            return 0;
        }
    }
    return -1;
}

static int add_env(t_shell *shell, const char *key, const char *value)
{
    int i;
    for (i = 0; shell->env[i]; i++);
    char **new_env = realloc(shell->env, sizeof(char *) * (i + 2));
    if (!new_env)
        return -1;
    shell->env = new_env;
    shell->env[i] = malloc(strlen(key) + strlen(value) + 2);
    if (!shell->env[i])
        return -1;
    sprintf(shell->env[i], "%s=%s", key, value);
    shell->env[i + 1] = NULL;
    return 0;
}

void ft_export(t_shell *shell, t_second *cmd)
{
    if (!cmd->args[1])
    {
        ft_printf("export: not enough arguments\n");
        shell->excode = 1;
        return;
    }

    for (int i = 1; cmd->args[i]; i++)
    {
        char *arg = cmd->args[i];
        char *equal_sign = strchr(arg, '=');
        int append = 0;

        if (equal_sign && equal_sign > arg && *(equal_sign - 1) == '+')
        {
            append = 1;
            *(equal_sign - 1) = '\0';
        }

        if (equal_sign)
        {
            *equal_sign = '\0';
            const char *key = arg;
            const char *value = equal_sign + 1;

            if (update_env(shell, key, value, append) == -1)
            {
                if (add_env(shell, key, value) == -1)
                {
                    perror("export");
                    shell->excode = 1;
                    return;
                }
            }
        }
        else
        {
            ft_printf("export: `%s': not a valid identifier\n", arg);
            shell->excode = 1;
        }
    }
    shell->excode = 0;
}