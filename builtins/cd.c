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

static int count_arg(char **params)
{
	int count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void error_malloc(void)
{
	print_error("Error: malloc failed");
	return;
}

static void	update_oldpwd(t_shell *shell)
{
	t_env_list	*tmp;
	char	*test;
	int		len;

	tmp = shell->env_head;
	test = NULL;
	len = env_size(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->key, "PWD=", 3) == 0)
			test = tmp->key;
		tmp = tmp->next;
	}
	if (!test)
		export("OLDPWD", &shell->env_head);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (error_malloc());
		export(test, &shell->env_head);
	}
	free(test);
}

static void update_pwd(t_shell *shell, char *param)
{
    char    cwd[PATH_MAX];
    char    *pwd;
    char    *oldpwd;

    update_oldpwd(shell);
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        perror(param);
        return;
    }

    // Convertir le chemin en format Unix si nécessaire
    if (cwd[1] == ':') // Si c'est un chemin Windows
    {
        char temp[PATH_MAX] = "/cygdrive/";
        if (cwd[0] >= 'A' && cwd[0] <= 'Z')
            temp[9] = cwd[0] + 32; // Convertir en minuscule
        else
            temp[9] = cwd[0];
        strcat(temp, cwd + 2);
        strcpy(cwd, temp);
    }

    // Mettre à jour PWD
    pwd = ft_strjoin("PWD=", cwd);
    if (!pwd)
        return (error_malloc());
    export(pwd, &shell->env_head);
    free(pwd);

    // Mettre à jour le prompt
    if (shell->cwd)
        free(shell->cwd);
    shell->cwd = create_buffer();
    if (!shell->cwd)
        error_malloc();

    printf("PWD updated to: %s\n", cwd);
}

static int ft_cdhome(t_shell *shell)
{
	t_env_list *tmp;
	char *home;
	int len;

	tmp = shell->env_head;
	home = NULL;
	len = env_size(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->key, "HOME=", 5) == 0)
		{
			home = tmp->key + 5;
			break;
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

int bl_cd(t_shell *shell, char **params)
{
    int res;
    char *old_pwd;
    char *new_pwd;

    old_pwd = getcwd(NULL, 0);
    printf("Current directory before cd: %s\n", old_pwd);
    free(old_pwd);

    if (count_arg(params) == 1)
    {
        printf("Changing to home directory\n");
        res = ft_cdhome(shell);
    }
    else if (count_arg(params) == 2)
    {
        printf("Changing to directory: %s\n", params[1]);
        res = chdir(params[1]);

        if (res == 0)
        {
            new_pwd = getcwd(NULL, 0);
            printf("Directory changed successfully to: %s\n", new_pwd);
            update_pwd(shell, params[1]);
            
            // Mettre à jour le prompt
            if (shell->cwd)
                free(shell->cwd);
            shell->cwd = create_buffer();
            if (!shell->cwd)
                return (1);
            
            free(new_pwd);
        }
        else
        {
            perror("chdir failed");
        }
    }
    else
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return 1;
    }

    return res;
}