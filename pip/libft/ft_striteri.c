/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:12:18 by wscherre          #+#    #+#             */
/*   Updated: 2023/11/20 16:41:35 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;
	char	*c;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		c = (char *)(s + i);
		f(i, c);
		i++;
	}
	return ;
}
