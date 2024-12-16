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

bool export(char *str, t_env_list **env) {
    int pos;
    char *value;
    t_env_list *current;

    value = ft_strdup(str);
    if (!value)
        return (false);

    current = *env;
    while (current) {
        if (ft_strncmp(current->key, str, ft_strchr(str, '=') - str) == 0) {
            free(current->key);
            current->key = value;
            return (true);
        }
        current = current->next;
    }
    return add_back_env(env, value);
}

// int	bl_export(char **str, t_env_list **env)
// {
// 	int	exit_code;
// 	int	i;

// 	exit_code = 0;
// 	i = 1;
// 	if (!str || !str[i])
// 	{
// 		if (*env && !export_no_args((*env)))
// 			return (print_error("Error: malloc failed"));
// 		return (0);
// 	}
// 	while (str[i])
// 	{
// 		if (!valid_identifier(str[i]))
// 		{
// 			print_error("export: invalid identifier\n");
// 			exit_code = 1;
// 		}
// 		else if (!export(str[i], env))
// 			return (print_error("Error: malloc failed"));
// 		i++;
// 	}
// 	return (exit_code);
// }