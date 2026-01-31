/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:06:22 by yabodaya          #+#    #+#             */
/*   Updated: 2026/01/31 01:23:08 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	char	**builtins;
	int		i;

	if (!cmd->argv[0])
		return (0);
	builtins = (char *[]){
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	exec_builtin(t_cmd *cmd, char ***envp)
{
	int	saved_stdin;
	int	saved_stdout;

	if (save_stdio(&saved_stdin, &saved_stdout))
		return ;
	if (apply_redirections(cmd))
	{
		restore_stdio(saved_stdin, saved_stdout);
		g_exit_status = 1;
		return ;
	}
	if (!ft_strcmp(cmd->argv[0], "echo"))
		echo_bi(cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		cd_bi(cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		pwd_bi(cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		export_bi(cmd, envp);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		unset_bi(cmd, envp);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		env_bi(cmd, *envp);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		exit_bi(cmd);
	restore_stdio(saved_stdin, saved_stdout);
}
