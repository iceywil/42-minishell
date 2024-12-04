/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:34:23 by codespace         #+#    #+#             */
/*   Updated: 2024/11/27 21:36:44 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exev(t_shell *shell, char **envp)
{
	if (!shell->s_current->cmd_path)
	{
		ft_printf("bash: %s: command not found\n", shell->s_current->cmd);
		free_shell(shell);
		exit(127);
	}
	else if (access(shell->s_current->cmd_path, F_OK) == -1)
	{
		ft_putendl_fd("No such file or directory", 2);
		free_shell(shell);
		exit(127);
	}
	else if (access(shell->s_current->cmd_path, X_OK) == -1)
	{
		ft_putendl_fd("Permission denied", 2);
		free_shell(shell);
		exit(126);
	}
	else
	{
		if (execve(shell->s_current->cmd_path, shell->s_current->args, envp) == -1)
		{
			ft_putendl_fd("Command error", 2);
			free_shell(shell);
			exit(1);
		}
	}
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

void	malloc_pids(t_shell *shell)
{
	int	*pids;
	int	i;

	i = 0;
	pids = NULL;
	pids = malloc(sizeof(int) * (shell->cmd_nbr + 1));
	if (!pids)
		malloc_error(shell);
	while (i < shell->cmd_nbr + 1)
	{
		pids[i] = 0;
		i++;
	}
	shell->pids = pids;
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
