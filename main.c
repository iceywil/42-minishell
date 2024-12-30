/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/12/30 17:33:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc == 1)
	{
		(init_all_start(&shell), ft_signals());
		if (!conf_env(&shell, envp))
			return (free_shell(&shell), 1);
		while (1)
		{
			init_all(&shell);
			shell.cwd = create_buffer(&shell);
			if (!shell.cwd)
				return (free_shell(&shell), 1);
			shell.line = readline(shell.cwd);
			if (!shell.line)
				break ;
			if (!check_empty_line(&shell) && !parsing(&shell))
				execute(&shell);
			add_history(shell.line);
			if (shell.line)
				(free(shell.line), shell.line = NULL);
			loop_free_shell(&shell);
		}
		return (ft_putstr_fd("exit\n", 1), free_shell(&shell), 0);
	}
}

int	check_empty_line(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*create_buffer(t_shell *shell)
{
	char	*str;
	char	*buffer;

	buffer = NULL;
	buffer = ft_calloc(PATH_MAX, sizeof(char *));
	if (!buffer)
		return (malloc_error(shell), NULL);
	buffer = getcwd(buffer, PATH_MAX);
	str = ft_strjoin(buffer, "> ");
	if (!str)
		return (free(buffer), malloc_error(shell), NULL);
	free(buffer);
	return (str);
}

void	execute(t_shell *shell)
{
	get_paths(shell);
	parse_paths(shell);
	handle_heredoc(shell, shell->s_head);
	copy_env(shell);
	shell->s_current = shell->s_head;
	if (shell->cmd_nbr == 1)
	{
		if (builtin_one_cmd(shell))
			return ;
		one_command(shell, shell->env_tab);
	}
	else
		exec(shell);
}

int	builtin_one_cmd(t_shell *shell)
{
	if (!ft_strcmp(shell->s_head->cmd, "exit") || !ft_strcmp(shell->s_head->cmd,
			"cd") || !ft_strcmp(shell->s_head->cmd, "export")
		|| !ft_strcmp(shell->s_head->cmd, "unset"))
	{
		handle_redirs(shell);
		if (shell->s_current->infile > 0)
			close(shell->s_current->infile);
		if (shell->s_current->outfile > 0)
			close(shell->s_current->outfile);
		if (!ft_strcmp(shell->s_head->cmd, "exit"))
			bl_exit(shell, shell->s_head->args);
		else if (!ft_strcmp(shell->s_head->cmd, "cd"))
			bl_cd(shell, shell->s_head->args);
		else if (!ft_strcmp(shell->s_head->cmd, "export"))
			bl_export(shell, shell->s_head->args);
		else if (!ft_strcmp(shell->s_head->cmd, "unset"))
			bl_unset(shell, shell->s_head->args);
		return (1);
	}
	return (0);
}

void	copy_env(t_shell *shell)
{
	t_env_list	*current;
	int			len;
	int			i;

	len = env_size(shell);
	current = shell->env_head;
	shell->env_tab = ft_calloc(len + 1, sizeof(char *));
	if (!shell->env_tab)
		return (malloc_error(shell));
	current = shell->env_head;
	i = 0;
	while (current)
	{
		shell->env_tab[i] = ft_strdup(current->key);
		if (!shell->env_tab[i])
			return (malloc_error(shell));
		i++;
		current = current->next;
	}
	shell->env_tab[i] = NULL;
}

void	init_all_start(t_shell *shell)
{
	shell->excode = 0;
	shell->switch_signal = 0;
	shell->env_head = NULL;
	shell->env_current = NULL;
	shell->cwd = NULL;
	shell->fds = NULL;
	shell->paths = NULL;
	shell->line = NULL;
	shell->f_head = NULL;
	shell->f_current = NULL;
	shell->s_head = NULL;
	shell->s_current = NULL;
	shell->env_tab = NULL;
}

void	init_all(t_shell *shell)
{
	shell->i = 0;
	shell->unset = 0;
	shell->fds = NULL;
	shell->paths = NULL;
	shell->line = NULL;
	shell->cwd = NULL;
	shell->f_head = NULL;
	shell->f_current = NULL;
	shell->s_head = NULL;
	shell->s_current = NULL;
	shell->env_tab = NULL;
}
