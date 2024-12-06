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

static int	cmp_llmax(const char *str, long long value, int sign)
{
	int	digit;

	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		digit = *str - '0';
		if (value > (LLONG_MAX - digit) / 10)
			return (0);
		value = value * 10 + digit;
		str++;
	}
	value *= sign;
	if (value < LLONG_MIN || value > LLONG_MAX)
		return (0);
	return (1);
}

static int	check_long(const char *str)
{
	long long	value;
	int			sign;

	value = 0;
	if (*str == '\0')
		return (0);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0')
		return (0);
	return (cmp_llmax(str, value, sign));
}

static int	exit_options(t_shell *shell, int *flag)
{
	int	i;

	i = 0;
	if (!check_long(shell->s_current->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(shell->s_current->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		(*flag) = 1;
		return (2);
	}
	return (ft_atoi(shell->s_current->args[1]) % 256);
}

void	bl_exit(t_shell *shell)
{
	int	ext;
	int	flag;

	flag = 0;
	if (shell->s_current->args[1])
		shell->excode = exit_options(shell, &flag);
	if (shell->s_current->args[1] && shell->s_current->args[2] && !flag)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_putstr_fd("exit\n", 1);
		shell->excode = 1;
		return ;
	}
	if (shell->s_current->next || shell->s_current->prev)
		return ;
	free_shell(shell);
	ft_putstr_fd("exit\n", 1);
	exit(ext);
}