/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:42:15 by wscherre          #+#    #+#             */
/*   Updated: 2023/11/20 17:26:23 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src && !dest)
		return (NULL);
	while (i < size)
	{
		*(unsigned char *)(dest + i) = *(unsigned const char *)(src + i);
		i++;
	}
	return (dest);
}
