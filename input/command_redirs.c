/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:27:54 by sounania          #+#    #+#             */
/*   Updated: 2026/02/06 14:18:21 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redir_in(t_cmd *cmd, t_token **current)
{
	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
		return (0);
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = strdup((*current)->value);
	if (!cmd->infile)
		return (0);
	return (1);
}

int	handle_redir_out(t_cmd *cmd, t_token **current)
{
	int	is_append;

	is_append = ((*current)->type == TOKEN_REDIR_APPEND);
	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
		return (0);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = strdup((*current)->value);
	if (!cmd->outfile)
		return (0);
	cmd->append = is_append;
	return (1);
}

int	handle_heredoc(t_cmd *cmd, t_token **current)
{
	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
		return (0);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_delim = strdup((*current)->value);
	if (!cmd->heredoc_delim)
		return (0);
	return (1);
}
