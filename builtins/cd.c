/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:36:08 by codespace         #+#    #+#             */
/*   Updated: 2025/01/13 03:47:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_oldpwd(t_shell *shell)
{
	char	old_pwd[PATH_MAX];
	char	*oldpwd_var;

	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return ;
	oldpwd_var = ft_strjoin("OLDPWD=", old_pwd);
	if (oldpwd_var)
	{
		export(shell, oldpwd_var);
		free(oldpwd_var);
	}
}

static void	update_pwd(t_shell *shell, char *new_path)
{
	char	*pwd_var;

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
		if (!ft_strncmp(tmp->key, "HOME=", 5))
		{
			home = tmp->key + 5;
			update_oldpwd(shell);
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
	char	tmp[PATH_MAX];

	if (params[1] && params[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!params[1] || !ft_strcmp(params[1], "~"))
		return (ft_cdhome(shell));
	(path = params[1], update_oldpwd(shell));
	if (!chdir(path))
	{
		update_pwd(shell, path);
		path = getcwd(tmp, PATH_MAX);
		if (!path)
		{
			ft_putstr_fd("chdir: error retrieving current directory: ge", 2);
			ft_putstr_fd("tcwd: cannot access parent directories: No suc", 2);
			return (ft_putstr_fd("h file or directory\n", 2), 0);
		}	
	}
	else
		return (perror(path), 1);
	return (0);
}
