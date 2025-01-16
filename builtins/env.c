/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 02:12:28 by codespace         #+#    #+#             */
/*   Updated: 2025/01/16 02:12:32 by codespace        ###   ########.fr       */
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

void	init_all(t_shell *shell)
{
	shell->i = 0;
	shell->unset = 0;
	shell->fds = NULL;
	shell->paths = NULL;
	shell->line = NULL;
	shell->cwd = NULL;
	shell->f_head = NULL;
	shell->f_current = NULL;
	shell->s_head = NULL;
	shell->s_current = NULL;
	shell->env_tab = NULL;
	shell->tmpexcode = 0;
	shell->last_pid = -1;
}
