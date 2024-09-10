/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:45:54 by wscherre          #+#    #+#             */
/*   Updated: 2023/11/20 17:26:46 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	if (dest > src)
	{
		while (size > 0)
		{
			size--;
			*(unsigned char *)(dest + size) = *(unsigned char *)(src
					+ size);
		}
	}
	else
	{
		ft_memcpy(dest, src, size);
	}
	return (dest);
}
