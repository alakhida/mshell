/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 07:47:35 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/16 13:21:02 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe_chain(t_cmd *cmd, int pip[], int *save_stdout,
		bool pipe_chain)
{
	if (*save_stdout)
		close(*save_stdout);
	if (pipe_chain && cmd->next)
	{
		close(pip[1]);
		*save_stdout = pip[0];
	}
}

bool	pipe_chain_present(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	if (i == 1)
		return (false);
	return (true);
}

int	count_pipes(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	handling_pipe(t_cmd *cmd, int pip[], t_info *info)
{
	if (info->pipe_chain && cmd->next)
	{
		close(pip[0]);
		dup2(pip[1], STDOUT_FILENO);
		close(pip[1]);
	}
	if (info->save_stdout)
	{
		dup2(info->save_stdout, STDIN_FILENO);
		close(info->save_stdout);
	}
	if (cmd->red && handle_redirections(cmd))
	{
		exit(EXIT_FAILURE);
	}
}

void	exec_bin(t_cmd *cmd, t_info *info, t_env **env)
{
	int	pip[2];

	if (info->pipe_chain && cmd->next)
		pipe(pip);
	info->child = fork();
	if (info->child == -1)
		exit(EXIT_FAILURE);
	if (info->child == 0)
	{
		handling_pipe(cmd, pip, info);
		if (access(cmd->cmd[0], F_OK) == 0)
			info->path = cmd->cmd[0];
		else
			info->path = cmd_path(cmd->cmd[0], *env);
		if (cmd_is_builtin(cmd->cmd[0]))
			exec_built_in(cmd, env);
		else if (execve(info->path, cmd->cmd, info->envp) == -1)
		{
			ft_putendl_fd("command not found", 2);
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
	handle_pipe_chain(cmd, pip, &info->save_stdout, info->pipe_chain);
}
