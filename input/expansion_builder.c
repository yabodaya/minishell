/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sounania <sounania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:27:51 by sounania          #+#    #+#             */
/*   Updated: 2026/02/02 11:46:14 by sounania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*build_expanded_string(char *str, int *i, char *var_value)
{
	char	*result;
	int		result_len;
	int		var_name_len;
	int		j;
	int		k;

	var_name_len = get_var_name_len(str + *i + 1);
	result_len = *i + ft_strlen(var_value)
		+ ft_strlen(str + *i + 1 + var_name_len);
	result = malloc(result_len + 1);
	if (!result)
		return (NULL);
	j = 0;
	k = 0;
	while (k < *i)
		result[j++] = str[k++];
	k = 0;
	while (var_value && var_value[k])
		result[j++] = var_value[k++];
	k = *i + 1 + var_name_len;
	while (str[k])
		result[j++] = str[k++];
	result[j] = '\0';
	*i = *i + ft_strlen(var_value);
	return (result);
}
