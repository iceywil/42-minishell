/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:40 by codespace         #+#    #+#             */
/*   Updated: 2024/12/05 01:14:39 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_infile(t_shell *shell)
{
	if (shell->s_current->infile)
		close(shell->s_current->infile);
	shell->s_current->infile = -1;
	if (access(shell->s_current->redir_current->line, F_OK) == -1)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(shell->s_current->redir_current->line, 2);
		return (1);
	}
	if (access(shell->s_current->redir_current->line, R_OK) == -1)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(shell->s_current->redir_current->line, 2);
		return (1);
	}
	shell->s_current->infile = open(shell->s_current->redir_current->line,
			O_RDONLY, 0777);
	if (shell->s_current->infile == -1)
	{
		ft_putstr_fd("minishell: can't open ", 2);
		ft_putendl_fd(shell->s_current->redir_current->line, 2);
		return (1);
	}
	return (0);
}

int	open_outfile_append(t_shell *shell)
{
	char	*line;

	line = shell->s_current->redir_current->line;
	if (shell->s_current->outfile)
		close(shell->s_current->outfile);
	shell->s_current->outfile = -1;
	if (access(line, F_OK) == 0)
	{
		shell->s_current->outfile = open(line, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (shell->s_current->outfile == -1)
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			return (ft_putendl_fd(line, 2), 1);
		}
	}
	else
	{
		shell->s_current->outfile = open(line, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (shell->s_current->outfile == -1)
			return (ft_putstr_fd("minishell: can't open: ", 2),
				ft_putendl_fd(line, 2), 1);
	}
	return (0);
}

void	check_outfile(t_shell *shell)
{
	/* if (access(argv[shell->argc - 1], F_OK) == 0)
	{
		if (access(argv[shell->argc - 1], R_OK | W_OK) == -1)
			shell->err = 1;
	} */
}

int	open_outfile(t_shell *shell)
{
	char	*line;

	line = shell->s_current->redir_current->line;
	if (shell->s_current->outfile)
		close(shell->s_current->outfile);
	shell->s_current->outfile = -1;
	if (access(line, F_OK) == 0)
	{
		shell->s_current->outfile = open(line, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (shell->s_current->outfile == -1)
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			return (ft_putendl_fd(shell->s_current->redir_current->line, 2), 1);
		}
	}
	else
	{
		shell->s_current->outfile = open(line, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (shell->s_current->outfile == -1)
			return (ft_putstr_fd("minishell: can't open ", 2),
				ft_putendl_fd(shell->s_current->redir_current->line, 2), 1);
	}
	return (0);
}
