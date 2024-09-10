/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:43:03 by wscherre          #+#    #+#             */
/*   Updated: 2023/11/14 15:11:50 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	x;

	x = -1;
	i = 0;
	if (!c)
		return ((char *)(s + ft_strlen((char *)s)));
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			x = i;
		i++;
	}
	if (x < 0)
		return (NULL);
	return ((char *)(s + x));
}
