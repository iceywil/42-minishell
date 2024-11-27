/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:40:22 by a                 #+#    #+#             */
/*   Updated: 2024/11/10 22:04:25 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*f_handle_dollar(t_shell *shell, char *var_name, size_t var_len)
{
	int		i;
	char	*env_value;

	i = 0;
	env_value = NULL;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var_name, var_len)
			&& shell->env[i][var_len] == '=')
		{
			env_value = shell->env[i] + var_len + 1;
			break ;
		}
		i++;
	}
	free(var_name);
	return (env_value);
}

char	*f_get_var_name(char *line, char **var_end)
{
	char	*var_start;


	var_start = NULL;
	var_start = ft_strchr(line, '$');
	if (!var_start)
		return (NULL);
	else
		var_start = var_start + 1;
	*var_end = var_start;
	while (**var_end && **var_end != ' ' && **var_end != '\''
		&& **var_end != '\"')
		(*var_end)++;
	return (strndup(var_start, *var_end - var_start));
}

char	*f_handle_env_cmd(t_shell *shell, char *line)
{
	char	*var_end;
	char	*var_name;
	char	*env_value;
	size_t	prefix_len;
	char	*new_line;

	if (!line || !*line || line[0] == '\'' || line[ft_strlen(line) - 1] == '\'')
		return (line);
	var_name = NULL;
	//Maybe add "$PA"TH > TH
	//Fix ''$PATH
	var_name = f_get_var_name(line, &var_end);
	if (!var_name)
		return (line);
	if (!var_name || !*var_name)
		return (line);
	env_value = f_handle_dollar(shell, var_name, ft_strlen(var_name));
	if (!env_value)
		return (line);
	prefix_len = ft_strchr(line, '$') - line;
	new_line = f_create_new_line(line, env_value, var_end, prefix_len);
	if (!new_line)
		return (NULL);
	free(line);
	return (new_line);
}

char	*f_create_new_line(char *line, char *env_value, char *var_end,
		size_t prefix_len)
{
	char	*new_line;
	size_t	suffix_len;

	suffix_len = ft_strlen(var_end);
	new_line = malloc(prefix_len + ft_strlen(env_value) + suffix_len + 1);
	if (!new_line)
		return (NULL);
	ft_strncpy(new_line, line, prefix_len);
	ft_strcpy(new_line + prefix_len, env_value);
	ft_strcpy(new_line + prefix_len + ft_strlen(env_value), var_end);
	return (new_line);
}
