/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:07:20 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 18:07:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_to_arr(t_env_list *env)
{
	t_env_list	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (env_size(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->key);
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = (lst->key);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static void	ft_swap_str_tab(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	sort_array(char **arr, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);
			if (diff > 0)
			{
				ft_swap_str_tab(i, j, arr);
				continue ;
			}
			j++;
		}
	i++;
	}
}

static bool	export_no_args(t_env_list *env)
{
	char	**arr;
	int		i;
	int		j;

	arr = lst_to_arr(env);
	if (!arr)
		return (false);
	sort_array(arr, env_size(env));
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

static int	exist(char *str, t_env_list *env)
{
	int		i;
	int		j;
	t_env_list	*tmp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	tmp = env;
	if (!ft_strncmp(tmp->key, str, i) && (tmp->key[i] == '\0' || \
		tmp->key[i] == '='))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != env)
	{
		if (!ft_strncmp(tmp->key, str, i) && (tmp->key[i] == '\0' || \
			tmp->key[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

bool	export(char *str, t_env_list **env)
{
	int		pos;
	int		i;
	char	*value;

	pos = exist(str, (*env));
	value = ft_strdup(str);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		i = 0;
		while (i < pos)
		{
			(*env) = (*env)->next;
			i++;
		}
		free((*env)->key);
		(*env)->key = value;
	}
	else if (pos == -1)
		if (!add_back_env(env, value))
			return (false);
	return (true);
}

int	bl_export(t_shell *shell)
{
    char **str;
    t_env_list **env;
	int	exit_code;
	int	i;

    (*env) = shell->env_head;
	exit_code = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (*env && !export_no_args((*env)))
			return (print_error("Error: malloc failed"));
		return (0);
	}
	while (str[i])
	{
		if (!valid_identifier(str[i]))
		{
			print_error("export: invalid identifier\n");
			exit_code = 1;
		}
		else if (!export(str[i], env))
			return (print_error("Error: malloc failed"));
		i++;
	}
	return (exit_code);
}