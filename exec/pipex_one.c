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
	if (ft_strcmp(shell->s_current->args[0], "echo") == 0)
	{
		bl_echo(shell);
		// return (1);
	}
	// else if (ft_strcmp(shell->s_current->args[0], "cd") == 0)
	// {
	// 	bl_cd();
	// 	return (1);
	// }
// 	int	check_newline(char **tab, int *flag)
// {
// 	int	n;
// 	int	i;

// 	n = 1;
// 	while (tab[n] && tab[n][0] == '-' && tab[n][1] == 'n')
// 	{
// 		i = 1;
// 		if (tab[n][0] == '-' && tab[n][1] == 'n')
// 		{
// 			while (tab[n][i] == 'n')
// 				i++;
// 			if (tab[n][i] != '\0')
// 				return (n);
// 		}
// 		*flag = 1;
// 		n++;
// 	}
// 	return (n);
// }

// void	bl_echo(t_shell *shell)
// {
// 	int	i;
// 	int	flag;
// 	int	ext;

// 	flag = 0;
// 	i = check_newline(shell->s_current->args, &flag);
// 	if (shell->s_current->args[1])
// 	{
// 		while (shell->s_current->args[i])
// 		{
// 			if (shell->s_current->args[i] && !shell->s_current->args[i + 1])
// 				printf("%s", shell->s_current->args[i++]);
// 			else if (shell->s_current->args[i])
// 				printf("%s ", shell->s_current->args[i++]);
// 		}
// 	}
// 	if (!flag)
// 		printf("\n");
// 	if (shell->s_current->next)
// 		ext = shell->excode;
// 	else
// 		ext = shell->uns;
// 	free_shell(shell);
// 	exit(ext);
// }
	else if (ft_strcmp(shell->s_current->args[0], "pwd") == 0)
	{
		bl_pwd();
		return (1);
	}
	else if (ft_strcmp(shell->s_current->args[0], "unset") == 0)
	{
		bl_unset(shell->s_current->args[1]);
		return (1);
	}
	else if (ft_strcmp(shell->s_current->args[0], "exit") == 0)
	{
		bl_exit(shell);
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
