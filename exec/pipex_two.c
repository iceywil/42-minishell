/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:34:23 by codespace         #+#    #+#             */
/*   Updated: 2024/12/06 22:37:40 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cmd(t_shell *shell, char **envp)
{
	/* 	if (!ft_strcmp(shell->s_current->args[0], "echo"))
			return (echo_cmd(shell, envp), exit(0));
		else if (!ft_strcmp(shell->s_current->args[0], "cd"))
			return (cd_cmd(shell, envp), exit(0));
		else if (!ft_strcmp(shell->s_current->args[0], "pwd"))
			return (pwd_cmd(shell, envp), exit(0));
		else if (!ft_strcmp(shell->s_current->args[0], "export"))
			return (export_cmd(shell, envp), exit(0));
		else if (!ft_strcmp(shell->s_current->args[0], "unset"))
			return (unset_cmd(shell, envp), exit(0));
		else if (!ft_strcmp(shell->s_current->args[0], "env"))
			return (env_cmd(shell, envp), exit(0));
		else if (!ft_strcmp(shell->s_current->args[0], "exit"))
			return (exit_cmd(shell, envp), exit(0)); */
}

void	exev(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	if (!shell->s_current->cmd_path)
		print_err(shell->s_current->args[0], " Command not found", 0, 0);
	else if (access(shell->s_current->cmd_path, F_OK) == -1)
	{
		if (shell->s_current->cmd_path[0] == '/'
			|| shell->s_current->cmd_path[0] == '.')
			print_err(shell->s_current->args[0], " No such file or directory",
				0, 0);
		else
			print_err(shell->s_current->args[0], " Command not found", 0, 0);
	}
	else if (access(shell->s_current->cmd_path, X_OK) == -1)
		print_err(shell->s_current->args[0], " Permission denied", 0, 0);
	else if (!execve(shell->s_current->cmd_path, shell->s_current->args, envp))
		print_err(shell->s_current->args[0], " Command error", 0, 0);
	shell->err = 127;
	exit(0);
}

void	check_access(t_shell *shell)
{
	/* 	if (!shell->s_current->cmd_path)
			shell->err = 127; */
	if (access(shell->s_current->cmd_path, X_OK) == -1)
	{
		if (shell->s_current->cmd_path[0] == '.')
			shell->err = 126;
		else
			shell->err = 127;
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

void	join_path(t_shell *shell, t_second *s_current, char *path)
{
	char	*part_path;

	part_path = NULL;
	if (!ft_strncmp(s_current->cmd, "/", 1))
	{
		s_current->cmd_path = ft_strdup(s_current->cmd);
		if (!s_current->cmd_path)
			malloc_error(shell);
		return ;
	}
	part_path = ft_strjoin(path, "/");
	if (!part_path)
		malloc_error(shell);
	s_current->cmd_path = ft_strjoin(part_path, s_current->cmd);
	if (!s_current->cmd_path)
		malloc_error(shell);
	free(part_path);
}
