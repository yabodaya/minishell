/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:49:19 by yabodaya          #+#    #+#             */
/*   Updated: 2026/02/06 14:25:20 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				*heredoc_delim;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote_type;
	struct s_token	*next;
}	t_token;

typedef struct s_parser
{
	char	*input;
	int		pos;
	char	in_quote;
	t_token	*tokens;
}	t_parser;

extern int	g_last_exit_status;
void		exec_builtin(t_cmd	*cmd, char ***envp);
void		exec_cmd(t_cmd *cmd, char **envp);
int			apply_redirections(t_cmd *cmd);
void		pipe_exec(t_cmd *cmd, char ***envp);
void		set_signal_prompt(void);
void		set_signal_exec(void);
void		set_signal_child(void);

t_token		*tokenize(char *input);
t_token		*create_token(t_token_type type, char *value,
				t_quote_type quote_type);
void		add_token_to_list(t_token **tokens, t_token_type type,
				char *value, t_quote_type quote_type);
void		free_tokens(t_token *tokens);
char		*extract_word(char *input, int *i, t_quote_type *quote_type);
char		*extract_quoted(char *input, int *i, char quote_char);
int			is_whitespace(char c);
void		skip_spaces(char *input, int *i);
int			is_quote(char c);
int			is_operator(char c);
int			handle_quote(char *input, int *i, t_token **tokens);
int			handle_double_operator(char *input, int *i, t_token **tokens);
int			handle_single_operator(char *input, int *i, t_token **tokens);
int			handle_word(char *input, int *i, t_token **tokens);
int			handle_operator(char *input, int *i, t_token **tokens);
t_cmd		*create_command(void);
void		free_command(t_cmd *cmd);
void		free_commands(t_cmd *cmds);
t_cmd		*build_commands(t_token *tokens);
int			count_args(t_token *tokens);
int			add_arg_to_command(t_cmd *cmd, char *arg, int *arg_index);
int			init_args_array(t_cmd *cmd, int arg_count);
int			handle_redir_in(t_cmd *cmd, t_token **current);
int			handle_redir_out(t_cmd *cmd, t_token **current);
int			handle_heredoc(t_cmd *cmd, t_token **current);
int			validate_syntax(char *input, t_token *tokens);
int			has_unclosed_quotes(char *input);
int			validate_pipes(t_token *tokens);
int			validate_redirections(t_token *tokens);
void		expand_tokens(t_token *tokens);
char		*expand_variables_in_token(char *value, int in_single_quotes);
char		*get_variable_value(char *var_name);
char		*get_env_value(char *var_name);
int			get_var_name_len(char *str);
char		*extract_var_name(char *str, int len);
int			should_expand(char *token_value);
int			is_in_single_quotes(char *original, int pos);
char		*build_expanded_string(char *str, int *i, char *var_value);
int			ft_isalnum(char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);
int			ft_strlen(char *s);
#endif