/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 03:16:31 by codespace         #+#    #+#             */
/*   Updated: 2025/01/06 03:36:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_files(t_shell *shell)
{
	shell->s_current = shell->s_head;
	shell->s_current->redir_current = shell->s_current->redir_head;
	while (shell->s_current->redir_current)
	{
		if (!ft_strcmp(shell->s_current->redir_current->token, "<"))
			check_infile(shell);
		else if (!ft_strcmp(shell->s_current->redir_current->token, ">>"))
			check_outfile_append(shell);
		else if (!ft_strcmp(shell->s_current->redir_current->token, ">"))
			check_outfile(shell);
		shell->s_current->redir_current = shell->s_current->redir_current->next;
	}
}

void	check_infile(t_shell *shell)
{
	if (access(shell->s_current->redir_current->line, F_OK) == -1)
	{
		shell->excode = 1;
		return ;
	}
	if (access(shell->s_current->redir_current->line, R_OK) == -1)
	{
		shell->excode = 1;
		return ;
	}
	shell->s_current->infile = open(shell->s_current->redir_current->line,
			O_RDONLY, 0777);
	if (shell->s_current->infile == -1)
	{
		shell->excode = 1;
		return ;
	}
	else
	{
		close(shell->s_current->infile);
		shell->s_current->infile = -1;
	}
}

void	check_outfile(t_shell *shell)
{
	if (access(shell->s_current->redir_current->line, F_OK) == -1)
	{
		shell->excode = 1;
		return ;
	}
	if (access(shell->s_current->redir_current->line, W_OK) == -1)
	{
		shell->excode = 1;
		return ;
	}
	shell->s_current->outfile = open(shell->s_current->redir_current->line,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (shell->s_current->outfile == -1)
	{
		shell->excode = 1;
		return ;
	}
	else
	{
		close(shell->s_current->outfile);
		shell->s_current->outfile = -1;
	}
}

void	check_outfile_append(t_shell *shell)
{
	if (access(shell->s_current->redir_current->line, F_OK) == -1)
	{
		shell->excode = 1;
		return ;
	}
	if (access(shell->s_current->redir_current->line, W_OK) == -1)
	{
		shell->excode = 1;
		return ;
	}
	shell->s_current->outfile = open(shell->s_current->redir_current->line,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (shell->s_current->outfile == -1)
	{
		shell->excode = 1;
		return ;
	}
	else
	{
		close(shell->s_current->outfile);
		shell->s_current->outfile = -1;
	}
}
