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

void	suppr_space(char *str)
{
    char *start;
    char *end;
    int i;

    start = str;
    i = 0;
    while (start[i] && (start[i] == ' ' || start[i] == '\t'))
        i++;
    end = start + ft_strlen(start) - 1;
    while (end > start && (end[i] == ' ' || end[i] == '\t'))
        end--;
    *(end + 1) = '\0';
    if (start != str)
    {
        while (start[i])
            str[i] = start[i];
        str[i] = '\0';
    }
}

t_env_list	*new_env(char *key, char *value, t_shell *shell)
{
    t_env_list *new;

    new = ft_calloc(sizeof(t_env_list), 1);
    if (!new)
        return (NULL);
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    if (!new->key || !new->value)
    {
        free(new->key);
        free(new->value);
        free(new);
        return (NULL);
    }
    return (new);
}

void add_or_update_env(t_env_list **env, const char *key, const char *value, t_shell *shell)
{
    t_env_list *current = *env;
    t_env_list *new_node;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            if (!current->value)
            {
                free_shell(shell);
                return;
            }
            return;
        }
        current = current->next;
    }
    new_node = new_env((char *)key, (char *)value, shell);
    if (!new_node)
    {
        free_shell(shell);
        return;
    }

    new_node->next = *env;
    *env = new_node;
}

