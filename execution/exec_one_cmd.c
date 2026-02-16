/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:59:30 by yabodaya          #+#    #+#             */
/*   Updated: 2026/02/06 14:31:50 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

static void	permission_denied(char *cmd, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free(path);
	exit(126);
}

static void	child_exec(t_cmd *cmd, char **envp)
{
	char	*path;

	set_signal_child();
	if (setup_redirections(cmd))
		exit(1);
	path = get_path(cmd->args[0], envp);
	if (!path)
		cmd_not_found(cmd->args[0]);
	if (access(path, X_OK) != 0)
		permission_denied(cmd->args[0], path);
	execve(path, cmd->args, envp);
	perror("minishell");
	free(path);
	exit(126);
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		g_last_exit_status = 1;
		return ;
	}
	if (pid == 0)
		child_exec(cmd, envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_status = 128 + WTERMSIG(status);
}
