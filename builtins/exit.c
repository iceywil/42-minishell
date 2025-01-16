/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:50:30 by codespace         #+#    #+#             */
/*   Updated: 2025/01/16 17:15:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	atoi_exit(const char *str, int *err)
{
	unsigned long long	result;
	int					sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	*err = 0;
	while (str[i] && isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > LONG_MAX)
			return (*err = 1, 0);
	}
	if (str[i] != '\0')
		return (*err = 1, 0);
	return ((int)((result * sign) % 256));
}

static int	get_exit_status(t_shell *shell, char **args, int *should_exit)
{
	int	i;
	int	j;

	*should_exit = 1;
	if (!is_empty(args[1]))
		i = atoi_exit(args[1], &j);
	else
		j = 1;
	if (j)
	{
		(ft_putstr_fd("exit\nexit: ", 2), ft_putstr_fd(args[1], 2));
		return (ft_putstr_fd(": numeric argument required\n", 2), 2);
	}
	if (args[1] && args[2])
	{
		shell->excode = 1;
		*should_exit = 0;
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		return (1);
	}
	return (i);
}

int	bl_exit(t_shell *shell, char **args)
{
	int	exit_status;
	int	should_exit;

	should_exit = 0;
	if (!args[1])
	{
		ft_putstr_fd("exit\n", 2);
		free_shell(shell);
		exit(shell->excode);
	}
	exit_status = get_exit_status(shell, args, &should_exit);
	if (!should_exit)
		return (shell->excode);
	free_shell(shell);
	exit(exit_status);
	return (shell->excode);
}
