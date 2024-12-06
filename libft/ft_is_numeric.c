/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:38:29 by marvin            #+#    #+#             */
/*   Updated: 2024/11/28 22:38:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_numeric(char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    if (!str || len == 0)
        return (0);
    if (str[i] == '-' || str[i] == '+' || str[i] == ' ')
        i = 1;
    else
        i = 0;
    while (i < len)
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
