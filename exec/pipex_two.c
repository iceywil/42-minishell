/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:34:23 by codespace         #+#    #+#             */
/*   Updated: 2024/12/10 09:13:34 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cmd(t_shell *shell, char **envp)
{
	t_env_list *env;
	if (ft_strncmp(shell->s_current->args[0], "exit", INT_MAX) == 0)
		(bl_exit(shell, shell->s_current->args), exit(shell->excode));
	if (!ft_strncmp("echo", shell->s_current->args[0], INT_MAX))
		(bl_echo(shell), exit(shell->excode));
	else if (!ft_strncmp("pwd", shell->s_current->args[0], INT_MAX))
		(bl_pwd(shell), exit(shell->excode));
	else if (!ft_strncmp("cd", shell->s_current->args[0], 2))
		(bl_cd(shell, shell->s_current->args), exit(shell->excode));
	else if (!ft_strncmp("env", shell->s_current->args[0], INT_MAX))
		(bl_env(shell), exit(shell->excode));
	// else if (!ft_strncmp("export", shell->s_current->args[0], 6))
	// 	(bl_export(shell), exit(shell->excode));
	// else if (ft_strcmp(shell->s_current->args[0], "unset") == 0)
	// {
	// 	bl_unset(shell->s_current->args[1]);
	// 	return (1);
	// }
	else
		exev(shell, envp);
}

void	exev(t_shell *shell, char **envp)
{
	if (!shell->s_current->cmd_path)
		print_err(shell->s_current->cmd, ": command not found", 0, 0);
	else if (access(shell->s_current->cmd_path, F_OK) == -1)
	{
		if (shell->s_current->cmd[0] == '/' || shell->s_current->cmd[0] == '.')
			print_err(shell->s_current->cmd, ": No such file or directory", 0,
				0);
		else
			print_err(shell->s_current->cmd, ": command not found", 0, 0);
	}
	else if (access(shell->s_current->cmd_path, X_OK) == -1)
		print_err(shell->s_current->cmd, ": Permission denied", 0, 0);
	else if (!execve(shell->s_current->cmd_path, shell->s_current->args, envp))
		print_err(shell->s_current->cmd, ": command error", 0, 0);
	exit(1);
}

void	check_access(t_shell *shell)
{
	if (!shell->s_current->cmd_path)
		shell->excode = 127;
	else if (access(shell->s_current->cmd_path, F_OK) == -1)
		shell->excode = 127;
	else if (access(shell->s_current->cmd_path, X_OK) == -1)
		shell->excode = 126;
}

void	malloc_fds(t_shell *shell)
{
	int	**fds;
	int	i;

	i = 0;
	fds = malloc(sizeof(int *) * (shell->cmd_nbr + 1));
	if (!fds)
		malloc_error(shell);
	while (i < shell->cmd_nbr)
	{
		fds[i] = NULL;
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			malloc_error(shell);
		fds[i][0] = -1;
		fds[i][1] = -1;
		i++;
	}
	fds[i] = NULL;
	shell->fds = fds;
}
