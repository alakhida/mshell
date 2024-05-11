/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:15:59 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/11 07:59:57 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

bool	cmd_is_builtin(char *string)
{
	if (!ft_strcmp(string, "cd") || !ft_strcmp(string, "echo")
		|| !ft_strcmp(string, "env") || !ft_strcmp(string, "unset")
		|| !ft_strcmp(string, "export") || !ft_strcmp(string, "pwd")
		|| !ft_strcmp(string, "exit"))
		return (true);
	return (false);
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

char	*ft_strtok(char *str, const char *delim)
{
    static char *s = NULL;
    char *ret;
    int i;

    if (str)
        s = str;
    if (!s)
        return (NULL);
    i = 0;
    while (s[i])
    {
        if (ft_strchr(delim, s[i]))
        {
            s[i] = '\0';
            ret = s;
            s = s + i + 1;
            return (ret);
        }
        i++;
    }
    ret = s;
    s = NULL;
    return (ret);
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
		return NULL;
	ft_strcpy(result, s1);
	ft_strcat(result, "/");
	ft_strcat(result, s2);
	return (result);
}

char     *cmd_path(char *cmd, t_env *env)
{
    t_env  *curr; 
    char    *path;
    char    *dir;
	char	*cmdpath;

    curr = env;
    if (!curr)
        return (NULL);
    while (curr)
    {
        if (ft_strcmp(curr->varname, "PATH") == 0)
            break;
        curr = curr->next;
    }
    path = ft_strdup(curr->value);
    dir = ft_strtok(path, ":");
     while (dir != NULL)
     {
        cmdpath = copy_path(dir, cmd);
        if (access(cmdpath, X_OK) == 0)
        {
            free (path);
            path = cmdpath;
            free (cmdpath);
            break;
        }
        free(cmdpath);
        dir = ft_strtok(NULL, ":");
    }
    return path;
}

void exec_cmd(t_env **env, t_cmd *cmds)
{
    bool pipe_chain = pipe_chain_present(cmds);
    int save_stdout = 0;
    pid_t child;

    while (cmds)
	{
        char **envp = ms_env_dup(*env);
        char *path = cmd_path(cmds->cmd[0], *env);
        if (path == NULL)
		{
            printf("Command not found: %s\n", cmds->cmd[0]);
            cmds = cmds->next;
            continue;
        }
        if (cmd_is_builtin(cmds->cmd[0]) && !pipe_chain)
            exec_built_in(cmds, env);
        else
            exec_bin(cmds, envp, path, &save_stdout, &child, pipe_chain);
        cmds = cmds->next;
    }
    wait_child(&child);
}

