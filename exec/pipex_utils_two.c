/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/02 16:10:55 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_infile(t_shell *shell, char **argv)
{
	shell->filein = -1;
	if (access(argv[1], F_OK) == -1)
	{
		ft_putstr_fd("Error File ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" does not exist\n", 2);
		return ;
	}
	if (access(argv[1], R_OK) == -1)
	{
		ft_putstr_fd("Error File ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" permission denied\n", 2);
		return ;
	}
	shell->filein = open(argv[1], O_RDONLY, 0777);
	if (shell->filein == -1)
	{
		ft_putstr_fd("Error Can't open ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" file\n", 2);
	}
}

void	open_outfile_here(t_shell *shell, char **argv)
{
	shell->fileout = -1;
	if (access(argv[shell->argc - 1], F_OK) == 0)
	{
		shell->fileout = open(argv[shell->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->fileout == -1)
		{
			ft_putstr_fd("Error File ", 2);
			ft_putstr_fd(argv[shell->argc - 1], 2);
			ft_putstr_fd(" permission denied\n", 2);
		}
	}
	else
	{
		shell->fileout = open(argv[shell->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->fileout == -1)
		{
			ft_putstr_fd("Error Can't open ", 2);
			ft_putstr_fd(argv[shell->argc - 1], 2);
			ft_putstr_fd(" file\n", 2);
		}
	}
}

void	check_outfile(t_shell *shell, char **argv)
{
	if (access(argv[shell->argc - 1], F_OK) == 0)
	{
		if (access(argv[shell->argc - 1], R_OK | W_OK) == -1)
			shell->err = 1;
	}
}

void	open_outfile(t_shell *shell, char **argv)
{
	shell->fileout = -1;
	if (access(argv[shell->argc - 1], F_OK) == 0)
	{
		shell->fileout = open(argv[shell->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->fileout == -1)
		{
			ft_putstr_fd("Error File ", 2);
			ft_putstr_fd(argv[shell->argc - 1], 2);
			ft_putstr_fd(" permission denied\n", 2);
		}
	}
	else
	{
		shell->fileout = open(argv[shell->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->fileout == -1)
		{
			ft_putstr_fd("Error Can't open ", 2);
			ft_putstr_fd(argv[shell->argc - 1], 2);
			ft_putstr_fd(" file\n", 2);
		}
	}
}
