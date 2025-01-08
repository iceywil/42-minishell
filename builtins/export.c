/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:52:22 by codespace         #+#    #+#             */
/*   Updated: 2025/01/08 19:04:28 by codespace        ###   ########.fr       */
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
	sort_array(arr);
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

void	export(t_shell *shell, char *str)
{
	char		*value;
	t_env_list	*current;
	t_env_list	*last;

	value = ft_strdup(str);
	if (!value)
		malloc_error(shell);
	current = shell->env_head;
	while (current)
	{
		last = current;
		if (ft_strncmp(current->key, str, ft_strchr(str, '=') - str) == 0)
		{
			free(current->key);
			current->key = value;
			return ;
		}
		current = current->next;
	}
	last->next = create_env_node(shell, value);
}

int	bl_export(t_shell *shell, char **str)
{
	int	i;

	i = 1;
	if (!str || !str[i])
	{
		if (shell->env_head && !export_no_args(shell, shell->env_head))
			malloc_error(shell);
		return (0);
	}
	while (str[i])
	{
		if (!valid_identifier(str[i]))
		{
			(ft_putstr_fd("export: `", 2), ft_putstr_fd(str[i], 2),
				ft_putendl_fd("': not a valid identifier", 2));
			return (1);
		}
		else
			export(shell, str[i]);
		i++;
	}
	return (0);
}
