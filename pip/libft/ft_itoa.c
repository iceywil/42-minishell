/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:52:42 by wscherre          #+#    #+#             */
/*   Updated: 2023/11/14 15:52:43 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_length(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_ispositive(int length, long nbr)
{
	char	*res;

	res = malloc((length + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[length] = '\0';
	while (length--)
	{
		res[length] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (res);
}

char	*ft_isnegative(int length, long nbr)
{
	char	*res;

	res = malloc((length + 1) * sizeof(char));
	if (!res)
		return (NULL);
	nbr = -nbr;
	res[length] = '\0';
	while (--length)
	{
		res[length] = (nbr % 10) + '0';
		nbr /= 10;
	}
	res[0] = '-';
	return (res);
}

char	*ft_iszero(void)
{
	char	*res;

	res = malloc(2 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		length;

	nbr = n;
	length = ft_length(n);
	if (nbr < 0)
		return (ft_isnegative(length, nbr));
	else if (nbr == 0)
		return (ft_iszero());
	else
		return (ft_ispositive(length, nbr));
}
