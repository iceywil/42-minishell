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


static int	ft_isllong(char *str)
{
	if (str[0] == '-' && ft_strlen(str) >= 20
		&& ft_strcmp(&str[1], "9223372036854775808") > 0)
		return (1);
	else if (ft_strlen(str) >= 19
		&& ft_strcmp(str, "9223372036854775807") > 0)
		return (1);
	return (0);
}

int	ms_check_exit_arg(char *arg)
{
	int			i;
	long long	exit_code;
	t_shell		*shell;


	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	if (ft_isdigit(arg[i]) == 0 || ft_isllong(arg) != 0)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", arg);
		shell->excode = 255;
		return (1);
	}
	exit_code = ft_atol(arg);
	shell->excode = exit_code % 256;
	if (shell->excode < 0 || shell->excode > 255)
		shell->excode = 255;
	return (0);
}

void	bl_exit(char **arg, t_shell *shell)
{
	int	i;

	i = 0;
	ft_printf("exit\n");
	if (arg[0])
	{
		i = ms_check_exit_arg(arg[0]);
		if (arg[1] && i == 0)
		{
			ft_printf("minishell: exit: too many arguments\n");
			shell->excode = 1;
			return ;
		}
	}
	free_shell(shell);
	exit(shell->excode);
}