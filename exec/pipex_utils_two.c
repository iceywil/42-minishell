/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:40 by codespace         #+#    #+#             */
/*   Updated: 2024/12/10 09:13:43 by a                ###   ########.fr       */
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
		print_err(shell->s_current->redir_current->line,
			": No such file or directory", 0, 0);
		return (1);
	}
	if (access(shell->s_current->redir_current->line, R_OK) == -1)
	{
		print_err(shell->s_current->redir_current->line, ": Permission denied",
			0, 0);
		return (1);
	}
	shell->s_current->infile = open(shell->s_current->redir_current->line,
			O_RDONLY, 0777);
	if (shell->s_current->infile == -1)
	{
		print_err(shell->s_current->redir_current->line, ": Can't open", 0, 0);
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
			print_err(line, ": Permission denied", 0, 0);
			return (1);
		}
	}
	else
	{
		shell->s_current->outfile = open(line, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (shell->s_current->outfile == -1)
		{
			print_err(line, ": Can't open", 0, 0);
			return (1);
		}
	}
	return (0);
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
			print_err(line, ": Permission denied", 0, 0);
			return (1);
		}
	}
	else
	{
		shell->s_current->outfile = open(line, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (shell->s_current->outfile == -1)
			return (print_err(line, ": Can't open", 0, 0), 1);
	}
	return (0);
}
