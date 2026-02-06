// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/01/26 10:39:45 by sounania          #+#    #+#             */
// /*   Updated: 2026/02/06 14:25:33 by yabodaya         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int	g_last_exit_status = 0;

// // TOKEN TESTING

// /*void	print_token_type(t_token_type type)
// {
// 	if (type == TOKEN_WORD)
// 		printf("WORD");
// 	else if (type == TOKEN_PIPE)
// 		printf("PIPE");
// 	else if (type == TOKEN_REDIR_IN)
// 		printf("REDIR_IN");
// 	else if (type == TOKEN_REDIR_OUT)
// 		printf("REDIR_OUT");
// 	else if (type == TOKEN_REDIR_APPEND)
// 		printf("REDIR_APPEND");
// 	else if (type == TOKEN_REDIR_HEREDOC)
// 		printf("REDIR_HEREDOC");
// }

// void	print_tokens(t_token *tokens)
// {
// 	int	i;

// 	i = 1;
// 	while (tokens)
// 	{
// 		printf("Token %d: [", i);
// 		print_token_type(tokens->type);
// 		printf("] = \"%s\"\n", tokens->value);
// 		tokens = tokens->next;
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	char	*input;
// 	t_token	*tokens;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 			add_history(input);
// 		tokens = tokenize(input);
// 		print_tokens(tokens);
// 		free_tokens(tokens);
// 		free(input);
// 	}
// 	return (0);
// }*/

// // COMMAND TESTING

// void	print_token_type(t_token_type type)
// {
// 	if (type == TOKEN_WORD)
// 		printf("WORD");
// 	else if (type == TOKEN_PIPE)
// 		printf("PIPE");
// 	else if (type == TOKEN_REDIR_IN)
// 		printf("REDIR_IN");
// 	else if (type == TOKEN_REDIR_OUT)
// 		printf("REDIR_OUT");
// 	else if (type == TOKEN_REDIR_APPEND)
// 		printf("REDIR_APPEND");
// 	else if (type == TOKEN_REDIR_HEREDOC)
// 		printf("REDIR_HEREDOC");
// }

// void	print_tokens(t_token *tokens)
// {
// 	int	i;

// 	i = 1;
// 	while (tokens)
// 	{
// 		printf("Token %d: [", i);
// 		print_token_type(tokens->type);
// 		printf("] = \"%s\"\n", tokens->value);
// 		tokens = tokens->next;
// 		i++;
// 	}
// }

// void	print_command(t_cmd *cmd, int cmd_num)
// {
// 	int	i;

// 	printf("\n=== Command %d ===\n", cmd_num);
// 	printf("Args: ");
// 	if (cmd->args)
// 	{
// 		i = 0;
// 		while (cmd->args[i])
// 		{
// 			printf("\"%s\"", cmd->args[i]);
// 			if (cmd->args[i + 1])
// 				printf(", ");
// 			i++;
// 		}
// 	}
// 	printf("\n");
// 	if (cmd->infile)
// 		printf("Input: < %s\n", cmd->infile);
// 	if (cmd->outfile)
// 	{
// 		if (cmd->append)
// 			printf("Output: >> %s\n", cmd->outfile);
// 		else
// 			printf("Output: > %s\n", cmd->outfile);
// 	}
// 	if (cmd->heredoc_delim)
// 		printf("Heredoc: << %s\n", cmd->heredoc_delim);
// }

// void	print_commands(t_cmd *cmds)
// {
// 	int	i;

// 	i = 1;
// 	while (cmds)
// 	{
// 		print_command(cmds, i);
// 		cmds = cmds->next;
// 		i++;
// 	}
// }

// int	run_loop(void)
// {
// 	char		*input;
// 	t_token		*tokens;
// 	t_cmd	*commands;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 			add_history(input);
// 		tokens = tokenize(input);
// 		printf("\n--- TOKENS (before expansion) ---\n");
// 		print_tokens(tokens);
// 		if (!validate_syntax(input, tokens))
// 		{
// 			free_tokens(tokens);
// 			free(input);
// 			continue ;
// 		}
// 		expand_tokens(tokens);
// 		printf("\n--- TOKENS (after expansion) ---\n");
// 		print_tokens(tokens);
// 		commands = build_commands(tokens);
// 		printf("\n--- COMMANDS ---\n");
// 		print_commands(commands);
// 		printf("\n");
// 		free_commands(commands);
// 		free_tokens(tokens);
// 		free(input);
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	return (run_loop());
// }
