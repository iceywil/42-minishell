/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:53:46 by codespace         #+#    #+#             */
/*   Updated: 2025/01/02 18:53:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bl_env(t_shell *shell)
{
	t_env_list	*temp;

	temp = shell->env_head;
	while (temp)
	{
		if (ft_strchr(temp->key, '='))
			ft_printf("%s\n", temp->key);
		temp = temp->next;
	}
	return (0);
}

void	copy_env(t_shell *shell)
{
	t_env_list	*current;
	int			len;
	int			i;

	len = env_size(shell);
	current = shell->env_head;
	shell->env_tab = ft_calloc(len + 1, sizeof(char *));
	if (!shell->env_tab)
		return (malloc_error(shell));
	current = shell->env_head;
	i = 0;
	while (current)
	{
		shell->env_tab[i] = ft_strdup(current->key);
		if (!shell->env_tab[i])
			return (malloc_error(shell));
		i++;
		current = current->next;
	}
	shell->env_tab[i] = NULL;
}
