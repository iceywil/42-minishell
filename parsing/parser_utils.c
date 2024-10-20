/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:40 by codespace         #+#    #+#             */
/*   Updated: 2024/10/20 03:15:31 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *input)
{
	int	i;
	int	j;

	if (!input)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != '\'' && input[i] != '\"')
		{
			input[j] = input[i];
			j++;
		}
		i++;
	}
	input[j] = '\0';
	return (input);
}

int	is_token(char c)
{
	if (c == PIPE || c == LEFT || c == RIGHT)
		return (1);
	return (0);
}

int	count_args(char *cmd)
{
	char	quote_char;
	int		count;
	int		i;

	count = 0;
	i = 0;
	quote_char = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		if (cmd[i])
		{
			count++;
			while (cmd[i] && (quote_char || (cmd[i] != ' ' && cmd[i] != '\t')))
			{
				if ((cmd[i] == '\'' || cmd[i] == '\"') && !quote_char)
					quote_char = cmd[i];
				else if (cmd[i] == quote_char)
					quote_char = 0;
				i++;
			}
		}
	}
	return (count);
}
