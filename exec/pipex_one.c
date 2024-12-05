/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:29:59 by codespace         #+#    #+#             */
/*   Updated: 2024/11/27 22:27:38 by a                ###   ########.fr       */
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
		if (shell->s_current->filein != -1)
		{
			dup_fd(shell, shell->s_current->filein, STDIN_FILENO);
			close(shell->s_current->filein);
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
	ft_printf("Entering builtin_cmd\n");
	ft_printf("Command: %s\n", shell->s_current->args[0]);
	if (ft_strcmp(shell->s_current->args[0], "exit") == 0)
	{
		ft_printf("Calling bl_exit\n");
		bl_exit(shell->s_current->args, shell);
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
	else
		return (0);
}

void	exec(t_shell *shell)
{
	malloc_fds(shell);
	malloc_pids(shell);
	shell->i = 0;
	shell->s_current = shell->s_head;
	first_cmd(shell, shell->env);
	if (shell->s_current->filein != -1)
		close(shell->s_current->filein);
	shell->i++;
	shell->s_current = shell->s_current->next;
	while (shell->s_current)
	{
		mid_cmd(shell, shell->env);
		shell->i++;
		shell->s_current = shell->s_current->next;
	}
	last_cmd(shell, shell->env);
	wait_childrens();
	if (shell->s_current->prev->filein)
		close(shell->s_current->prev->filein);
	close_last_pipes(shell);
	close_own_pipes(shell);
}

void	first_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	create_own_pipes(shell);
	check_access(shell);
	pid = fork();
	shell->pids[shell->s_current->i] = pid;
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		// handle_redirs(shell);
		// open_infile(shell, argv);
		if (shell->s_current->filein != -1)
		{
			dup_fd(shell, shell->s_current->filein, STDIN_FILENO);
			close(shell->s_current->filein);
		}
		else
			(close_own_pipes(shell), free_shell(shell));
		//
		dup_fd(shell, shell->fds[0][1], STDOUT_FILENO);
		close_own_pipes(shell);
		exev(shell, envp);
	}
	close(shell->fds[0][1]);
}

void	mid_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	create_own_pipes(shell);
	check_access(shell);
	pid = fork();
	shell->pids[shell->x] = pid;
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		dup_fd(shell, shell->fds[shell->x - 1][0], STDIN_FILENO);
		dup_fd(shell, shell->fds[shell->x][1], STDOUT_FILENO);
		close_own_pipes(shell);
		close_last_pipes(shell);
		exev(shell, envp);
	}
	close(shell->fds[shell->x][1]);
	close(shell->fds[shell->x - 1][0]);
}

void	last_cmd(t_shell *shell, char **envp)
{
	pid_t	pid;

	create_own_pipes(shell);
	check_access(shell);
	check_outfile(shell);
	pid = fork();
	shell->pids[shell->x] = pid;
	if (pid == -1)
		error_exit(shell, "Fork Error", errno);
	if (pid == 0)
	{
		/* 		if (shell->here)
					open_outfile_here(shell, argv);
				else
					open_outfile(shell, argv);
				dup_fd(shell, shell->fds[shell->x - 1][0], STDIN_FILENO);
				(close_own_pipes(shell), close_last_pipes(shell));
				if (shell->fileout != -1)
				{
					dup_fd(shell, shell->fileout, STDOUT_FILENO);
					(close(shell->fileout), exev(shell, envp));
				} */
	}
	close(shell->fds[shell->x - 1][0]);
}
