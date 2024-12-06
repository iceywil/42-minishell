/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:44:15 by codespace         #+#    #+#             */
/*   Updated: 2024/12/06 22:28:21 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_paths(t_shell *shell)
{
	int		i;
	char	*first;

	i = 0;
	shell->unset = 0;
	if (!shell->env || !shell->env[0] || !shell->env[0][0])
		return ;
	while (shell->env[i] && !ft_strnstr(shell->env[i], "PATH", 4))
		i++;
	if (!shell->env[i])
	{
		shell->unset = 1;
		return ;
	}
	shell->paths = ft_split(shell->env[i], ':');
	if (!shell->paths)
		malloc_error(shell);
	first = ft_strtrim(shell->paths[0], "PATH=");
	if (!first)
		malloc_error(shell);
	free(shell->paths[0]);
	shell->paths[0] = first;
}

// check this later
void	envp_loop(t_shell *shell, int i, int y)
{
	/* while (i < shell->args)
	{
		if (argv[y][0] == '/' && access(argv[y], F_OK) == 0 && access(argv[y],
				X_OK) == 0)
		{
			shell->cmd_paths[i] = malloc(sizeof(char));
			shell->cmd_paths[i][0] = '\0';
			i++;
		}
		else
		{
			shell->err = 127;
			if (shell->unset == 1)
			{
				ft_putendl_fd("Command not found", 2);
				ft_putendl_fd("Command not found", 2);
			}
			free_shell(shell);
		}
		y++;
	} */
}

void	parse_paths(t_shell *shell)
{
	int			i;
	int			j;
	t_second	*s_current;

	s_current = shell->s_head;
	while (s_current)
	{
		s_current->infile = -1;
		if (s_current->cmd)
		{
			j = 0;
			while (shell->paths && shell->paths[j])
			{
				join_path(shell, s_current, shell->paths[j++]);
				if (access(s_current->cmd_path, F_OK) == 0
					|| !ft_strncmp(s_current->cmd, "/", 1))
					break ;
				if (s_current->cmd_path)
					free(s_current->cmd_path);
				s_current->cmd_path = NULL;
			}
		}
		s_current = s_current->next;
	}
}
