/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:34:23 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 13:43:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exev(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	if (!shell->paths[shell->x])
		(ft_putendl_fd("Command not found", 2), free_shell(shell));
	else if (access(shell->paths[shell->x], F_OK) == -1)
	{
		if (shell->cmd_args[shell->x][0][0] == '/'
			|| shell->cmd_args[shell->x][0][0] == '.')
			(ft_putendl_fd("No such file or directory", 2),
				free_shell(shell));
		else
			(ft_putendl_fd("Command not found", 2), free_shell(shell));
	}
	else if (access(shell->paths[shell->x], X_OK) == -1)
		(ft_putendl_fd("Permission denied", 2), free_shell(shell));
	else
	{
		i = execve(shell->paths[shell->x], shell->cmd_args[shell->x], envp);
		if (i == -1)
			ft_putendl_fd("Command error", 2);
	}
}

void	check_access(t_shell *shell)
{
	shell->err = 0;
	if (!shell->paths[shell->x])
		shell->err = 127;
	else if (access(shell->paths[shell->x], X_OK) == -1)
	{
		if (shell->cmd_args[shell->x][0][0] == '.')
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
	fds = malloc(sizeof(int *) * (shell->args + 1));
	if (!fds)
		malloc_error(shell);
	while (i < shell->args)
	{
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
	pids = malloc(sizeof(int) * (shell->args + 1));
	if (!pids)
		malloc_error(shell);
	while (i < shell->args + 1)
	{
		pids[i] = 0;
		i++;
	}
	shell->pids = pids;
}

void	join_path(t_shell *shell, int i, int j)
{
	char	*part_path;

	while (shell->cmd_paths[i])
	{
		if (ft_strchr(shell->cmd_args[j][0], '/'))
		{
			shell->paths[j] = ft_strdup(shell->cmd_args[j][0]);
			if (!shell->paths[j])
				malloc_error(shell);
			return ;
		}
		if (shell->paths[j])
			(free(shell->paths[j]), shell->paths[j] = NULL);
		part_path = ft_strjoin(shell->cmd_paths[i++], "/");
		if (!part_path)
			(ft_free_double_tab(&shell->cmd_paths), malloc_error(shell));
		shell->paths[j] = ft_strjoin(part_path, shell->cmd_args[j][0]);
		if (!shell->paths[j])
			(ft_free_double_tab(&shell->cmd_paths), malloc_error(shell));
		free(part_path);
		if (access(shell->paths[j], F_OK) == 0)
			return ;
	}
}
