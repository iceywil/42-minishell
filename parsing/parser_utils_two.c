/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:05:35 by a                 #+#    #+#             */
/*   Updated: 2024/10/26 01:05:42 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_side_quotes(char *str)
{
	int		len;
	char	quote_type;

	if (!str || !*str)
		return ;
	len = ft_strlen(str);
	if (len < 2)
		return ;
	quote_type = '\0';
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len
			- 1] == '\"'))
	{
		quote_type = str[0];
	}
	if (quote_type)
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
}
