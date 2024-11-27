/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:29:43 by wscherre          #+#    #+#             */
/*   Updated: 2024/10/27 23:54:19 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		s1len;
	int		s1start;
	int		s1end;

	if (!s1 || !set)
		return (NULL);
	s1len = ft_strlen((char *)s1);
	s1start = 0;
	s1end = s1len - 1;
	while (ft_is_sep(s1[s1start], (char *)set) && s1[s1start])
		s1start++;
	while (ft_is_sep(s1[s1end], (char *)set) && s1[s1end])
		s1end--;
	if (s1start > s1end)
	{
		s2 = ft_strdup("");
		if (!s2)
			return (NULL);
		return (s2);
	}
	s2 = ft_substr(s1, s1start, s1end - s1start + 1);
	if (!s2)
		return (NULL);
	return (s2);
}
