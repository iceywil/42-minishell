/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:34:23 by codespace         #+#    #+#             */
/*   Updated: 2025/01/03 00:12:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (shell->s_current->cmd)
	{
		if (!shell->s_current->cmd_path)
			print_err(shell->s_current->cmd, ": command not found", 0);
		else if (access(shell->s_current->cmd_path, F_OK) == -1)
		{
			if (shell->s_current->cmd[0] == '/'
				|| shell->s_current->cmd[0] == '.')
				print_err(shell->s_current->cmd, ": No such file or directory",
					0);
			else
				print_err(shell->s_current->cmd, ": command not found", 0);
		}
		else if (access(shell->s_current->cmd_path, X_OK) == -1)
			print_err(shell->s_current->cmd, ": Permission denied", 0);
		else if (!execve(shell->s_current->cmd_path, shell->s_current->args,
				envp))
			print_err(shell->s_current->cmd, ": command error", 0);
	}
	close(0);
	close(1);
	(free_shell(shell), exit(1));
}

void	check_access(t_shell *shell)
{
	if (!shell->s_current->cmd_path)
		shell->excode = 127;
	else if (access(shell->s_current->cmd_path, F_OK) == -1)
		shell->excode = 127;
	else if (access(shell->s_current->cmd_path, X_OK) == -1)
		shell->excode = 126;
	else
		shell->excode = 0;
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

int	builtin_one_cmd(t_shell *shell)
{
	if (!ft_strcmp(shell->s_head->cmd, "exit") || !ft_strcmp(shell->s_head->cmd,
			"cd") || !ft_strcmp(shell->s_head->cmd, "export")
		|| !ft_strcmp(shell->s_head->cmd, "unset"))
	{
		handle_redirs(shell);
		if (shell->s_current->infile > 0)
			close(shell->s_current->infile);
		if (shell->s_current->outfile > 0)
			close(shell->s_current->outfile);
		if (!ft_strcmp(shell->s_head->cmd, "exit"))
			bl_exit(shell, shell->s_head->args);
		else if (!ft_strcmp(shell->s_head->cmd, "cd"))
			bl_cd(shell, shell->s_head->args);
		else if (!ft_strcmp(shell->s_head->cmd, "export"))
			bl_export(shell, shell->s_head->args);
		else if (!ft_strcmp(shell->s_head->cmd, "unset"))
			bl_unset(shell, shell->s_head->args);
		return (1);
	}
	return (0);
}
