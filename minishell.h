/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/24 18:51:10 by a                ###   ########.fr       */
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

# define TOKEN_M "syntax error near unexpected token `"
# define NEWLINE_M "syntax error near unexpected token `newline'"
# define LEFT_M "syntax error near unexpected token `<'"
# define RIGHT_M "syntax error near unexpected token `>'"
# define DOUBLE_LEFT_M "syntax error near unexpected token `<<'"
# define DOUBLE_RIGHT_M "syntax error near unexpected token `>>'"
# define PIPE_M "syntax error near unexpected token `|'"
# define DOUBLE_PIPE_M "syntax error near unexpected token `||'"
# define DIRECTORY_M "Is a directory"
# define AND_M "syntax error near unexpected token `&'"
# define DOUBLE_AND_M "syntax error near unexpected token `&&'"

# define PIPE "|"
# define DOUBLE_PIPE "||"
# define LEFT "<"
# define RIGHT ">"
# define DOUBLE_LEFT "<<"
# define DOUBLE_RIGHT ">>"


typedef struct t_first
{
	int				i;
	char			*line;
	int				cmd;
	struct t_first	*next;
}					t_first;

typedef struct t_second
{
	char			*prev_token;
	char			*delim;
	char			*cmd;
	char			**args;
	char			*next_token;
	struct t_second	*next;
	struct t_second	*prev;
}					t_second;

typedef struct s_shell
{
	int				i;
	int				x;
	// Pipex
	int				unset;
	int				err;
	int				**fds;
	int				*pids;
	int				args;
	int				argc;
	int				here;
	int				filein;
	int				fileout;
	char			**paths;
	char			**cmd_paths;
	char			***cmd_args;
	// Minishell
	int				excode;
	char			*line;
	// Parser
	t_first			*f_head;
	t_first			*f_current;
	t_second		*s_head;
	t_second		*s_current;

	// Env
	char			*cwd;
	char			**env;

}					t_shell;

// MAIN
char				*create_buffer(void);
void				init_all(t_shell *shell);

// PARSING
int					parsing(t_shell *shell);
void				check_token_legit(t_shell *shell);
void				check_token_fill(t_shell *shell);

// utils
int					is_token(char c);
int					check_open_quotes(t_shell *shell, char *input, int flag);
int					count_args(char *cmd);

// first parser
void				f_split_input(t_shell *shell, char *input);
int					f_split_loop(t_shell *shell, char *input, int start, int i);
void				f_add_node(t_shell *shell, char *line, int cmd);
int					f_no_quotes(t_shell *shell, char *input, int start, int i);
char				*f_handle_env_cmd(t_shell *shell, char *line);

// second parser
void				s_parsing(t_shell *shell);
void				s_parsing_token(t_shell *shell, t_second *second,
						char *line);
void				clean_empty_and_quotes(t_shell *shell, t_first *current);
void				remove_side_quotes(char *str);
void				clean_first(t_shell *shell);
t_second			*s_create_node(t_shell *shell);
void				s_args_loop(t_shell *shell);

// FREE EXIT
void				free_shell(t_shell *shell);
void				check_exit(t_shell *shell);
void				free_pipex(t_shell *shell);
void				error_exit(t_shell *shell, char *msg, int error);
void				malloc_error(t_shell *shell);
void				print_err(char *msg, char *word, char redir, int flag);

// PIPEX
void				pipex(t_shell *shell, int argc, char **argv, char **envp);
void				get_paths(t_shell *shell, char **envp);
void				parse_args(t_shell *shell, char **argv, int argc, int i);
void				parse_paths(t_shell *shell);
void				join_path(t_shell *shell, int i, int j);
void				envp_check(t_shell *shell, char **argv);
void				envp_loop(t_shell *shell, char **argv, int i, int y);
// int			get_heredoc(t_shell *shell);
// void		exec(t_shell *shell, char **envp, char **argv);
void				here_doc(t_shell *shell, char **envp, char **argv);
void				dup_fd(t_shell *shell, int fd1, int fd2);
void				check_access(t_shell *shell);
void				first_cmd(t_shell *shell, char **envp, char **argv);
void				mid_cmd(t_shell *shell, char **envp);
void				last_cmd(t_shell *shell, char **envp, char **argv);
void				exev(t_shell *shell, char **envp);
void				create_own_pipes(t_shell *shell);
void				close_own_pipes(t_shell *shell);
void				wait_childrens(void);
void				close_last_pipes(t_shell *shell);
void				malloc_fds(t_shell *shell);
void				malloc_pids(t_shell *shell);
void				check_outfile(t_shell *shell, char **argv);
void				open_infile(t_shell *shell, char **argv);
void				open_outfile(t_shell *shell, char **argv);
void				open_outfile_here(t_shell *shell, char **argv);

#endif
