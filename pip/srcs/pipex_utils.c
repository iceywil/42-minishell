/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:32 by wscherre          #+#    #+#             */
/*   Updated: 2024/04/25 15:05:30 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exev(t_main *pipex, char **envp)
{
	int	i;

	i = 0;
	if (!pipex->paths[pipex->x])
		(ft_putendl_fd("Command not found", 2), free_all_exit(pipex));
	else if (access(pipex->paths[pipex->x], F_OK) == -1)
	{
		if (pipex->cmd_args[pipex->x][0][0] == '/'
			|| pipex->cmd_args[pipex->x][0][0] == '.')
			(ft_putendl_fd("No such file or directory", 2),
				free_all_exit(pipex));
		else
			(ft_putendl_fd("Command not found", 2), free_all_exit(pipex));
	}
	else if (access(pipex->paths[pipex->x], X_OK) == -1)
		(ft_putendl_fd("Permission denied", 2), free_all_exit(pipex));
	else
	{
		i = execve(pipex->paths[pipex->x], pipex->cmd_args[pipex->x], envp);
		if (i == -1)
			ft_putendl_fd("Command error", 2);
	}
}

void	check_access(t_main *pipex)
{
	pipex->err = 0;
	if (!pipex->paths[pipex->x])
		pipex->err = 127;
	else if (access(pipex->paths[pipex->x], X_OK) == -1)
	{
		if (pipex->cmd_args[pipex->x][0][0] == '.')
			pipex->err = 126;
		else
			pipex->err = 127;
	}
}

void	malloc_fds(t_main *pipex)
{
	int	**fds;
	int	i;

	i = 0;
	fds = malloc(sizeof(int *) * (pipex->args + 1));
	if (!fds)
		malloc_error(pipex);
	while (i < pipex->args)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			malloc_error(pipex);
		fds[i][0] = -1;
		fds[i][1] = -1;
		i++;
	}
	fds[i] = NULL;
	pipex->fds = fds;
}

void	malloc_pids(t_main *pipex)
{
	int	*pids;
	int	i;

	i = 0;
	pids = malloc(sizeof(int) * (pipex->args + 1));
	if (!pids)
		malloc_error(pipex);
	while (i < pipex->args + 1)
	{
		pids[i] = 0;
		i++;
	}
	pipex->pids = pids;
}

void	join_path(t_main *pipex, int i, int j)
{
	char	*part_path;

	while (pipex->cmd_paths[i])
	{
		if (ft_strchr(pipex->cmd_args[j][0], '/'))
		{
			pipex->paths[j] = ft_strdup(pipex->cmd_args[j][0]);
			if (!pipex->paths[j])
				malloc_error(pipex);
			return ;
		}
		if (pipex->paths[j])
			(free(pipex->paths[j]), pipex->paths[j] = NULL);
		part_path = ft_strjoin(pipex->cmd_paths[i++], "/");
		if (!part_path)
			(ft_free_double_tab(&pipex->cmd_paths), malloc_error(pipex));
		pipex->paths[j] = ft_strjoin(part_path, pipex->cmd_args[j][0]);
		if (!pipex->paths[j])
			(ft_free_double_tab(&pipex->cmd_paths), malloc_error(pipex));
		free(part_path);
		if (access(pipex->paths[j], F_OK) == 0)
			return ;
	}
}
