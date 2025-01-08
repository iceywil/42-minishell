/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delims.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 16:54:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirs(t_shell *shell)
{
	shell->x = 0;
	shell->s_current->redir_current = shell->s_current->redir_head;
	while (shell->s_current->redir_current)
	{
		if (!ft_strcmp(shell->s_current->redir_current->token, "<"))
			shell->x = open_infile(shell);
		else if (!ft_strcmp(shell->s_current->redir_current->token, ">>"))
			shell->x = open_outfile_append(shell);
		else if (!ft_strcmp(shell->s_current->redir_current->token, ">"))
			shell->x = open_outfile(shell);
		else if (!ft_strcmp(shell->s_current->redir_current->token, "<<"))
		{
			if (shell->s_current->infile != -1)
				close(shell->s_current->infile);
			shell->s_current->infile = open("/tmp/.here_doc_a", O_RDONLY);
		}
		if (shell->x)
			return (close_files(shell), 1);
		shell->s_current->redir_current = shell->s_current->redir_current->next;
	}
	return (0);
}

void	close_files(t_shell *shell)
{
	if (shell->s_current->infile != -1)
		close(shell->s_current->infile);
	if (shell->s_current->outfile != -1)
		close(shell->s_current->outfile);
}

void	handle_heredoc(t_second *current)
{
	t_first	*redir;
	int		tmp;
	char	*str;

	while (current)
	{
		redir = current->redir_head;
		while (redir)
		{
			if (!ft_strcmp(redir->token, "<<"))
			{
				ft_sig_heredoc();
				tmp = open("/tmp/.here_doc_a", O_WRONLY | O_CREAT | O_TRUNC,
						0777);
				str = readline("> ");
				while (str && ft_strcmp(redir->line, str))
					(ft_putendl_fd(str, tmp), free(str), str = readline("> "));
				close(tmp);
				ft_signals();
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
