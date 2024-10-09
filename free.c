/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:10:56 by codespace         #+#    #+#             */
/*   Updated: 2024/10/08 18:39:07 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cwd)
			free(shell->cwd);
		/* if (shell->line)
			free(shell->line); */
	}
	free_pipex(shell);
	exit(shell->excode);
}

void	check_exit(t_shell *shell)
{
	if (ft_strncmp(shell->line, "exit", 4) == 0)
	{
		shell->excode = 0;
		free_shell(shell);
	}
}

void	error_exit(t_shell *shell, char *msg, int error)
{
	ft_putendl_fd(msg, 2);
	free_shell(shell);
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
