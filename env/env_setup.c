/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:59:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 13:29:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool conf_second_env(t_shell *shell)
{
    char	path[PATH_MAX];
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || !add_back_env(&(shell->env_head), tmp) || getcwd(path, PATH_MAX) == NULL)
		free_shell(shell);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !add_back_env(&(shell->env_head), tmp))
		free_shell(shell);
	return (1);
}

int conf_env(t_shell *shell, char **env) {
    t_env_list *envp;
    int i;
    char *temps;

    if (!(*env)) {
        printf("Environment is empty\n");
        return (conf_second_env(shell));
    }
    i = -1;
    envp = NULL;
    while (env[++i]) {
        temps = ft_strdup(env[i]);
        if (!temps) {
            printf("Failed to duplicate string\n");
            return (free_list(&envp));
        }
        if (!add_back_env(&envp, temps)) {
            printf("Failed to add environment variable: %s\n", temps);
            return (free_list(&envp));
        }
    }
    shell->env_head = envp;
    printf("Environment setup complete\n");
    return (1);
}
