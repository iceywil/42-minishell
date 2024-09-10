/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:31:46 by wscherre          #+#    #+#             */
/*   Updated: 2023/11/20 17:08:26 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s2;
	char	c;

	s2 = NULL;
	i = 0;
	if (!s || !f)
		return (NULL);
	while (s[i])
		i++;
	s2 = malloc((i + 1) * (sizeof(char)));
	if (!s2)
		return (NULL);
	s2[i] = '\0';
	i = 0;
	while (s[i])
	{
		c = *(char *)(s + i);
		s2[i] = f(i, c);
		i++;
	}
	return (s2);
}
