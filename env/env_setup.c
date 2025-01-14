/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:49:35 by codespace         #+#    #+#             */
/*   Updated: 2025/01/13 02:57:58 by codespace        ###   ########.fr       */
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
	while (envp[i] && ft_strncmp(envp[i], "OLDPWD=", 7))
		i++;
	if (envp[i])
	{
		tmp = ft_strdup(envp[i]);
		if (!tmp)
			malloc_error(shell);
		add_back_env(shell, tmp);
	}
	if (!getcwd(path, PATH_MAX))
		error_exit(shell, "getcwd error", 1);
	tmp = ft_strjoin("PWD=", path);
	add_back_env(shell, tmp);
}

void	conf_env(t_shell *shell, char **envp)
{
	char	*tmp;
	char	path[PATH_MAX];

	shell->x = 0;
	if (!envp || !envp[0])
	{
		if (!getcwd(path, PATH_MAX))
			error_exit(shell, "getcwd error", 1);
		tmp = ft_strjoin("PWD=", path);
		add_back_env(shell, tmp);
		return ;
	}
	while (envp[shell->x])
	{
		tmp = ft_strdup(envp[shell->x++]);
		if (!tmp)
			malloc_error(shell);
		add_back_env(shell, tmp);
	}
	conf_second_env(shell, envp);
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
