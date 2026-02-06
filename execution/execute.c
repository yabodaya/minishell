/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:39:44 by yabodaya          #+#    #+#             */
/*   Updated: 2026/02/06 11:35:54 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_cmd	*cmd, char ***envp)
{
	if (!cmd)
		return ;
	if (!cmd->next)
	{
		if (isbuiltin(cmd))
			exec_builtin(cmd, envp);
		else
			exec_cmd(cmd, envp);
	}
	else
		pipe_exec(cmd, envp);
}
