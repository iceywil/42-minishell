/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:13:21 by wscherre          #+#    #+#             */
/*   Updated: 2024/04/25 15:04:44 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iss_sep(char d, char c)
{
	if (d == c)
		return (1);
	if (d == '\0')
		return (1);
	return (0);
}

int	ft_count_strings(char const *str, char c)
{
	int	i;
	int	strings;

	strings = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_iss_sep(str[i + 1], c) == 1 && ft_iss_sep(str[i], c) == 0)
			strings++;
		i++;
	}
	return (strings);
}

void	ft_strrcpy(char *dest, char const *src, char c)
{
	int	i;

	i = 0;
	while (ft_iss_sep(src[i], c) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	ft_split_strings(char **ptr, char const *str, char c)
{
	int	i;
	int	j;
	int	string;

	string = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_iss_sep(str[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_iss_sep(str[i + j], c) == 0)
				j++;
			ptr[string] = (char *)malloc(sizeof(char) * (j + 1));
			if (!ptr[string])
				return (0);
			ft_strrcpy(ptr[string], str + i, c);
			i += j;
			string++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		totstrings;

	if (!s)
		return (NULL);
	totstrings = ft_count_strings(s, c);
	ptr = malloc(sizeof(char *) * (totstrings + 1));
	if (!ptr)
		return (NULL);
	ptr[totstrings] = 0;
	if (ft_split_strings(ptr, s, c) == 0)
		return (ft_free_double_tab(&ptr), NULL);
	return (ptr);
}
/*
void	ft_free_double_tab(char ***tab)
{
	int	i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

int	main(void)
{
	char **tab;

	tab = ft_split("addskdsk sdq", ' ');
	ft_free_double_tab(&tab);
} */