/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delims.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 02:10:24 by codespace         #+#    #+#             */
/*   Updated: 2025/01/16 15:52:12 by codespace        ###   ########.fr       */
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

int	handle_heredoc(t_shell *shell, t_second *current)
{
	t_first	*redir;

	while (current)
	{
		redir = current->redir_head;
		while (redir)
		{
			if (!ft_strcmp(redir->token, "<<"))
			{
				ft_sig_heredoc();
				if (here_doc(shell, redir))
					return (1);
				ft_signals();
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

int	here_doc(t_shell *shell, t_first *redir)
{
	char	*str;
	int		fd;

	fd = open("/tmp/.here_doc_a", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!fd)
		(print_err("open: ", "/tmp/.here_doc_a", 1), exit(1));
	shell->fd2 = dup(STDIN_FILENO);
	str = readline("> ");
	while (str && ft_strcmp(redir->line, str))
		(ft_putendl_fd(str, fd), free(str), str = readline("> "));
	free(str);
	if (ctrlc(shell, fd))
		return (1);
	close(fd);
	close(shell->fd2);
	return (0);
}

int	ctrlc(t_shell *shell, int fd)
{
	if (g_sig == SIGINT)
	{
		shell->excode = 130;
		g_sig = 0;
		close(fd);
		dup2(shell->fd2, STDIN_FILENO);
		shell->fd0 = 0;
		unlink("/tmp/.here_doc_a");
		shell->tmpexcode = 130;
		return (1);
	}
	return (0);
}
