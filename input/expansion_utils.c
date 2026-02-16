/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sounania <sounania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:27:24 by sounania          #+#    #+#             */
/*   Updated: 2026/02/02 11:27:36 by sounania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_single_quotes(char *original, int pos)
{
	int		i;
	char	quote;
	int		in_quotes;

	i = 0;
	in_quotes = 0;
	quote = 0;
	while (i < pos && original[i])
	{
		if (!in_quotes && is_quote(original[i]))
		{
			in_quotes = 1;
			quote = original[i];
		}
		else if (in_quotes && original[i] == quote)
			in_quotes = 0;
		i++;
	}
	return (in_quotes && quote == '\'');
}

int	should_expand(char *token_value)
{
	int	i;

	i = 0;
	while (token_value[i])
	{
		if (token_value[i] == '$' && token_value[i + 1])
			return (1);
		i++;
	}
	return (0);
}
