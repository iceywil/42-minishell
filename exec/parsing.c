/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:44:15 by codespace         #+#    #+#             */
/*   Updated: 2024/12/10 09:13:12 by a                ###   ########.fr       */
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
					|| s_current->cmd[0] == '/')
					break ;
				if (s_current->cmd_path)
					free(s_current->cmd_path);
				s_current->cmd_path = NULL;
			}
		}
		s_current = s_current->next;
	}
}

void	join_path(t_shell *shell, t_second *s_current, char *path)
{
	char	*part_path;

	part_path = NULL;
	if (s_current->cmd[0] == '/')
	{
		s_current->cmd_path = ft_strdup(s_current->cmd);
		if (!s_current->cmd_path)
			malloc_error(shell);
		return ;
	}
	part_path = ft_strjoin(path, "/");
	if (!part_path)
		malloc_error(shell);
	s_current->cmd_path = ft_strjoin(part_path, s_current->cmd);
	if (!s_current->cmd_path)
		malloc_error(shell);
	free(part_path);
}
