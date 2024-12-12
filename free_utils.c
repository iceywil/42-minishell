/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:36:19 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 02:36:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_list(t_env_list **envp)
{
	t_env_list	*tmp;
	t_env_list	*current;

	if (!(*envp))
		return (0);
	current = *envp;
	while (current->next != *envp)
	{
		tmp = current;
		current = current->next;
		free(tmp->key);
		free(tmp);
	}
	free(current->key);
	free(current);
	*envp = NULL;
	return (0);
}

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

void	free_t_env(t_shell *shell, char *err, int ext)
{
	if (shell->env_head)
		free_list(&shell->env_head);
	if (err)
		print_error(err);
	rl_clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (ext != -1)
		exit(ext);
}