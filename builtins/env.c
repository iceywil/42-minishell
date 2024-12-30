/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:57:22 by codespace         #+#    #+#             */
/*   Updated: 2024/11/27 23:00:00 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int bl_env(t_shell *shell)
{
    t_env_list *temp;

    temp = shell->env_head;
    while (temp)
    {
        if (ft_strchr(temp->key, '='))
            ft_printf("%s\n", temp->key);
        temp = temp->next;
    }
    return (0);
}
