/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/09/12 12:56:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
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
# include <limits.h>

typedef struct s_main
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
}			t_main;

typedef struct s_shell
{
	char	*cwd;
	int		excode;
}			t_shell;

static char	*create_buffer(void);
void		parsing(void);
void		exec(int argc, char **argv, char **envp);

void free_shell(t_shell *shell);


void		get_paths(t_main *pipex, char **envp);
void		parse_args(t_main *pipex, char **argv, int argc, int i);
void		parse_paths(t_main *pipex);
void		join_path(t_main *pipex, int i, int j);
void		envp_check(t_main *pipex, char **argv);
void		envp_loop(t_main *pipex, char **argv, int i, int y);
// int			get_heredoc(t_main *pipex);

// void		exec(t_main *pipex, char **envp, char **argv);
void		here_doc(t_main *pipex, char **envp, char **argv);
void		doc_pipe(t_main *pipex, char **argv);
void		dup_fd(t_main *pipex, int fd1, int fd2);
void		check_access(t_main *pipex);

void		first_cmd(t_main *pipex, char **envp, char **argv);
void		mid_cmd(t_main *pipex, char **envp);
void		last_cmd(t_main *pipex, char **envp, char **argv);
void		exev(t_main *pipex, char **envp);
void		create_own_pipes(t_main *pipex);
void		close_own_pipes(t_main *pipex);
void		wait_childrens(void);
void		close_last_pipes(t_main *pipex);
void		malloc_fds(t_main *pipex);
void		malloc_pids(t_main *pipex);

void		check_outfile(t_main *pipex, char **argv);
void		open_infile(t_main *pipex, char **argv);
void		open_outfile(t_main *pipex, char **argv);
void		open_outfile_here(t_main *pipex, char **argv);

void		error_exit(t_main *pipex, char *msg, int error);
void		free_all_exit(t_main *pipex);
void		malloc_error(t_main *pipex);
void		free_all(t_main *pipex);

#endif
