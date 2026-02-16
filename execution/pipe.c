/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:45:10 by yabodaya          #+#    #+#             */
/*   Updated: 2026/02/06 14:39:01 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	pipe_child(t_cmd *cmd, char **envp, int *pipefd, int in_fd)
{
	set_signal_child();

	dup2(in_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pipefd[1], STDOUT_FILENO);

	close(pipefd[0]);
	close(pipefd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);

	if (setup_redirections(cmd))
		exit(1);

	if (is_builtin(cmd))
	{
		exec_builtin_core(cmd, envp);
		exit(g_last_exit_status);
	}
	else
		child_exec(cmd, envp);
}

void	pipe_exec(t_cmd *cmd, char ***envp)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;

	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (pipe(pipefd) == -1)
			return ;
		pid = fork();
		if (pid == 0)
			pipe_child(cmd, *envp, pipefd, in_fd);
		else
		{
			close(pipefd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			in_fd = pipefd[0];
			last_pid = pid;
		}
		cmd = cmd->next;
	}

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_status = 128 + WTERMSIG(status);

	while (wait(NULL) > 0)
		;
}
