/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:52:49 by codespace         #+#    #+#             */
/*   Updated: 2025/01/03 02:32:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_to_arr(t_shell *shell, t_env_list *env)
{
	char		**dest;
	int			i;

	dest = NULL;
	i = 0;
	dest = (char **)malloc(sizeof(char *) * (env_size(shell) + 1));
	if (!dest)
		return (NULL);
	while (env)
	{
		dest[i] = (env->key);
		env = env->next;
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

void	sort_array(char **arr)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			diff = ft_strcmp(arr[i], arr[j]);
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
