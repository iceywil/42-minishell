/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:50:57 by codespace         #+#    #+#             */
/*   Updated: 2025/01/02 18:50:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	remove_env_var(t_shell *shell, char *var)
{
	t_env_list	*current;
	t_env_list	*prev;
	int			var_len;

	var_len = ft_strlen(var);
	current = shell->env_head;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, var, var_len) == 0
			&& (current->key[var_len] == '=' || current->key[var_len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env_head = current->next;
			free(current->key);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	bl_unset(t_shell *shell, char **args)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = 1;
		}
		else
			remove_env_var(shell, args[i]);
		i++;
	}
	return (exit_code);
}
