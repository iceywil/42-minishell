/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:43:18 by wscherre          #+#    #+#             */
/*   Updated: 2024/11/28 21:40:19 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;

	dest = malloc(n + 1);
	if (!dest)
		return (NULL);
	ft_strncpy(dest, s, n);
	return (dest);
}
