/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:48:33 by codespace         #+#    #+#             */
/*   Updated: 2024/12/17 02:20:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int atoi_exit(const char *str, int *err)
{
    unsigned long long result;
    int i;
    int sign;

    result = 0;
    i = 0;
    sign = 1;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
        result = result * 10 + (str[i++] - '0');
    if (str[i] != '\0' || result > LONG_MAX)
        *err = 1;
    else
        *err = 0;
    return (int)((result * sign) % 256);
}

static int get_exit_status(t_shell *shell, char **args, int *should_exit)
{
    int i;
    int j;

    *should_exit = 1;
    if (!args[1])
        return (shell->excode);

    i = atoi_exit(args[1], &j);
    if (j)
    {
        print_error("exit: ");
        print_error(args[1]);
        print_error(": numeric argument required\n");
        return (2);
    }
    if (args[2])
    {
        print_error("exit: too many arguments\n");
        shell->excode = 1;
        *should_exit = 0;
        return (1);
    }
    return (i);
}

void bl_exit(t_shell *shell, char **args)
{
    int exit_status;
    int should_exit;
    
    should_exit = 0;
    exit_status = get_exit_status(shell, args, &should_exit);
    if (!should_exit)
        return;
    ft_putstr_fd("exit\n", 2);
    free_shell(shell);
    exit(exit_status);
}