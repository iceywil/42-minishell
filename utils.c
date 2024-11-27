/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:59:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 13:29:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cree une nouvelle matrix en ajoutant une ligne et free l'ancienne */
char	**bl_add_line(char **src, char *new_line)
{
	int	i;
	char	**new_src;

	i = 0;
	while (src[i])
		i++;
	new_src = malloc(sizeof(char *) * (i + 2));
	if (!new_src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new_src[i] = ft_strdup(src[i]);
		i++;
	}
	new_src[i] = ft_strdup(new_line);
	i++;
	new_src[i] = NULL;
	ft_free_double_tab(src);
	return (new_src);
}


char	**bl_remove_line(char **src, char *line)
{
	int	i;
	int	j;
	char	**new_src;

	i = 0;
	j = 0;
	while (src[i])
		i++;
	new_src = malloc(sizeof(char *) * (i + 1));
	if (!new_src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		if (ft_strcmp(src[i], line) == 0)
			i++;
		if (src[i])
		{
			new_src[j++] = ft_strdup(src[i]);
			i++;
		}
		
	}
	new_src[j] = NULL;
	ft_free_double_tab(src);
	return (new_src);
}
