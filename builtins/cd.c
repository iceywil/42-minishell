/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:45:37 by codespace         #+#    #+#             */
/*   Updated: 2024/11/29 14:54:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void update_env(t_env_list *env_head, const char *key, const char *value)
// {
// 	t_env_list *current = env_head;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, key) == 0)
// 		{
// 			free(current->value);
// 			current->value = ft_strdup(value);
// 			return;
// 		}
// 		current = current->next;
// 	}
// }

// void update_pwd(char *old_pwd)
// {
// 	char *pwd_d = getcwd(NULL, 0);
// 	if (!pwd_d)
// 	{
// 		perror("getcwd");
// 		return;
// 	}
// 	update_env(g_shell.env_head, "OLDPWD", old_pwd);
// 	update_env(g_shell.env_head, "PWD", pwd_d);
// 	free(old_pwd);
// 	free(pwd_d);
// }

// void exec_cd(const char *dir)
// {
// 	t_env_list *env_copy;
// 	char *old_pwd;

// 	old_pwd = NULL;
// 	env_copy = g_shell.env_head;
// 	while (env_copy)
// 	{
// 		if (ft_strcmp(env_copy->key, "PWD") == 0)
// 		{
// 			if (env_copy->value)
// 			{
// 				old_pwd = ft_strdup(env_copy->value);
// 				break;
// 			}
// 		}
// 		env_copy = env_copy->next;
// 	}
// 	if (chdir(dir) == -1)
// 	{
// 		perror("minishell: cd");
// 		g_shell.excode = 1;
// 		free(old_pwd);
// 		return;
// 	}
// 	update_pwd(old_pwd);
// }

// void cd_home(void)
// {
// 	t_env_list *env_copy;

// 	env_copy = g_shell.env_head;
// 	while (env_copy)
// 	{
// 		if (ft_strcmp(env_copy->key, "HOME") == 0)
// 		{
// 			exec_cd(env_copy->value);
// 			break;
// 		}
// 		env_copy = env_copy->next;
// 	}
// 	if (!env_copy || env_copy->value == NULL)
// 	{
// 		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
// 		g_shell.excode = 1;
// 		return;
// 	}
// 	exec_cd(env_copy->value);
// }

// int ft_checkdir(void)
// {
//     DIR *dir;
// 	dir = opendir(g_shell.builtin_path[1]);
//     if (!dir)
//     {
//         ft_putstr_fd("minishell: cd: %s: ", 2);
// 		ft_putstr_fd(g_shell.builtin_path[1], 2);
//         perror(NULL);
//         g_shell.excode = 1;
//         return 0;
//     }
//     closedir(dir);
//     return 1;
// }

// void bl_cd(void)
// {
// 	if (g_shell.builtin_path[1] && g_shell.builtin_path[2])
// 	{
// 		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
// 		g_shell.excode = 1;
// 		return;
// 	}
// 	if (!g_shell.builtin_path[1])
// 		cd_home();
// 	else
// 	{
// 		if (!ft_checkdir())
// 			return;
// 		exec_cd(g_shell.builtin_path[1]);
// 	}
// }
