/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:36:19 by marvin            #+#    #+#             */
/*   Updated: 2025/01/02 18:59:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_shell *shell)
{
	t_env_list	*current;
	t_env_list	*next;

	current = shell->env_head;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		free(current);
		current = next;
	}
	shell->env_head = NULL;
}

void	error_exit(t_shell *shell, char *msg, int error)
{
	ft_putendl_fd(msg, 2);
	free_shell(shell);
	exit(error);
}

void	malloc_error(t_shell *shell)
{
	ft_putendl_fd("Malloc error", 2);
	free_shell(shell);
	exit(1);
}

void	free_t_env(t_shell *shell, char *err, int ext)
{
	if (shell->env_head)
		free_list(shell);
	if (err)
		ft_putstr_fd(err, 2);
	rl_clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (ext != -1)
		exit(ext);
}
