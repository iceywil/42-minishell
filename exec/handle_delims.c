/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delims.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/11/26 22:10:19 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirs(t_shell *shell)
{
	shell->i = 0;
	shell->s_current->redir_current = shell->s_current->redir_head;
	while (shell->s_current->redir_current)
	{
		if (!ft_strcmp(shell->s_current->redir_current->token, "<"))
			shell->i = open_infile(shell);
		else if (!ft_strcmp(shell->s_current->redir_current->token, ">>"))
			shell->i = open_outfile_append(shell);
		else if (!ft_strcmp(shell->s_current->redir_current->token, ">"))
			shell->i = open_outfile(shell);
		if (shell->i)
			return (1);
		if (shell->s_current->redir_current->outfile)
		{
			dup_fd(shell, shell->s_current->redir_current->outfile,
				STDOUT_FILENO);
			close(shell->s_current->redir_current->outfile);
		}
		shell->s_current->redir_current = shell->s_current->redir_current->next;
	}
	if (shell->s_current->heredoc)
		shell->s_current->filein = open(shell->s_current->heredoc, O_RDONLY);
	else if (shell->s_current->infile != -1)
		shell->s_current->filein = shell->s_current->infile;
	return (0);
}

void	handle_heredoc(t_shell *shell, t_second *current)
{
	t_first	*redir;
	int		tmp;
	char	*str;

	while (current)
	{
		redir = current->redir_head;
		while (redir)
		{
			if (ft_strcmp(redir->token, "<<"))
			{
				current->heredoc = ft_strdup("/tmp/.here_doc_a");
				if (!current->heredoc)
					malloc_error(shell);
				tmp = open(current->heredoc, O_WRONLY | O_CREAT | O_TRUNC,
						0777);
				str = readline("> ");
				while (str && ft_strcmp(redir->line, str))
					(ft_putendl_fd(str, tmp), free(str), str = readline("> "));
				close(tmp);
			}
			redir = redir->next;
		}
		current = current->next;
	}
}

void	handle_input(t_shell *shell)
{
	t_first		*redir;
	t_second	*current;
	int			tmp;
	char		*str;

	redir = shell->s_current->redir_current;
	current = shell->s_current;
}

void	handle_output(t_shell *shell)
{
	t_first		*redir;
	t_second	*current;

	redir = shell->s_current->redir_head;
	current = shell->s_current;
	while (redir)
	{
		if (!ft_strcmp(redir->token, ">") || !ft_strcmp(redir->token, ">>"))
			dup_fd(shell, redir->outfile, STDOUT_FILENO);
		redir = redir->next;
	}
}
