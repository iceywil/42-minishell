/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:10:56 by codespace         #+#    #+#             */
/*   Updated: 2024/12/06 22:17:47 by a                ###   ########.fr       */
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
		if (shell->paths)
			ft_free_double_tab(&shell->paths);
		if (shell->fds)
		{
			i = 0;
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

void	print_err(char *word, char *msg, char redir, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(word, 2);
		ft_putendl_fd(msg, 2);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(msg, 2);
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

void	free_first(t_shell *shell)
{
	t_first	*current;
	t_first	*next;

	current = shell->f_head;
	while (current)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
	shell->f_head = NULL;
	shell->f_current = NULL;
}
