/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:49:14 by alakhida          #+#    #+#             */
/*   Updated: 2024/02/18 23:36:03 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ms_prompt(void)
{
	char *cmd;

	cmd = readline("$> ");
	add_history(cmd);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

t_cmd *ms_parse_cmd(char *cmd)
{
	t_cmd *cmds;
	t_cmd *itr;
	char **pipe_cmds;

	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	pipe_cmds = ft_split(cmd, '|');
	int i = 0;
	itr = cmds;
	while (pipe_cmds[i])
	{
		itr->cmd = ft_split(pipe_cmds[i], ' ');
		itr->is_pipe = false;
		itr->next = NULL;
		if (pipe_cmds[i + 1])
		{
			itr->next = (t_cmd *)malloc(sizeof(t_cmd));
			itr->is_pipe = true;
			itr = itr->next;
		}
		i++;
	}
	return (cmds);
}

int	cmd_exists(char *cmd, char **envp)
{
	int i = 0;
	while (envp[i])
	{
		if (strncmp("PATH=", envp[i], 5) == 0)
			break;
		i++;
	}
	char **holder = ft_split(envp[i], '=');
	char *path = ft_strdup(holder[1]);
	free (holder[0]);
	free (holder[1]);
	free (holder);
	holder = ft_split(path, ':');
	i = 0;
	while (holder[i])
	{
		char *cmdpath;
		cmdpath = ft_strjoin(holder[i], "/");
		cmdpath = ft_strjoin(cmdpath, cmd);
		if (access(cmdpath, X_OK) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	exec(t_cmd *cmds, char **envp)
{
	while (cmds)
	{
		if (cmd_exists(cmds->cmd[0], envp) == false)
			printf("%s does not exist\n", cmds->cmd[0]);
		else
		{
		}
		cmds = cmds->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	char *cmd;
	t_cmd *cmds;

	cmd = NULL;
	while(1)
	{
		cmd = ms_prompt();
		if (cmd == NULL)
			break;
		cmds = ms_parse_cmd(cmd);
		exec(cmds, envp);
	}
}