/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:52:22 by codespace         #+#    #+#             */
/*   Updated: 2025/01/02 18:59:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	export_no_args(t_shell *shell, t_env_list *env)
{
	char	**arr;
	int		i;
	int		j;

	arr = lst_to_arr(shell, env);
	if (!arr)
		return (false);
	sort_array(arr, env_size(shell));
	i = 0;
	while (arr[i])
	{
		ft_printf("declare -x ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			ft_printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			ft_printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			ft_printf("\n");
		i++;
	}
	free(arr);
	return (true);
}

static bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	export(t_shell *shell, char *str, t_env_list **env)
{
	char		*value;
	t_env_list	*current;

	value = ft_strdup(str);
	if (!value)
		return (false);
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, str, ft_strchr(str, '=') - str) == 0)
		{
			free(current->key);
			current->key = value;
			return (true);
		}
		current = current->next;
	}
	create_env_node(shell, value);
	return (true);
}

int	bl_export(t_shell *shell, char **str)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (shell->env_current && !export_no_args(shell, shell->env_current))
			malloc_error(shell);
		return (0);
	}
	while (str[i])
	{
		if (!valid_identifier(str[i]))
		{
			ft_putstr_fd("export: invalid identifier\n", 2);
			exit_code = 1;
		}
		else if (!export(shell, str[i], &shell->env_current))
			malloc_error(shell);
		i++;
	}
	return (exit_code);
}
