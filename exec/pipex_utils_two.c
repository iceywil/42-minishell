/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/11 21:45:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_infile(t_shell *shell)
{
	if (shell->s_current->infile != -1)
		close(shell->s_current->infile);
	shell->s_current->infile = -1;
	if (access(shell->s_current->redir_current->line, F_OK) == -1)
	{
		print_err(shell->s_current->redir_current->line,
			": No such file or directory", 0);
		return (1);
	}
	if (access(shell->s_current->redir_current->line, R_OK) == -1)
	{
		print_err(shell->s_current->redir_current->line, ": Permission denied",
			0);
		return (1);
	}
	shell->s_current->infile = open(shell->s_current->redir_current->line,
			O_RDONLY, 0777);
	if (shell->s_current->infile == -1)
	{
		print_err(shell->s_current->redir_current->line, ": Can't open", 0);
		return (1);
	}
	return (0);
}

int	open_outfile_append(t_shell *shell)
{
	if (shell->s_current->outfile != -1)
		close(shell->s_current->outfile);
	shell->s_current->outfile = -1;
	if (access(shell->s_current->redir_current->line, F_OK) == 0)
	{
		shell->s_current->outfile = open(shell->s_current->redir_current->line,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->s_current->outfile == -1)
		{
			print_err(shell->s_current->redir_current->line,
				": Permission denied", 0);
			return (1);
		}
	}
	else
	{
		shell->s_current->outfile = open(shell->s_current->redir_current->line,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->s_current->outfile == -1)
		{
			print_err(shell->s_current->redir_current->line, ": Can't open", 0);
			return (1);
		}
	}
	return (0);
}

int	open_outfile(t_shell *shell)
{
	if (shell->s_current->outfile != -1)
		close(shell->s_current->outfile);
	shell->s_current->outfile = -1;
	if (access(shell->s_current->redir_current->line, F_OK) == 0)
	{
		shell->s_current->outfile = open(shell->s_current->redir_current->line,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->s_current->outfile == -1)
		{
			print_err(shell->s_current->redir_current->line,
				": Permission denied", 0);
			return (1);
		}
	}
	else
	{
		shell->s_current->outfile = open(shell->s_current->redir_current->line,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->s_current->outfile == -1)
		{
			print_err(shell->s_current->redir_current->line, ": Can't open", 0);
			return (1);
		}
	}
	return (0);
}

void	print_dup(char *cmd, char *msg)
{
	dup2(2, 1);
	printf("minishell: %s%s\n", cmd, msg);
	close(2);
}
