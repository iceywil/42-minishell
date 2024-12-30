/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:36:19 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 17:57:38 by codespace        ###   ########.fr       */
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

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

void	free_t_env(t_shell *shell, char *err, int ext)
{
	if (shell->env_head)
		free_list(shell);
	if (err)
		print_error(err);
	rl_clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (ext != -1)
		exit(ext);
}