/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:51:02 by codespace         #+#    #+#             */
/*   Updated: 2025/01/02 18:55:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bl_pwd(t_shell *shell)
{
	char	*pwd;

	if (shell->s_current->args[1] && shell->s_current->args[1][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: invalid option\n", 2);
		shell->excode = 2;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ",
			2);
		ft_putstr_fd("getcwd: cannot access parent directories\n",
			2);
		shell->excode = 1;
		return ;
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
}
