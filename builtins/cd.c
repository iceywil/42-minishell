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
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	test = NULL;
	while (len--)
	{
		if (ft_strncmp(tmp->key, "PWD=", 3) == 0)
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

static void	update_pwd(t_shell *shell, char *param)
{
	char cwd[PATH_MAX];
	char *pwd;
	char *oldpwd;

	update_oldpwd(shell);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export(shell, pwd, &shell->env_head);
	free(pwd);
}

static int	ft_cdhome(t_shell *shell)
{
	t_env_list *tmp;
	char *home;
	int len;

	tmp = shell->env_head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	home = NULL;
	while (len--)
	{
		if (ft_strncmp(tmp->key, "HOME=", 5) == 0)
		{
			home = tmp->key + 5;
			break ;
		}
		tmp = tmp->next;
	}
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == 0)
		update_pwd(shell, home);
	else
		perror(home);
	return (0);
}

int	bl_cd(t_shell *shell, char **params)
{
	int res;

	if (count_arg(params) == 1)
		return (ft_cdhome(shell));
	if (count_arg(params) == 2)
	{
		res = chdir(params[1]);
		if (res == 0)
			update_pwd(shell, params[1]);
		if (res == -1)
			res *= -1;
		if (res == 1)
			perror(params[1]);
		return (res);
	}
	ft_putstr_fd("cd: too many arguments\n", 2);
	return (1);
}
