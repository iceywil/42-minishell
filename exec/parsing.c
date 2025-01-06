/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:44:15 by codespace         #+#    #+#             */
/*   Updated: 2025/01/06 04:06:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_paths(t_shell *shell)
{
	char		*first;
	t_env_list	*current;

	current = shell->env_head;
	shell->unset = 0;
	if (!shell->env_head || !shell->env_head->key || !shell->env_head->key[0])
		return ;
	while (current && !ft_strnstr(current->key, "PATH", 4))
		current = current->next;
	if (!current)
	{
		shell->unset = 1;
		return ;
	}
	shell->paths = ft_split(current->key, ':');
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
					|| s_current->cmd[0] == '.' || s_current->cmd[0] == '/')
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
	if (s_current->cmd[0] == '.' || s_current->cmd[0] == '/')
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

void	execute(t_shell *shell)
{
	get_paths(shell);
	parse_paths(shell);
	handle_heredoc(shell->s_head);
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
