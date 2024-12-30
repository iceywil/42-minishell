/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/09 14:45:37 by codespace         #+#    #+#             */
/*   Updated: 2024/11/29 14:54:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	count_arg(char **params)
{
	int count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void	error_malloc(void)
{
	print_error("Error: malloc failed");
	return ;
}

static void	update_oldpwd(t_shell *shell)
{
	t_env_list *tmp;
	char *test;
	int len;

	tmp = shell->env_head;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	tmp = shell->env_head;
	test = NULL;
	while (tmp && len--)
	{
		if (ft_strncmp(tmp->key, "PWD=", 4) == 0)
			test = tmp->key;
		tmp = tmp->next;
	}
	if (!test)
		export(shell, "OLDPWD", &shell->env_head);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (error_malloc());
		export(shell, test, &shell->env_head);
	}
	free(test);
}

static void	update_pwd(t_shell *shell, char *new_path)
{
	char old_pwd[PATH_MAX];
	char *pwd_var;
	char *oldpwd_var;

	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return;

	// Mettre à jour OLDPWD
	oldpwd_var = ft_strjoin("OLDPWD=", old_pwd);
	if (oldpwd_var)
	{
		export(shell, oldpwd_var, &shell->env_head);
		free(oldpwd_var);
	}

	// Mettre à jour PWD
	pwd_var = ft_strjoin("PWD=", new_path);
	if (pwd_var)
	{
		export(shell, pwd_var, &shell->env_head);
		free(pwd_var);
	}
}

static int	ft_cdhome(t_shell *shell)
{
	t_env_list *tmp;
	char *home;

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
	char *path;
	
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
