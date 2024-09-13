/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:10:56 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 14:58:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cwd)
			free(shell->cwd);
	}
	free_shell(shell);
	exit(shell->excode);
}

void check_exit(char *line, t_shell *shell)
{
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		shell->excode = 0;
		free(line);
		free_shell(shell);
	}
}

void	error_exit(t_shell *shell, char *msg, int error)
{
	free_shell(shell);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(error);
}


void	free_pipex(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell)
	{
		if (shell->cmd_paths)
			ft_free_double_tab(&shell->cmd_paths);
		if (shell->cmd_args)
		{
			while (shell->cmd_args[i])
				ft_free_double_tab(&shell->cmd_args[i++]);
			free(shell->cmd_args);
		}
		if (shell->paths)
			ft_free_double_tab(&shell->paths);
		if (shell->fds)
		{
			i = 0;
			while (i < shell->args)
				free(shell->fds[i++]);
			free(shell->fds);
		}
		if (shell->pids)
			free(shell->pids);
	}
}

void	malloc_error(t_shell *shell)
{
	free_shell(shell);
	ft_putendl_fd("Malloc Error", 2);
	exit(0);
}
