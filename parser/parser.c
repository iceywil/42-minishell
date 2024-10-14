/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:26 by a                 #+#    #+#             */
/*   Updated: 2024/10/14 17:17:52 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_shell *shell)
{
	if (check_open_quotes(shell, shell->line, 0))
		return (1);
	if (check_tokens(shell, shell->line))
		return (1);
	if (check_semicolon(shell, shell->line))
		return (1);
	if (check_format(shell, shell->line))
		return (1);
	return (0);
}

int	check_open_quotes(t_shell *shell, char *input, int flag)
{
	int	i;
	int	single;
	int	doublee;

	single = 0;
	doublee = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"')
			doublee++;
		else if (input[i] == '\'')
			single++;
	}
	if (single % 2 != 0 || doublee % 2 != 0)
	{
		shell->excode = 2;
		print_err("syntax error quotes not closed", 0, 0, 0);
	}
	return (0);
}

int	check_tokens(t_shell *shell, char *input)
{
	if (check_count(shell, shell->line, '|'))
		return (1);
	if (check_between(shell, shell->line, '|'))
		return (1);
	if (check_last(shell, shell->line, '|'))
		return (1);
	if (check_count(shell, shell->line, '&'))
		return (1);
	if (check_between(shell, shell->line, '&'))
		return (1);
	if (check_last(shell, shell->line, '&'))
		return (1);
	if (check_count(shell, shell->line, '>'))
		return (1);
	if (check_between(shell, shell->line, '>'))
		return (1);
	if (check_last(shell, shell->line, '>'))
		return (1);
	if (check_count(shell, shell->line, '<'))
		return (1);
	if (check_between(shell, shell->line, '<'))
		return (1);
	if (check_last(shell, shell->line, '<'))
		return (1);
}

int	check_count(t_shell *shell, char *input, char redir)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (input[i])
	{
		if (input[i] == redir)
			flag++;
		else
			flag = 0;
		if (flag == 3)
			return (print_err(TOKEN_M, 0, redir, 2), 1);
		else if (flag > 3)
			return (print_err(TOKEN_M, 0, redir, 3), 1);
		i++;
	}
	return (0);
}

int	check_between(t_shell *shell, char *input, char redir)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == redir)
		{
			if(!flag && input[i - 1] != )
		}
		else if (input[i] != ' ')
			flag = 1;
		i++;
	}
	return (0);
}

int	check_last(t_shell *shell, char *input, char redir)
{
	return (0);
}

int	check_redir(t_shell *shell, char *input, char redir, int flag)
{
	int	alpha;
	int	i;

	i = -1;
	alpha = 0;
	while (input[++i])
	{
		if (ft_isalpha(input[i]))
			alpha = 1;
		if (input[i] == redir)
		{
			flag++;
			if (!alpha && flag > 2)
				return (print_err(TOKEN_M, 0, redir, 2), 1);
			if (flag > 2)
				return (print_err(TOKEN_M, 0, redir, 3), 1);
		}
		else
			flag = 0;
	}
	return (0);
}

int	check_semicolon(t_shell *shell, char *input)
{
	return (0);
}

int	check_format(t_shell *shell, char *input)
{
	return (0);
}
