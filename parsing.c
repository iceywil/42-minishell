/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:44:15 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 13:43:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	get_paths(t_shell *shell, char **envp)
{
	int		i;
	char	*first;

	i = 0;
	shell->unset = 0;
	shell->filein = 0;
	shell->fileout = 0;
	if (!envp || !envp[0] || !envp[0][0])
		return ;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
	{
		shell->unset = 1;
		return ;
	}
	shell->cmd_paths = ft_split(envp[i], ':');
	if (!shell->cmd_paths)
		malloc_error(shell);
	first = ft_strtrim(shell->cmd_paths[0], "PATH=");
	free(shell->cmd_paths[0]);
	shell->cmd_paths[0] = first;
}

void	parse_args(t_shell *shell, char **argv, int argc, int i)
{
	int	x;

	if (shell->here == 1)
		shell->args = argc - 4;
	else
		shell->args = argc - 3;
	envp_check(shell, argv);
	shell->paths = malloc(sizeof(char *) * (shell->args + 1));
	if (!shell->paths)
		malloc_error(shell);
	shell->cmd_args = malloc(sizeof(char **) * (shell->args + 1));
	if (!shell->cmd_args)
		malloc_error(shell);
	x = 0;
	while (i < shell->argc - 1)
	{
		shell->cmd_args[x] = NULL;
		shell->cmd_args[x] = ft_split(argv[i], ' ');
		if (!shell->cmd_args[x])
			malloc_error(shell);
		i++;
		x++;
	}
	shell->cmd_args[x] = NULL;
}

void	envp_check(t_shell *shell, char **argv)
{
	int	i;
	int	y;

	i = 0;
	if (shell->here == 1)
		y = 3;
	else
		y = 2;
	if (!shell->cmd_paths)
	{
		shell->cmd_paths = malloc(sizeof(char *) * (shell->args + 1));
		shell->cmd_paths[shell->args] = NULL;
		while (i < shell->args)
			shell->cmd_paths[i++] = NULL;
		i = 0;
		envp_loop(shell, argv, i, y);
	}
}

void	envp_loop(t_shell *shell, char **argv, int i, int y)
{
	while (i < shell->args)
	{
		if (argv[y][0] == '/' && access(argv[y], F_OK) == 0 && access(argv[y],
				X_OK) == 0)
		{
			shell->cmd_paths[i] = malloc(sizeof(char));
			shell->cmd_paths[i][0] = '\0';
			i++;
		}
		else
		{
			shell->err = 127;
			if (shell->unset == 1)
			{
				ft_putendl_fd("Command not found", 2);
				ft_putendl_fd("Command not found", 2);
			}
			free_shell(shell);
		}
		y++;
	}
}

void	parse_paths(t_shell *shell)
{
	int	i;
	int	j;

	j = 0;
	shell->paths[shell->args] = NULL;
	while (shell->cmd_args[j])
	{
		shell->paths[j] = NULL;
		i = 0;
		if (!shell->cmd_args[j][0])
			shell->paths[j] = NULL;
		else
			join_path(shell, i, j);
		j++;
	}
}
