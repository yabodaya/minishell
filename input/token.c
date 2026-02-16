/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sounania <sounania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:39:52 by sounania          #+#    #+#             */
/*   Updated: 2026/02/06 09:02:12 by sounania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value, t_quote_type quote_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->quote_type = quote_type;
	token->next = NULL;
	return (token);
}

void	add_token_to_list(t_token **tokens, t_token_type type,
					char *value, t_quote_type quote_type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(type, value, quote_type);
	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

t_token	*tokenize(char *input)
{
	t_token			*tokens;
	char			*word;
	t_quote_type	quote_type;
	int				i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (handle_operator(input, &i, &tokens))
			continue ;
		word = extract_word(input, &i, &quote_type);
		if (word)
		{
			add_token_to_list(&tokens, TOKEN_WORD, word, quote_type);
			free(word);
		}
	}
	return (tokens);
}

int	handle_operator(char *input, int *i, t_token **tokens)
{
	if (handle_quote(input, i, tokens))
		return (1);
	if (handle_double_operator(input, i, tokens))
		return (1);
	if (handle_single_operator(input, i, tokens))
		return (1);
	if (handle_word(input, i, tokens))
		return (1);
	return (0);
}
