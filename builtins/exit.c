/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:48:33 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 12:28:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int 	all_atoi(char *str)
// {
// 	int	signe;
// 	int	i;
// 	int	nb;

// 	i = 0;
// 	signe = 1;
// 	nb = 0;
// 	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-')
// 	{
// 		signe = -signe;
// 		i++;
// 	}
// 	else if (str[i] == '+')
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		nb = nb * 10 + str[i] - '0';
// 		i++;
// 	}
// 	return (nb * signe);
// }

// void	bl_exit(char **arg, t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("exit\n");
// 	if (arg[0])
// 	{
// 		i = ms_check_exit_arg(arg[0]);
// 		if (arg[1] && i == 0)
// 		{
// 			ft_printf("minishell: exit: too many arguments\n");
// 			shell->excode = 1;
// 			return ;
// 		}
// 	}
// 	free_shell(shell);
// 	exit(shell->excode);
// }



// static int	almost_atoi(char *str, int *err)
// {
// 	unsigned long long	ret;
// 	int					i;
// 	int					j;
// 	int					pn;

// 	i = 0;
// 	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	pn = 1;
// 	if (str[i] == '+' || str[i] == '-')
// 		if (str[i++] == '-')
// 			pn = -1;
// 	j = i;
// 	ret = 0;
// 	while ('0' <= str[i] && str[i] <= '9')
// 		ret = ret * 10 + (str[i++] - 48);
// 	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
// 		(pn == 1 && (ret > LONG_MAX))))
// 		*err = 1;
// 	return ((int)((ret * pn) % 256));
// }

// void	ft_exit(t_data *data, char **args)
// {
// 	int	ret;
// 	int	err;

// 	ret = 0;
// 	err = 0;
// 	if (args[1])
// 	{ 
// 		ret = almost_atoi(args[1], &err);
// 		if (err)
// 		{
// 			print_error("exit: ");
// 			print_error(args[1]);
// 			print_error(": numeric argument required\n");
// 			free_t_env(data, NULL, 2);
// 		}
// 	}
// 	if (args[1] && args[2])
// 	{
// 		print_error("exit: too many arguments\n");
// 		data->exit_code = 1;
// 		return ;
// 	}
// 	if (!args[1])
// 		free_t_env(data, NULL, data->exit_code);
// 	free_t_env(data, NULL, ret);
// }