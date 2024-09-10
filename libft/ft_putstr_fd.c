/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:26:18 by wscherre          #+#    #+#             */
/*   Updated: 2023/11/20 16:40:21 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int				i;
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	i = 0;
	if (!s2)
		return ;
	while (s2[i])
	{
		write(fd, &s2[i], 1);
		i++;
	}
}
