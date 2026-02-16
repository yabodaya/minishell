/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:06:22 by yabodaya          #+#    #+#             */
/*   Updated: 2026/02/06 18:47:02 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	save_stdio(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
		return (1);
	return (0);
}

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	is_builtin(t_cmd *cmd)
{
	char	**builtins;
	int		i;

	if (!cmd->args[0])
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
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void exec_builtin_core(t_cmd *cmd, char **envp)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		echo_bi(cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		cd_bi(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd_bi(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export_bi(cmd, &envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset_bi(cmd, &envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		env_bi(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		exit_bi(cmd);
}

void	exec_builtin(t_cmd *cmd, char ***envp)
{
	int	saved_stdin;
	int	saved_stdout;

	if (save_stdio(&saved_stdin, &saved_stdout))
		return ;
	if (setup_redirections(cmd))
	{
		restore_stdio(saved_stdin, saved_stdout);
		g_last_exit_status = 1;
		return ;
	}
	if (!ft_strcmp(cmd->args[0], "echo"))
		echo_bi(cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		cd_bi(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd_bi(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export_bi(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset_bi(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		env_bi(cmd, *envp);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		exit_bi(cmd);
	restore_stdio(saved_stdin, saved_stdout);
}
