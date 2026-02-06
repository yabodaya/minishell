/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sounania <sounania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:15:00 by sounania          #+#    #+#             */
/*   Updated: 2026/02/06 12:15:00 by sounania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *var_name)
{
	char	*value;

	if (!var_name || !*var_name)
		return (NULL);
	value = getenv(var_name);
	if (!value)
		return (strdup(""));
	return (strdup(value));
}

int	get_var_name_len(char *str)
{
	int	len;

	len = 0;
	if (str[0] == '?')
		return (1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

char	*extract_var_name(char *str, int len)
{
	char	*name;
	int		i;

	name = malloc(len + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_variable_value(char *var_name)
{
	char	*value;
	char	*exit_str;

	if (!var_name)
		return (strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_str = ft_itoa(g_last_exit_status);
		return (exit_str);
	}
	value = get_env_value(var_name);
	return (value);
}
