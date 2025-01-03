/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:49:35 by codespace         #+#    #+#             */
/*   Updated: 2025/01/03 00:22:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_list	*create_env_node(t_shell *shell, char *new)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		malloc_error(shell);
	new_node->key = new;
	new_node->next = NULL;
	return (new_node);
}

void	conf_second_env(t_shell *shell, char **envp)
{
	char	path[PATH_MAX];
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "OLDPWD=", 7))
		i++;
	if (envp[i])
	{
		tmp = ft_strdup(envp[i]);
		if (!tmp)
			malloc_error(shell);
		shell->env_current->next = create_env_node(shell, tmp);
		shell->env_current = shell->env_current->next;
	}
	if (!getcwd(path, PATH_MAX))
		error_exit(shell, "getcwd error", 1);
	tmp = NULL;
	tmp = ft_strjoin("PWD=", path);
	if (!tmp)
		malloc_error(shell);
	shell->env_current->next = create_env_node(shell, tmp);
}

int	conf_env(t_shell *shell, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strdup(envp[i]);
		if (!tmp)
			malloc_error(shell);
		if (shell->env_head == NULL)
		{
			shell->env_head = create_env_node(shell, tmp);
			shell->env_current = shell->env_head;
		}
		else
		{
			shell->env_current->next = create_env_node(shell, tmp);
			shell->env_current = shell->env_current->next;
		}
		i++;
	}
	conf_second_env(shell, envp);
	return (1);
}

int	env_size(t_shell *shell)
{
	int			size;
	t_env_list	*current;

	current = shell->env_head;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void	add_back_env(t_shell *shell, char *value)
{
	t_env_list	*new_node;

	new_node = create_env_node(shell, value);
	shell->env_current = shell->env_head;
	if (!shell->env_current)
	{
		shell->env_head = new_node;
		return ;
	}
	while (shell->env_current->next)
		shell->env_current = shell->env_current->next;
	shell->env_current->next = new_node;
}
