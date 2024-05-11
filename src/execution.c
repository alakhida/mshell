/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:15:59 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/11 12:01:04 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	cmd_is_builtin(char *string)
{
	if (!ft_strcmp(string, "cd") || !ft_strcmp(string, "echo")
		|| !ft_strcmp(string, "env") || !ft_strcmp(string, "unset")
		|| !ft_strcmp(string, "export") || !ft_strcmp(string, "pwd")
		|| !ft_strcmp(string, "exit"))
		return (true);
	return (false);
}

char	*copy_path(char *s1, char *s2)
{
	size_t	len;
	size_t	len2;
	char	*result;

	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc((len + len2 + 2) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, "/");
	ft_strcat(result, s2);
	return (result);
}

char	*get_cmd_path(t_env *env)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (!ft_strcmp(env->varname, "PATH"))
		{
			path = ft_strdup(env->value);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

char	*cmd_path(char *cmd, t_env *env)
{
	t_env	*curr; 
	char	*path;
	char	*dir;
	char	*cmdpath;

	curr = env;
	if (!curr)
		return (NULL);
	path = get_cmd_path(curr);
	dir = ft_strtok(path, ":");
	while (dir != NULL)
	{
		cmdpath = copy_path(dir, cmd);
		if (access(cmdpath, X_OK) == 0)
		{
			free (path);
			path = cmdpath;
			free (cmdpath);
			break ;
		}
		free(cmdpath);
		dir = ft_strtok(NULL, ":");
	}
	return (path);
}

// void	init_args(t_cmd *cmds, t_env *env)
// {
//
// }

void	exec_cmd(t_env **env, t_cmd *cmds)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	info->pipe_chain = pipe_chain_present(cmds);
	info->saved_stdout = dup(STDOUT_FILENO);
	info->saved_stdin = dup(STDIN_FILENO);
	while (cmds)
	{
		info->envp = ms_env_dup(*env);
		info->path = cmd_path(cmds->cmd[0], *env);
		if (info->path == NULL)
		{
			printf("Command not found: %s\n", cmds->cmd[0]);
			cmds = cmds->next;
			continue ;
		}
		if (cmd_is_builtin(cmds->cmd[0]) && !info->pipe_chain)
		{
			exec_built_in(cmds, env);
		}
		else
			exec_bin(cmds, info, env);
		cmds = cmds->next;
	}
	dup2(info->saved_stdout, STDOUT_FILENO);
	dup2(info->saved_stdin, STDIN_FILENO);
	wait_child(&info->child);
}
