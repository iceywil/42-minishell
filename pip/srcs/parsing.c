/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:18:52 by wscherre          #+#    #+#             */
/*   Updated: 2024/04/19 20:58:05 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_paths(t_main *pipex, char **envp)
{
	int		i;
	char	*first;

	i = 0;
	pipex->unset = 0;
	pipex->filein = 0;
	pipex->fileout = 0;
	if (!envp || !envp[0] || !envp[0][0])
		return ;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
	{
		pipex->unset = 1;
		return ;
	}
	pipex->cmd_paths = ft_split(envp[i], ':');
	if (!pipex->cmd_paths)
		malloc_error(pipex);
	first = ft_strtrim(pipex->cmd_paths[0], "PATH=");
	free(pipex->cmd_paths[0]);
	pipex->cmd_paths[0] = first;
}

void	parse_args(t_main *pipex, char **argv, int argc, int i)
{
	int	x;

	if (pipex->here == 1)
		pipex->args = argc - 4;
	else
		pipex->args = argc - 3;
	envp_check(pipex, argv);
	pipex->paths = malloc(sizeof(char *) * (pipex->args + 1));
	if (!pipex->paths)
		malloc_error(pipex);
	pipex->cmd_args = malloc(sizeof(char **) * (pipex->args + 1));
	if (!pipex->cmd_args)
		malloc_error(pipex);
	x = 0;
	while (i < pipex->argc - 1)
	{
		pipex->cmd_args[x] = NULL;
		pipex->cmd_args[x] = ft_split(argv[i], ' ');
		if (!pipex->cmd_args[x])
			malloc_error(pipex);
		i++;
		x++;
	}
	pipex->cmd_args[x] = NULL;
}

void	envp_check(t_main *pipex, char **argv)
{
	int	i;
	int	y;

	i = 0;
	if (pipex->here == 1)
		y = 3;
	else
		y = 2;
	if (!pipex->cmd_paths)
	{
		pipex->cmd_paths = malloc(sizeof(char *) * (pipex->args + 1));
		pipex->cmd_paths[pipex->args] = NULL;
		while (i < pipex->args)
			pipex->cmd_paths[i++] = NULL;
		i = 0;
		envp_loop(pipex, argv, i, y);
	}
}

void	envp_loop(t_main *pipex, char **argv, int i, int y)
{
	while (i < pipex->args)
	{
		if (argv[y][0] == '/' && access(argv[y], F_OK) == 0 && access(argv[y],
				X_OK) == 0)
		{
			pipex->cmd_paths[i] = malloc(sizeof(char));
			pipex->cmd_paths[i][0] = '\0';
			i++;
		}
		else
		{
			pipex->err = 127;
			if (pipex->unset == 1)
			{
				ft_putendl_fd("Command not found", 2);
				ft_putendl_fd("Command not found", 2);
			}
			free_all_exit(pipex);
		}
		y++;
	}
}

void	parse_paths(t_main *pipex)
{
	int	i;
	int	j;

	j = 0;
	pipex->paths[pipex->args] = NULL;
	while (pipex->cmd_args[j])
	{
		pipex->paths[j] = NULL;
		i = 0;
		if (!pipex->cmd_args[j][0])
			pipex->paths[j] = NULL;
		else
			join_path(pipex, i, j);
		j++;
	}
}
