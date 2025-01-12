/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:34:23 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 17:20:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>

void	builtin_cmd(t_shell *shell)
{
	if (!shell->s_current->cmd)
		return ;
	else if (!ft_strcmp("exit", shell->s_current->args[0]))
		bl_exit(shell, shell->s_current->args);
	else if (!ft_strcmp("echo", shell->s_current->args[0]))
		bl_echo(shell);
	else if (!ft_strcmp("pwd", shell->s_current->args[0]))
		bl_pwd(shell);
	else if (!ft_strcmp("cd", shell->s_current->args[0]))
		bl_cd(shell, shell->s_current->args);
	else if (!ft_strcmp("env", shell->s_current->args[0]))
		bl_env(shell);
	else if (!ft_strcmp("export", shell->s_current->args[0]))
		bl_export(shell, shell->s_current->args);
	else if (!ft_strcmp("unset", shell->s_current->args[0]))
		bl_unset(shell, shell->s_current->args);
	else
		return ;
	close(0);
	close(1);
	(free_shell(shell), exit(1));
}

void	exev(t_shell *shell, char **envp)
{
	struct stat	st;

	if (shell->s_current->cmd)
	{
		if (!shell->s_current->cmd_path || is_empty(shell->s_current->cmd))
			print_dup(shell->s_current->cmd, ": command not found");
		else if (stat(shell->s_current->cmd_path, &st) == 0
			&& S_ISDIR(st.st_mode))
			print_dup(shell->s_current->cmd, ": Is a directory");
		else if (access(shell->s_current->cmd_path, F_OK) == -1)
		{
			if (shell->s_current->cmd[0] == '/'
				|| shell->s_current->cmd[0] == '.')
				print_dup(shell->s_current->cmd, ": No such file or directory");
			else
				print_dup(shell->s_current->cmd, ": command not found");
		}
		else if (access(shell->s_current->cmd_path, X_OK) == -1)
			print_dup(shell->s_current->cmd, ": Permission denied");
		else if (!execve(shell->s_current->cmd_path, shell->s_current->args,
				envp))
			print_dup(shell->s_current->cmd, ": command error");
	}
	(close(0), close(1), free_shell(shell), exit(0));
}

void	check_access(t_shell *shell)
{
	struct stat	st;

	if (shell->s_current->cmd)
	{
		if (!shell->s_current->cmd_path)
			shell->excode = 127;
		else if (stat(shell->s_current->cmd_path, &st) == 0
			&& S_ISDIR(st.st_mode))
			shell->excode = 126;
		else if (access(shell->s_current->cmd_path, F_OK) == -1)
			shell->excode = 127;
		else if (access(shell->s_current->cmd_path, X_OK) == -1)
			shell->excode = 126;
		else
			shell->excode = 0;
	}
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

void	builtin_one_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	check_files(shell);
	if (handle_redirs(shell))
		return ;
	close_files(shell);
	if (!ft_strcmp(shell->s_head->cmd, "exit"))
		bl_exit(shell, shell->s_head->args);
	else if (!ft_strcmp(shell->s_head->cmd, "cd"))
		i = bl_cd(shell, shell->s_head->args);
	else if (!ft_strcmp(shell->s_head->cmd, "export"))
		i = bl_export(shell, shell->s_head->args);
	else if (!ft_strcmp(shell->s_head->cmd, "unset"))
		i = bl_unset(shell, shell->s_head->args);
	else if (!ft_strcmp(shell->s_head->cmd, "pwd"))
		i = bl_pwd(shell);
	else if (!ft_strcmp(shell->s_head->cmd, "env"))
		i = bl_env(shell);
	else if (!ft_strcmp(shell->s_head->cmd, "echo"))
		bl_echo(shell);
	shell->excode = i;
}
