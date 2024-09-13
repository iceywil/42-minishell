/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/09/13 15:15:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_shell
{
	int		x;
	int		err;
	int		unset;
	int		**fds;
	int		*pids;
	int		args;
	int		argc;
	int		here;
	int		filein;
	int		fileout;
	char	**paths;
	char	**cmd_paths;
	char	***cmd_args;
	char	*cwd;
	int		excode;
}			t_shell;

static char	*create_buffer(void);
void		parsing(void);

void		pipex(t_shell *shell, int argc, char **argv, char **envp);

void		free_shell(t_shell *shell);
void		check_exit(char *line, t_shell *shell);
void		free_pipex(t_shell *shell);

void		get_paths(t_shell *shell, char **envp);
void		parse_args(t_shell *shell, char **argv, int argc, int i);
void		parse_paths(t_shell *shell);
void		join_path(t_shell *shell, int i, int j);
void		envp_check(t_shell *shell, char **argv);
void		envp_loop(t_shell *shell, char **argv, int i, int y);
// int			get_heredoc(t_shell *shell);

// void		exec(t_shell *shell, char **envp, char **argv);
void		here_doc(t_shell *shell, char **envp, char **argv);
void		dup_fd(t_shell *shell, int fd1, int fd2);
void		check_access(t_shell *shell);

void		first_cmd(t_shell *shell, char **envp, char **argv);
void		mid_cmd(t_shell *shell, char **envp);
void		last_cmd(t_shell *shell, char **envp, char **argv);
void		exev(t_shell *shell, char **envp);
void		create_own_pipes(t_shell *shell);
void		close_own_pipes(t_shell *shell);
void		wait_childrens(void);
void		close_last_pipes(t_shell *shell);
void		malloc_fds(t_shell *shell);
void		malloc_pids(t_shell *shell);

void		check_outfile(t_shell *shell, char **argv);
void		open_infile(t_shell *shell, char **argv);
void		open_outfile(t_shell *shell, char **argv);
void		open_outfile_here(t_shell *shell, char **argv);

void		error_exit(t_shell *shell, char *msg, int error);
void		free_all_exit(t_shell *shell);
void		malloc_error(t_shell *shell);
void		free_all(t_shell *shell);

#endif
