/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:29:59 by codespace         #+#    #+#             */
/*   Updated: 2024/12/07 00:22:15 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_command(t_shell *shell, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		// check access for cmd
		// check_access(shell);
		shell->s_current = shell->s_head;
		if (handle_redirs(shell))
		{
			shell->err = 1;
			return ;
		}
		if (shell->s_current->infile != -1)
		{
			dup_fd(shell, shell->s_current->infile, STDIN_FILENO);
			close(shell->s_current->infile);
		}
		if (shell->s_current->outfile != -1)
		{
			dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO);
			close(shell->s_current->outfile);
		}
		// Exécuter la commande intégrée si elle existe
		if (builtin_cmd(shell, envp))
		{
			free_shell(shell);
			exit(shell->excode);
		}
		// Exécuter la commande externe
		exev(shell, envp);
	}
	wait_childrens();
}

int	builtin_cmd(t_shell *shell, char **envp)
{
	/* if (ft_strcmp(shell->s_current->args[0], "exit") == 0)
	{
		bl_exit(shell);
		return (1);
	}
	else if (ft_strcmp(shell->s_current->args[0], "echo") == 0)
	{
		bl_echo(shell);
		return (1);
	}
	// else if (ft_strcmp(shell->s_current->args[0], "cd") == 0)
	// {
	// 	bl_cd();
	// 	return (1);
	// }
	else if (ft_strcmp(shell->s_current->args[0], "pwd") == 0)
	{
		bl_pwd(shell);
		return (1);
	}
	else if (ft_strcmp(shell->s_current->args[0], "env") == 0)
	{
		bl_env(shell);
		return (1);
	}
	else if (ft_strcmp(shell->s_current->args[0], "unset") == 0)
	{
		bl_unset(shell->s_current->args[1]);
		return (1);
	}
	else if (ft_strcmp(shell->s_current->args[0], "export") == 0)
	{
		bl_export(shell);
		return (1);
	}
	else
		return (0); */
}

void	exec(t_shell *shell)
{
	malloc_fds(shell);
	shell->i = 0;
	shell->s_current = shell->s_head;
	first_cmd(shell, shell->env);
	if (shell->s_current->infile != -1)
		close(shell->s_current->infile);
	shell->i++;
	shell->s_current = shell->s_current->next;
	while (shell->i != shell->cmd_nbr - 1)
	{
		mid_cmd(shell, shell->env);
		shell->i++;
		shell->s_current = shell->s_current->next;
	}
	last_cmd(shell, shell->env);
	wait_childrens();
	close_last_pipes(shell);
	close_own_pipes(shell);
}

void	first_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	create_own_pipes(shell);
	// check_access(shell);
	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (handle_redirs(shell))
		{
			shell->err = 1;
			close_own_pipes(shell);
			exit(1);
		}
		if (shell->s_current->infile != -1)
		{
			dup_fd(shell, shell->s_current->infile, STDIN_FILENO);
			close(shell->s_current->infile);
		}
		if (shell->s_current->outfile != -1)
		{
			dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO);
			close(shell->s_current->outfile);
		}
		else
			dup_fd(shell, shell->fds[shell->i][1], STDOUT_FILENO);
		close_own_pipes(shell);
		builtin_cmd(shell, envp);
		exev(shell, envp);
	}
	close(shell->fds[0][1]);
}

void	mid_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	create_own_pipes(shell);
	// check_access(shell);
	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (handle_redirs(shell))
		{
			shell->err = 1;
			close_own_pipes(shell);
			exit(1);
		}
		if (shell->s_current->infile != -1)
		{
			dup_fd(shell, shell->s_current->infile, STDIN_FILENO);
			close(shell->s_current->infile);
		}
		else
			dup_fd(shell, shell->fds[shell->i - 1][0], STDIN_FILENO);
		if (shell->s_current->outfile != -1)
		{
			dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO);
			close(shell->s_current->outfile);
		}
		else
			dup_fd(shell, shell->fds[shell->i][1], STDOUT_FILENO);
		close_own_pipes(shell);
		close_last_pipes(shell);
		builtin_cmd(shell, envp);
		exev(shell, envp);
	}
	close(shell->fds[shell->i][1]);
	close(shell->fds[shell->i - 1][0]);
}

void	last_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	create_own_pipes(shell);
	// check_access(shell);
	pid = fork();
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		if (handle_redirs(shell))
		{
			shell->err = 1;
			close_own_pipes(shell);
			exit(1);
		}
		if (shell->s_current->infile != -1)
		{
			dup_fd(shell, shell->s_current->infile, STDIN_FILENO);
			close(shell->s_current->infile);
		}
		else
		{
			dup_fd(shell, shell->fds[shell->i - 1][0], STDIN_FILENO);
		}
		if (shell->s_current->outfile != -1)
		{
			dup_fd(shell, shell->s_current->outfile, STDOUT_FILENO);
			close(shell->s_current->outfile);
		}
		close_own_pipes(shell);
		close_last_pipes(shell);
		builtin_cmd(shell, envp);   
		exev(shell, envp);
	}
	close(shell->fds[shell->i][1]);
	close(shell->fds[shell->i - 1][0]);
}
