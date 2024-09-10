/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:20:00 by wscherre          #+#    #+#             */
/*   Updated: 2024/01/15 17:52:07 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *form, ...)
{
	int		len;
	int		i;
	va_list	args;

	if (!form)
		return (0);
	len = 0;
	i = 0;
	va_start(args, form);
	while (form[i])
	{
		if (form[i] == '%')
		{
			i++;
			len += ft_print_formatted(args, form[i]);
		}
		else
			len += write(1, &form[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
