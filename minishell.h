/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:46:19 by codespace         #+#    #+#             */
/*   Updated: 2024/12/07 00:45:15 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define _XOPEN_SOURCE 700

#include "libft/libft.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NEWLINE_M "syntax error near unexpected token `newline'\n"
#define DIRECTORY_M "Is a directory\n"

#define PIPE '|'
#define LEFT '<'
#define RIGHT '>'
#define DOUBLE_LEFT "<<"
#define DOUBLE_RIGHT ">>"

typedef struct t_first
{
	char *token;
	char *line;
	int cmd;
	struct t_first *prev;
	struct t_first *next;
} t_first;

typedef struct t_second
{
	int i;
	char *cmd;
	char *cmd_path;
	char **args;
	t_first *args_head;
	t_first *args_current;
	t_first *redir_head;
	t_first *redir_current;
	char *heredoc;
	int infile;
	int outfile;
	struct t_second *next;
	struct t_second *prev;
} t_second;

typedef struct s_env_list
{
	char *key;
	char *value;
	int index;
	bool isunset;
	struct s_env_list *next;
	struct s_env_list *prev;
} t_env_list;

typedef struct s_shell
{
	int i;
	int x;
	// Execute
	int unset;
	int err;
	int cmd_nbr;
	char **paths;
	int **fds;
	int *pids;
	// Minishell
	int excode;
	char *line;
	// Parser
	t_first *f_head;
	t_first *f_current;
	t_second *s_head;
	t_second *s_current;
	// Env
	char *cwd;
	char **env;
	t_env_list *env_head;
	char *pwd;
	char *oldpwd;
} t_shell;

// MAIN
char *create_buffer(void);
void init_all(t_shell *shell);
void execute(t_shell *shell);
void copy_env(t_shell *shell, char **envp);
int check_empty_line(t_shell *shell);
void init_env_list(t_shell *shell, char **envp);

// PARSING
int parsing(t_shell *shell);
int check_token_legit(t_shell *shell, t_first *current);

// utils
int is_token(char c);
int check_open_quotes(t_shell *shell, char *input,
					  int flag);
int count_args(char *cmd);

// first parser
void f_parsing(t_shell *shell, char *input);
int f_split_loop(t_shell *shell, char *input, int start,
				 int i);
void f_add_node(t_shell *shell, char *line, int cmd);
int f_no_quotes(t_shell *shell, char *input, int start,
				int i);
char *f_handle_env_cmd(t_shell *shell, char *line);
int f_handle_token(t_shell *shell, char *input, int start,
				   int i);
char *f_handle_env_cmd(t_shell *shell, char *line);
char *f_find_var_value(t_shell *shell, char *var_start,
					   int var_len);
char *f_replace_line(t_shell *shell, char *line,
					 char *var_value, int start);
char *f_handle_err(t_shell *shell, char *line, int start);
char *f_set_shard(t_shell *shell, char *line);

// second parser
void s_parsing(t_shell *shell);
void clean_empty_and_quotes(t_shell *shell,
							t_first *current);
void remove_quotes(char *str);
void s_create_node(t_shell *shell, t_second *new_node);
void s_add_redir(t_shell *shell, t_second *second);
void s_add_arg(t_shell *shell, t_second *second);
void s_save_args(t_shell *shell, t_second *second);

// FREE EXIT
void free_shell(t_shell *shell);
void check_exit(t_shell *shell);
void free_pipex(t_shell *shell);
void error_exit(t_shell *shell, char *msg, int error);
void malloc_error(t_shell *shell);
void print_err(char *msg, char *word, char redir, int flag);
void clean_first(t_shell *shell);
void clean_second(t_shell *shell);

// PIPEX
void exec(t_shell *shell);
void get_paths(t_shell *shell);
// void				parse_args(t_shell *shell, char **argv, int argc, int i);
void parse_paths(t_shell *shell);
void join_path(t_shell *shell, t_second *s_current,
			   char *path);
void envp_check(t_shell *shell);
void envp_loop(t_shell *shell, int i, int y);
// int			get_heredoc(t_shell *shell);
// void		exec(t_shell *shell, char **envp, char **argv);
void dup_fd(t_shell *shell, int fd1, int fd2);
void check_access(t_shell *shell);

// LOOP
void one_command(t_shell *shell, char **envp);
void first_cmd(t_shell *shell, char **envp);
void mid_cmd(t_shell *shell, char **envp);
void last_cmd(t_shell *shell, char **envp);

// UTILS
void exev(t_shell *shell, char **envp);
void create_own_pipes(t_shell *shell);
void close_own_pipes(t_shell *shell);
void wait_childrens(void);
void close_last_pipes(t_shell *shell);
void malloc_fds(t_shell *shell);
void check_outfile(t_shell *shell);
int open_infile(t_shell *shell);
int open_outfile(t_shell *shell);
int open_outfile_append(t_shell *shell);
void handle_heredoc(t_shell *shell, t_second *current);
int handle_redirs(t_shell *shell);

// BUILTINS
void bl_echo(t_shell *shell);
void bl_pwd(t_shell *shell);
int bl_env(t_shell *shell);
void bl_exit(char **arg, t_shell *shell);
int check_newline(char **arg, int *flag);
char *env(char **env, char *ag);
char *bl_varenv(char **env, char *arg);
int env_compare(char **env, char **arg, int i);
void bl_set_env(char **env, char *value);
void builtin_cmd(t_shell *shell, char **envp);
char **bl_add_line(char **env, char *value);
void suppr_space(char *str);
t_env_list *new_env(char *key, char *value, t_shell *shell);
void add_or_update_env(t_env_list **env, char *arg, char *value, t_shell *shell);
bool is_valid_identifier(char *arg);
void handle_id(t_env_list *env, char *arg, t_shell *shell);


// UTILS
void init_shell(t_shell *shell, char **envp);
t_env_list *find_env_node(t_env_list *env_head, const char *key);
void edit_env_value(t_shell *shell, const char *key, const char *value);
void add_env_value(t_shell *shell, const char *key, const char *value);
void set_env(t_shell *shell, const char *key, const char *value);
char *get_env_value(t_env_list *env_head, const char *key);
char *ft_strcat(char *dest, const char *src);
char *ft_strjoin_double(const char *s1, const char *sep, const char *s2);
void ft_getenv(t_shell *shell, char **envp);
void fill_envp(t_shell *shell);
char *get_value_by_key(t_env_list *env_head, const char *key);

//Env
size_t	env_size(t_env_list *env);
int add_back_env(t_env_list **env, char *new_element);
int conf_env(t_shell *shell, char **env);
bool conf_second_env(t_shell *shell);
int	free_list(t_env_list **envp);
bool	print_error(char *str);
void	free_t_env(t_shell *shell, char *err, int ext);
// export
char	**lst_to_arr(t_env_list *env);
void	sort_array(char **arr, int len);
bool	export(char *str, t_env_list **env);
int	bl_export(t_shell *shell);
int	bl_cd(t_shell *shell, char **params);


#endif