/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:57:22 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 12:19:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env(char **env, char *ag)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], ag) == 0)
		{
			ft_free_double_tab(split);
			break ;
		}
		else
			i++;
		ft_free_double_tab(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

char	*bl_varenv(char **env, char *arg)
{
	int		i;
	char	*var_env;
	size_t	arg_len;

	i = 0;
	var_env = NULL;
	arg_len = ft_strlen(arg);
	while (env[i] && !var_env)
	{
		if (ft_strncmp(env[i], arg, arg_len) == 0 && env[i][arg_len] == '=')
			var_env = ft_strdup(env[i] + arg_len + 1);
		i++;
	}
	return (var_env);
}

int	env_compare(char **env, char **arg, int i)
{
	size_t	arg_len;

	while (env[i])
	{
		if (ft_strncmp(env[i], arg[0], arg_len) == 0 && env[i][arg_len] == '=')
			break ;
		i++;
	}
	return (i);
}

/* Remplace une ligne dans env par le nouveau contenue. Si la ligne n'existe
pas en cree une nouvelle. Arg devrait etre ex: HOME= et new content devrait 
etre ce qui va etre remplacer dedans. */
void	bl_set_env(char **env, char *value)
{
	char **arg;
	int i;
	t_shell *bl;
	
	i = env_compare(env, arg, i);
	arg = ft_split(value, '=');
	if (env[i] == NULL)
	{
		bl->env = bl_add_line(env, value);
		ft_free_double_tab(arg);
		return ;
	}
	free(env[i]);
	value = ft_strdup(value);
	env[i] = value;
	ft_free_double_tab(arg);
}
