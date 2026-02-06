/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabodaya <yabodaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:52:44 by yabodaya          #+#    #+#             */
/*   Updated: 2026/02/06 15:31:50 by yabodaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_bi(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	g_last_exit_status = 0;
}

void	exit_bi(t_cmd *cmd)
{
	long	exit_code;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!cmd->args[1])
		exit(g_last_exit_status);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_last_exit_status = 1;
		return ;
	}
	exit_code = ft_atol(cmd->args[1]);
	exit((unsigned char)exit_code);
}

void	unset_bi(t_cmd *cmd, char ***envp)
{
	int		i;
	char	**new_env;
	int		j;

	i = 1;
	while (cmd->args[i])
	{
		j = 0;
		new_env = malloc(sizeof(char *) * (env_size(*envp)));
		while ((*envp)[j])
		{
			if (!starts_with((*envp)[j], cmd->args[i]))
			{
				new_env[j] = ft_strdup((*envp)[j]);
				j++;
			}
			else
				free((*envp)[j]);
			j++;
		}
		new_env[j] = NULL;
		free_array(envp);
		*envp = new_env;
		i++;
	}
	g_last_exit_status = 0;
}

void	export_bi(t_cmd *cmd, char ***envp)
{
	int	i;
	int	j;
	int	found;

	i = 1;
	while (cmd->args[i])
	{
		found = 0;
		j = 0;
		while ((*envp)[j])
		{
			if (starts_with((*envp)[j], cmd->args[i]))
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			add_env_variable(envp, cmd->args[i]);
		i++;
	}
	g_last_exit_status = 0;
}
