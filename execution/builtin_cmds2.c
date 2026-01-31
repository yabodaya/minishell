/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 01:22:43 by yabodaya          #+#    #+#             */
/*   Updated: 2026/01/31 01:23:18 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_bi(t_cmd *cmd)
{
	char	buf[1024];

	(void)cmd;
	if (getcwd(buf, sizeof(buf)))
	{
		write(STDOUT_FILENO, buf, ft_strlen(buf));
		write(STDOUT_FILENO, "\n", 1);
		g_exit_status = 0;
	}
	else
	{
		perror("pwd");
		g_exit_status = 1;
	}
}

void	cd_bi(t_cmd *cmd)
{
	if (!cmd->argv[1])
	{
		g_exit_status = 0;
		return ;
	}
	if (chdir(cmd->argv[1]) == -1)
	{
		perror("cd");
		g_exit_status = 1;
	}
	else
		g_exit_status = 0;
}

void	echo_bi(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		write (STDOUT_FILENO, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write (STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write (STDOUT_FILENO, "\n", 1);
	g_exit_status = 0;
}
