/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/17 22:02:35 by a                ###   ########.fr       */
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

# define PIPE '|'
# define DOUBLE_PIPE "||"
# define LEFT '<'
# define RIGHT '>'
# define DOUBLE_LEFT "<<"
# define DOUBLE_RIGHT ">>"
# define AND '&'
# define DOUBLE_AND "&&"

typedef struct s_command
{
	int					i;
	char				*prev_token;
	char				*delim;
	char				*cmd;
	char				**args;
	char				*next_token;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_shell
{
	int					x;
	int					err;
	int					unset;
	// Pipex
	int					**fds;
	int					*pids;
	int					args;
	int					argc;
	int					here;
	int					filein;
	int					fileout;
	char				**paths;
	char				**cmd_paths;
	char				***cmd_args;
	// Minishell
	int					excode;
	char				*line;
	// Parser
	t_command			*head;
	t_command			*current;
	// Env
	char				*cwd;
	char				**env;

}						t_shell;

// MAIN
char					*create_buffer(void);

// PARSER
void					replace_quotes(char *input);
int						is_token(char c);
int					parse_input(t_shell *shell, char *input);
char					**split_cmd(char *cmd);
char					**split_loop(char **result, char *cmd, int i,
							int count);
static int				count_args(char *cmd);

// CHECKS
int						parsing(t_shell *shell);
int						check_open_quotes(t_shell *shell, char *input,
							int flag);

// FREE EXIT
void					free_shell(t_shell *shell);
void					check_exit(t_shell *shell);
void					free_pipex(t_shell *shell);
void					error_exit(t_shell *shell, char *msg, int error);
void					malloc_error(t_shell *shell);
void					print_err(char *msg, char *word, char redir, int flag);

// PIPEX
void					pipex(t_shell *shell, int argc, char **argv,
							char **envp);
void					get_paths(t_shell *shell, char **envp);
void					parse_args(t_shell *shell, char **argv, int argc,
							int i);
void					parse_paths(t_shell *shell);
void					join_path(t_shell *shell, int i, int j);
void					envp_check(t_shell *shell, char **argv);
void					envp_loop(t_shell *shell, char **argv, int i, int y);
// int			get_heredoc(t_shell *shell);
// void		exec(t_shell *shell, char **envp, char **argv);
void					here_doc(t_shell *shell, char **envp, char **argv);
void					dup_fd(t_shell *shell, int fd1, int fd2);
void					check_access(t_shell *shell);
void					first_cmd(t_shell *shell, char **envp, char **argv);
void					mid_cmd(t_shell *shell, char **envp);
void					last_cmd(t_shell *shell, char **envp, char **argv);
void					exev(t_shell *shell, char **envp);
void					create_own_pipes(t_shell *shell);
void					close_own_pipes(t_shell *shell);
void					wait_childrens(void);
void					close_last_pipes(t_shell *shell);
void					malloc_fds(t_shell *shell);
void					malloc_pids(t_shell *shell);
void					check_outfile(t_shell *shell, char **argv);
void					open_infile(t_shell *shell, char **argv);
void					open_outfile(t_shell *shell, char **argv);
void					open_outfile_here(t_shell *shell, char **argv);

#endif
