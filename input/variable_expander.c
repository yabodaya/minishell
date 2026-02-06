/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:26:43 by sounania          #+#    #+#             */
/*   Updated: 2026/02/06 14:18:59 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_exit_status;

static char	*expand_at_index(char *result, int *i)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_len = get_var_name_len(result + *i + 1);
	if (var_len == 0)
	{
		(*i)++;
		return (result);
	}
	var_name = extract_var_name(result + *i + 1, var_len);
	var_value = get_variable_value(var_name);
	temp = build_expanded_string(result, i, var_value);
	free(result);
	free(var_name);
	free(var_value);
	return (temp);
}

char	*expand_variables_in_token(char *value, int in_single_quotes)
{
	char	*result;
	int		i;

	if (in_single_quotes || !should_expand(value))
		return (strdup(value));
	result = strdup(value);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1])
			result = expand_at_index(result, &i);
		else
			i++;
	}
	return (result);
}

void	expand_tokens(t_token *tokens)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = expand_variables_in_token(current->value,
					(current->quote_type == QUOTE_SINGLE));
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
}
