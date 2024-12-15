/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:07:58 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 18:07:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void add_head(t_env_list **env, t_env_list *new_head)
{
	(*env) = new_head;
	(*env)->prev = *env;
	(*env)->next = *env;
}

static int new_element(t_env_list **env, char *new_element)
{
	(*env) = malloc(sizeof(t_env_list));
	if (*env == NULL)
		return (0);
	(*env)->key = new_element;
	(*env)->next = NULL;
	(*env)->prev = NULL;
	return (1);
}

size_t	env_size(t_env_list *env)
{
	size_t	size;
	t_env_list	*temp;

	size = 1;
	temp = env;
	if (env)
	{
		while (temp->next != env)
		{
			++size;
			temp = temp->next;
		}
		return (size);
	}
	return (0);
}

int add_back_env(t_env_list **env, char *new)
{
	t_env_list	*new_node;

	if (!new_element(&new_node, new))
		return (0);
	if (!(*env))
		add_head(env, new_node);
	else
	{
		new_node->prev = (*env)->prev;
		new_node->next = (*env);
		(*env)->prev->next = new_node;
		(*env)->prev = new_node;
	}
	return (1);
}
