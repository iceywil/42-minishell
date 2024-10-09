/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:29:59 by codespace         #+#    #+#             */
/*   Updated: 2024/10/02 16:10:45 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(t_shell *shell, char **envp, char **argv)
{
	malloc_fds(shell);
	malloc_pids(shell);
	shell->x = 0;
	first_cmd(shell, envp, argv);
	if (shell->filein != -1)
		close(shell->filein);
	shell->x++;
	while (shell->x < shell->argc - 5)
		(mid_cmd(shell, envp), shell->x++);
	last_cmd(shell, envp, argv);
	wait_childrens();
	if (shell->filein)
		close(shell->filein);
	close_last_pipes(shell);
	close_own_pipes(shell);
}
