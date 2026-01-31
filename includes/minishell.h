/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:49:19 by yabodaya          #+#    #+#             */
/*   Updated: 2026/01/31 01:01:56 by yabodaya         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**argv;
	int				infile;
	int				outfile;
	int				is_builtin;
	struct s_cmd	*next;
}	t_cmd;
extern int	g_exit_status;
void	exec_builtin(t_cmd	*cmd, char ***envp);
void	exec_cmd(t_cmd *cmd, char **envp);
int		apply_redirections(t_cmd *cmd);
#endif