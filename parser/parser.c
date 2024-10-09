/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:26 by a                 #+#    #+#             */
/*   Updated: 2024/10/09 16:22:22 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_shell *shell)
{
	check_open_quotes(shell, shell->line, 0);
	check_pipes(shell, shell->line);
	// check_redirections(shell);
}

void	check_open_quotes(t_shell *shell, char *input, int flag)
{
	char	quote;
	int		i;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '\"' || input[i] == '\'') && (!flag))
		{
			quote = input[i];
			flag = 1;
		}
		else if (flag == 1 && input[i] == quote)
			flag = 0;
	}
	if (flag == 1)
	{
		ft_putstr_fd("Invalid syntax unclosed quotes\n", 2);
		shell->excode = 2;
		free_shell(shell);
	}
	// shell->inp = ft_strdup(input);
	// if (!shell->inp)
	//	(free(input), exitmsg(shell, MERROR));
}

void	check_pipes(t_shell *shell, char *input)
{
	while (++input)
	{
		if (*input == '|' && (*(input - 1) != ' ' || *(input + 1) != ' '))
		{
			shell->excode = 2;
			error_exit(shell, "syntax error near unexpected token `|'", 2);
		}
	}
}
