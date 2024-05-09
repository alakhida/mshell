/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 07:47:35 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/09 07:49:53 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe_chain(t_cmd *cmd, int pip[], int *save_stdout, bool pipe_chain)
{
	if (pipe_chain && cmd->next)
	{
		close(pip[1]);
		*save_stdout = pip[0];
	}
}

void	handling_pipe(t_cmd *cmd, int pip[], int *save_stdout, bool pipe_chain)
{
	if (pipe_chain && cmd->next)
	{
		close(pip[0]);
		dup2(pip[1], STDOUT_FILENO);
		close(pip[1]);
	}
	if (*save_stdout)
	{
		dup2(*save_stdout, STDIN_FILENO);
		close(*save_stdout);
	}
}

void	exec_bin(t_cmd *cmd, char **envp, char *path, int *save_stdout, pid_t *child, bool pipe_chain)
{
	int pip[2];

	if (pipe_chain && cmd->next)
		pipe(pip);
	*child = fork();
	if (*child == -1)
		exit(EXIT_FAILURE);
	if (*child == 0)
	{
		handling_pipe(cmd, pip, save_stdout, pipe_chain);
		if (execve(path, cmd->cmd, envp) == -1)
			exit(EXIT_FAILURE);
	}
	handle_pipe_chain(cmd, pip, save_stdout, pipe_chain);
}

void wait_child(pid_t *child)
{
    while (wait(child) > 0);
}
