/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:04:30 by wscherre          #+#    #+#             */
/*   Updated: 2024/01/24 17:24:12 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_custom(char *fourre_merde, char *buff, int res)
{
	int		i;
	int		isrc;
	char	*newstatik;

	i = 0;
	isrc = 0;
	while (fourre_merde[i])
		i++;
	newstatik = malloc((i + res + 1) * sizeof(char));
	if (!newstatik)
		return (NULL);
	i = 0;
	while (fourre_merde[i])
	{
		newstatik[i] = fourre_merde[i];
		i++;
	}
	while (buff[isrc])
		newstatik[i++] = buff[isrc++];
	newstatik[i] = '\0';
	free(fourre_merde);
	return (newstatik);
}

int	ft_readline(int fd, char **fourre_merde)
{
	char	*buff;
	int		result;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	result = read(fd, buff, BUFFER_SIZE);
	if (result > 0)
	{
		buff[result] = '\0';
		*fourre_merde = ft_strcat_custom(*fourre_merde, buff, result);
		if (!(*fourre_merde))
		{
			free(buff);
			return (-1);
		}
	}
	if (result < 0 || *fourre_merde[0] == '\0')
		result = -1;
	free(buff);
	return (result);
}

char	*ft_fill_line(int fd, char **fourre_merde)
{
	int	result;
	int	i;

	while (1)
	{
		i = 0;
		while ((*fourre_merde)[i])
		{
			if ((*fourre_merde)[i] == '\n')
				return (ft_removelinefromstatic(fourre_merde));
			i++;
		}
		result = ft_readline(fd, fourre_merde);
		if (result < 0)
			return (NULL);
		if (result == 0)
			break ;
	}
	return (ft_removelinefromstatic(fourre_merde));
}

char	*ft_removelinefromstatic(char **fourre_merde)
{
	char	*statik;
	int		i;
	int		x;
	char	*res;
	int		z;

	statik = *fourre_merde;
	i = 0;
	while (statik[i] && statik[i] != '\n')
		i++;
	if (statik[i] == '\n')
		i++;
	res = malloc(i + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, statik, i);
	res[i] = '\0';
	x = 0;
	z = i;
	while (statik[z++])
		x++;
	ft_memmove(statik, statik + i, x);
	statik[x] = '\0';
	*fourre_merde = statik;
	return (res);
}
