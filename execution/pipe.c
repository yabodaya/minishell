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
	dup2(in_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (cmd->is_builtin)
		exec_builtin(cmd, envp);
	else
		child_exec(cmd, envp);
	exit(0);
}

static int	pipe_parent(int *pipefd, int in_fd)
{
	close(pipefd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	return (pipefd[0]);
}

void	pipe_exec(t_cmd *cmd, char ***envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		in_fd;

	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (pipe(pipefd) == -1)
			return ;
		pid = fork();
		if (pid == 0)
			pipe_child(cmd, envp, pipefd, in_fd);
		else if (pid > 0)
			in_fd = pipe_parent(pipefd, in_fd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
}
