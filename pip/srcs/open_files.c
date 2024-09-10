/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:32 by wscherre          #+#    #+#             */
/*   Updated: 2024/04/22 17:52:06 by wscherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_infile(t_main *pipex, char **argv)
{
	pipex->filein = -1;
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
	pipex->filein = open(argv[1], O_RDONLY, 0777);
	if (pipex->filein == -1)
	{
		ft_putstr_fd("Error Can't open ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" file\n", 2);
	}
}

void	open_outfile_here(t_main *pipex, char **argv)
{
	pipex->fileout = -1;
	if (access(argv[pipex->argc - 1], F_OK) == 0)
	{
		pipex->fileout = open(argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->fileout == -1)
		{
			ft_putstr_fd("Error File ", 2);
			ft_putstr_fd(argv[pipex->argc - 1], 2);
			ft_putstr_fd(" permission denied\n", 2);
		}
	}
	else
	{
		pipex->fileout = open(argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->fileout == -1)
		{
			ft_putstr_fd("Error Can't open ", 2);
			ft_putstr_fd(argv[pipex->argc - 1], 2);
			ft_putstr_fd(" file\n", 2);
		}
	}
}

void	check_outfile(t_main *pipex, char **argv)
{
	if (access(argv[pipex->argc - 1], F_OK) == 0)
	{
		if (access(argv[pipex->argc - 1], R_OK | W_OK) == -1)
			pipex->err = 1;
	}
}

void	open_outfile(t_main *pipex, char **argv)
{
	pipex->fileout = -1;
	if (access(argv[pipex->argc - 1], F_OK) == 0)
	{
		pipex->fileout = open(argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fileout == -1)
		{
			ft_putstr_fd("Error File ", 2);
			ft_putstr_fd(argv[pipex->argc - 1], 2);
			ft_putstr_fd(" permission denied\n", 2);
		}
	}
	else
	{
		pipex->fileout = open(argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fileout == -1)
		{
			ft_putstr_fd("Error Can't open ", 2);
			ft_putstr_fd(argv[pipex->argc - 1], 2);
			ft_putstr_fd(" file\n", 2);
		}
	}
}
