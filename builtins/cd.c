/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:45:37 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 12:27:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(char *arg, char *s)
{
	char	*string;

	string = ft_strjoin(arg, s);
	bl_set_env(g_shell.env, string);
	free(string);
}

int	bl_cd(char *arg)
{
	char	c[PATH_MAX];

	if (!arg)
	{
		arg = env(g_shell.env , "HOME") + 5;
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
	{
		if (arg[0] == '\0')
			return (1);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	pwd("OLDPWD=", c);
	getcwd(c, sizeof(c));
	pwd("PWD=", c);
	return (0);
}
