/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formatted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:33 by wscherre          #+#    #+#             */
/*   Updated: 2024/01/15 17:52:19 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_formatted(va_list args, char form)
{
	if (form == 'c')
		return (ft_print_c(va_arg(args, int)));
	else if (form == 's')
		return (ft_print_s(va_arg(args, const char *)));
	else if (form == 'p')
		return (ft_print_p(va_arg(args, void *)));
	else if (form == 'd' || form == 'i')
		return (ft_print_di(va_arg(args, int)));
	else if (form == 'u')
		return (ft_print_u(va_arg(args, unsigned int)));
	else if (form == 'x' || form == 'X')
		return (ft_print_x(form, va_arg(args, int)));
	else
	{
		write(1, &form, 1);
		return (1);
	}
}
