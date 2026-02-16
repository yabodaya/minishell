/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sounania <sounania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:40:01 by sounania          #+#    #+#             */
/*   Updated: 2026/02/06 13:08:00 by sounania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*alloc_word(char *input, int start, int len)
{
	char	*word;
	int		j;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = input[start + j];
		j++;
	}
	word[len] = '\0';
	return (word);
}

char	*extract_word(char *input, int *i, t_quote_type *quote_type)
{
	int	start;
	int	len;

	if (!input || !i || !quote_type)
		return (NULL);
	if (is_quote(input[*i]))
	{
		if (input[*i] == '\'')
			*quote_type = QUOTE_SINGLE;
		else
			*quote_type = QUOTE_DOUBLE;
		return (extract_quoted(input, i, input[*i]));
	}
	*quote_type = QUOTE_NONE;
	start = *i;
	len = 0;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_operator(input[*i]) && !is_quote(input[*i]))
	{
		len++;
		(*i)++;
	}
	return (alloc_word(input, start, len));
}

char	*extract_quoted(char *input, int *i, char quote_char)
{
	int		start;
	int		len;
	char	*str;
	int		j;

	(*i)++;
	start = *i;
	len = 0;
	while (input[*i] && input[*i] != quote_char)
	{
		len++;
		(*i)++;
	}
	if (input[*i] == quote_char)
		(*i)++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len)
		str[j++] = input[start++];
	str[len] = '\0';
	return (str);
}
