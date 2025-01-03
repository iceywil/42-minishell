/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:43:46 by codespace         #+#    #+#             */
/*   Updated: 2025/01/03 18:28:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd(t_shell *shell, char *new_path)
{
	char	old_pwd[PATH_MAX];
	char	*pwd_var;
	char	*oldpwd_var;

	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return ;
	oldpwd_var = ft_strjoin("OLDPWD=", old_pwd);
	if (oldpwd_var)
	{
		export(shell, oldpwd_var);
		free(oldpwd_var);
	}
	pwd_var = ft_strjoin("PWD=", new_path);
	if (pwd_var)
	{
		export(shell, pwd_var);
		free(pwd_var);
	}
}

static int	ft_cdhome(t_shell *shell)
{
	t_env_list	*tmp;
	char		*home;

	tmp = shell->env_head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "HOME=", 5) == 0)
		{
			home = tmp->key + 5;
			if (chdir(home) == 0)
			{
				update_pwd(shell, home);
				return (0);
			}
			perror(home);
			return (1);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("cd: HOME not set\n", 2);
	return (1);
}

int	bl_cd(t_shell *shell, char **params)
{
	char	*path;

	if (!params[1] || !ft_strcmp(params[1], "~"))
		return (ft_cdhome(shell));
	path = params[1];
	if (chdir(path) == 0)
	{
		update_pwd(shell, path);
		return (0);
	}
	perror(path);
	return (1);
}
