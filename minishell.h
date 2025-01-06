/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2025/01/06 03:31:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define NEWLINE_M "syntax error near unexpected token `newline'\n"
# define DIRECTORY_M "Is a directory\n"

# define PIPE '|'
# define LEFT '<'
# define RIGHT '>'
# define DOUBLE_LEFT "<<"
# define DOUBLE_RIGHT ">>"

typedef struct t_first
{
	char				*token;
	char				*line;
	int					cmd;
	struct t_first		*prev;
	struct t_first		*next;
}						t_first;

typedef struct t_second
{
	int					i;
	char				*cmd;
	char				*cmd_path;
	char				**args;
	t_first				*args_head;
	t_first				*args_current;
	t_first				*redir_head;
	t_first				*redir_current;
	char				*heredoc;
	int					infile;
	int					outfile;
	struct t_second		*next;
	struct t_second		*prev;
}						t_second;

typedef struct s_env_list
{
	char				*key;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_shell
{
	int					i;
	int					unset;
	int					err;
	int					cmd_nbr;
	char				**paths;
	int					**fds;
	int					excode;
	char				*line;
	t_first				*f_head;
	t_first				*f_current;
	t_second			*s_head;
	t_second			*s_current;
	char				*cwd;
	t_env_list			*env_head;
	t_env_list			*env_current;
	char				**env_tab;
	int					switch_signal;
	int					tmpexcode;
	int					g_sig;
}						t_shell;

extern int				g_sig;

// MAIN
char					*create_buffer(t_shell *shell);
void					init_all(t_shell *shell);
void					init_all_start(t_shell *shell);
void					execute(t_shell *shell);
int						check_empty_line(t_shell *shell);

// PARSING
int						parsing(t_shell *shell);
int						check_token_legit(t_shell *shell, t_first *current);

// utils
int						is_token(char c);
int						check_open_quotes(t_shell *shell, char *input);
int						count_args(char *cmd);

// first parser
void					f_parsing(t_shell *shell, char *input);
int						f_split_loop(t_shell *shell, char *input, int start,
							int i);
void					f_add_node(t_shell *shell, char *line, int cmd);
int						f_no_quotes(t_shell *shell, char *input, int start,
							int i);
char					*f_handle_env_cmd(t_shell *shell, char *line);
int						f_handle_token(t_shell *shell, char *input, int i);
char					*f_handle_env_cmd(t_shell *shell, char *line);
char					*f_find_var_value(t_shell *shell, char *var_start,
							int var_len);
char					*f_replace_line(t_shell *shell, char *line,
							char *var_value, int start);
char					*f_handle_err(t_shell *shell, char *line, int start);
char					*f_set_shard(t_shell *shell, char *line);

// second parser
void					s_parsing(t_shell *shell);
void					clean_empty_and_quotes(t_shell *shell,
							t_first *current);
void					remove_quotes(char *str);
void					s_create_node(t_shell *shell, t_second *new_node);
void					s_add_redir(t_shell *shell, t_second *second);
void					s_add_arg(t_shell *shell, t_second *second);
void					s_save_args(t_shell *shell, t_second *second);
void					s_set_arg_zero(t_shell *shell, t_second *second);

// FREE EXIT
void					free_shell(t_shell *shell);
void					error_exit(t_shell *shell, char *msg, int error);
void					malloc_error(t_shell *shell);
void					print_err(char *msg, char *word, int flag);
void					free_first(t_first *current);
void					free_second(t_shell *shell);
void					loop_free_shell(t_shell *shell);

// PIPEX
void					exec(t_shell *shell);
void					get_paths(t_shell *shell);
void					parse_paths(t_shell *shell);
void					join_path(t_shell *shell, t_second *s_current,
							char *path);
void					dup_fd(t_shell *shell, int fd1, int fd2);
void					check_access(t_shell *shell);

// LOOP
int						builtin_one_cmd(t_shell *shell);
void					one_command(t_shell *shell, char **envp);
void					first_cmd(t_shell *shell, char **envp);
void					mid_cmd(t_shell *shell, char **envp);
void					last_cmd(t_shell *shell, char **envp);

// UTILS
void					exev(t_shell *shell, char **envp);
void					create_own_pipes(t_shell *shell);
void					close_own_pipes(t_shell *shell);
void					wait_childrens(void);
void					close_last_pipes(t_shell *shell);
void					malloc_fds(t_shell *shell);
int						open_infile(t_shell *shell);
int						open_outfile(t_shell *shell);
int						open_outfile_append(t_shell *shell);
void					handle_heredoc(t_second *current);
int						handle_redirs(t_shell *shell);

// CHECK FILES
void					check_files(t_shell *shell);
void					check_infile(t_shell *shell);
void					check_outfile(t_shell *shell);
void					check_outfile_append(t_shell *shell);
void					close_files(t_shell *shell);

// BUILTINS
void					bl_echo(t_shell *shell);
void					bl_pwd(t_shell *shell);
int						bl_env(t_shell *shell);
void					bl_exit(t_shell *shell, char **args);
int						bl_unset(t_shell *shell, char **args);
int						bl_cd(t_shell *shell, char **params);

int						check_newline(char **arg, int *flag);
void					builtin_cmd(t_shell *shell);

// Env
int						conf_env(t_shell *shell, char **env);
void					conf_second_env(t_shell *shell, char **envp);
void					free_list(t_shell *shell);
bool					print_error(char *str);
void					free_t_env(t_shell *shell, char *err, int ext);
void					copy_env(t_shell *shell);
int						env_size(t_shell *shell);
void					add_back_env(t_shell *shell, char *value);
t_env_list				*create_env_node(t_shell *shell, char *new);

// export
char					**lst_to_arr(t_shell *shell, t_env_list *env);
void					sort_array(char **arr);
void					export(t_shell *shell, char *str);
int						bl_export(t_shell *shell, char **str);

// SIGNALS
void					handle_sig(int s);
void					sig_heredoc(int s);
void					ft_sig_heredoc(void);
void					ft_signals(void);
bool					catchsignals(t_shell *shell);

#endif
