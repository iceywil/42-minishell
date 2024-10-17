/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:10:56 by codespace         #+#    #+#             */
/*   Updated: 2024/10/15 18:31:58 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cwd)
			free(shell->cwd);
		if (shell->line)
			free(shell->line);
		if (shell->env)
			ft_free_double_tab(&shell->env);
	}
	// free_pipex(shell);
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

void	malloc_error(t_shell *shell)
{
	ft_putendl_fd("Malloc error", 2);
	free_shell(shell);
}

void	print_err(char *msg, char *word, char redir, int flag)
{
	if (flag == 0)
	{
		printf("minishell: %s\n", msg);
	}
	else if (flag == 1)
	{
		printf("minishell: %s: %s\n", word, msg);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd(redir, 2);
		ft_putendl_fd("'", 2);
	}
	else if (flag == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd(redir, 2);
		ft_putchar_fd(redir, 2);
		ft_putendl_fd("'", 2);
	}
}
