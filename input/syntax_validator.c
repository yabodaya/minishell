/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sounania <sounania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 10:35:34 by sounania          #+#    #+#             */
/*   Updated: 2026/02/02 12:38:19 by sounania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_unclosed_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	validate_syntax(char *input, t_token *tokens)
{
	if (!input || !*input)
	{
		printf("minishell: syntax error: empty input\n");
		return (0);
	}
	if (has_unclosed_quotes(input))
	{
		printf("minishell: syntax error: unclosed quotes\n");
		return (0);
	}
	if (!validate_pipes(tokens))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (!validate_redirections(tokens))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}
