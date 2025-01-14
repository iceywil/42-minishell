/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:51:02 by codespace         #+#    #+#             */
/*   Updated: 2025/01/13 03:51:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bl_pwd(t_shell *shell)
{
	char	pwd[PATH_MAX];
	char	*tmp;

	if (shell->s_current->args[1] && shell->s_current->args[1][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: invalid option\n", 2);
		return (2);
	}
	tmp = getcwd(pwd, PATH_MAX);
	if (!tmp)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories\n", 2);
		return (1);
	}
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
