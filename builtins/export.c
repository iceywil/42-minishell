/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:07:20 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 18:07:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_valid_identifier(const char *str)
{
    if (!str || !*str)
        return false;
    if (!ft_isalpha(*str) && *str != '_')
        return false;
    for (const char *s = str + 1; *s; ++s)
    {
        if (!ft_isalnum(*s) && *s != '_')
            return false;
    }
    return true;
}

void handle_id(t_env_list *env, char *arg, t_shell *shell)
{
    char *equal_sign;

    suppr_space(arg);
    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
    {
        *equal_sign = '\0';
        suppr_space(arg);
        suppr_space(equal_sign + 1);
        if (is_valid_identifier(arg))
            add_or_update_env(&env, arg, equal_sign + 1, shell);
        else
            ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
    }
    else
    {
        if (is_valid_identifier(arg))
            add_or_update_env(&env, arg, "", shell);
        else
            ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
    }
}

bool export_args(t_env_list *env, char *arg, char *next_arg, t_shell *shell)
{
    char *equal_sign;
    char *joined_arg = NULL;
    bool skip_next = false;

    suppr_space(arg);
    if (arg && arg[ft_strlen(arg) - 1] == '=' && next_arg)
    {
        joined_arg = ft_strjoin(arg, next_arg);
        if (!joined_arg)
            return (ft_putstr_fd("Error: malloc\n", STDERR_FILENO), false);
        arg = joined_arg;
        skip_next = true;
    }
    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
    {
        *equal_sign = '\0';
        handle_id(env, arg, shell);
        *equal_sign = '=';
    }
    else
        handle_id(env, arg, shell);
    free(joined_arg);
    return skip_next;
}

void bl_export(t_shell *shell)
{
    bool skip;
    int i;

    if (!shell->s_current->args[1])
        return;

    i = 1;
    while (shell->s_current->args[i])
    {
        skip = export_args(shell->env_head, shell->s_current->args[i], shell->s_current->args[i + 1], shell);
        if (skip)
            i++;
        i++;
    }
}