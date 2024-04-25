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

int		check_option(char *str)
{
	int		i;

	i = 1;
	if (str[0] == '-')
		while (str[i] == 'n')
			i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int		ft_echo(t_cmd *cmnd)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (cmnd->cmd[1] != NULL)
	{
		if (check_option(cmnd->cmd[1]) == 1)
		{
				i += 2;
				n = 1;
		}
		else
			i += 1;
		while (cmnd->cmd[i])
		{
			ft_putstr(cmnd->cmd[i]);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}

int		ft_pwd(t_env *envp)
{
	while (envp->next != NULL)
	{
		if (!ft_strcnmp(envp->varname, "PWD", 3))
			printf("%s\n", envp->value);
		envp = envp->next;
	}
	return (0);
}
int	ft_strchar(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		if (s[i] == c)
			break;
	}
	return (i);
}

t_env	*add_node(char *var, char *value)
{
	t_env* new = (t_env*)malloc(sizeof(t_env));
    if (new == NULL)
        return (NULL);
    new->varname = ft_strdup(var);
    new->value = ft_strdup(value);
    new->next = NULL;
	return (new);
}

void add_node_to_back(t_env *envp, t_env *node)
{
	while (envp->next != NULL)
		envp = envp->next;
	envp->next = node;
}

int		ft_export(t_cmd *cmds, t_env *envp)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	char	*var;
	char	*value;
	while (cmds->cmd[i] != NULL)
	{
		j = ft_strchar(cmds->cmd[i], '=');
		if (j != 1)
		{
			var = (char *)malloc(j * sizeof(char));
			ft_strlcpy(var, cmds->cmd[i], j);
			value = (char *)malloc((ft_strlen(cmds->cmd[i]) - j + 1) * sizeof(char));
			ft_strlcpy(value, &cmds->cmd[i] + j, ft_strlen(cmds->cmd[i]) - j + 1);
			while (envp->next != NULL)
			{
				if (!ft_strcnmp(var, envp->varname, ft_strlen(var)))
					envp->value = value;
				else
					add_node_to_back(envp, add_node(var, value));
				envp = envp->next;
			}
		}
		else
		{
			printf("%s : not a valid identifier", cmds->cmd[i]);
			return (0);
		}
		i++;
	}
}

int		ft_unset(t_cmd *cmds,t_env *env)
{
	int		i;

	t_env *curr;

	curr = env;
	i = 1;
	while (cmds->cmd[i] != NULL)
	{
		while (curr->next != NULL)
		{
			if (!ft_strcmp(cmds->cmd[i], curr->varname))
			{
				free (curr->value);
				free (curr->varname);
				curr = curr->next;
			}
			curr = curr->next;
		}
		i++;
	}
	env = curr;
	return (0);
}

void	update_pwd(t_env *env, char *var, char *value)
{
	t_env *curr;
	
	curr = env;
	while (curr->next != NULL)
	{
		if (!ft_strcmp(curr->varname, var))
		{
			free (curr->value);
			curr->value = ft_strdup(value);
		}
		curr = curr->next;
	}
	add_node("OLDPWD", value);
}

int    ft_cd(t_cmd *cmds, t_env *env)
{
	t_env	*current;
	char	*oldpwd;
	char	*pwd;

	current = env;
	oldpwd = getcwd(NULL, 0);
    if (cmds->cmd[1] == NULL)
	{
		update_pwd(env, "OLDPWD", oldpwd);
	    pwd = getenv("HOME");
		if (!pwd)
		{
			printf("cd: HOME not set\n");
			return (0);
		}
		update_pwd(env, "PWD", pwd);
		if (chdir("HOME") != 0)
			return (0);
	}
    if (access(cmds->cmd[1], F_OK))
	{
		printf("%s : NO such file or directory\n", cmds->cmd[1]);
        return (0);
	}
	else
	{
		chdir(cmds->cmd[1]);
		pwd = getcwd(NULL,0);
		update_pwd(env, "PWD", pwd);
		update_pwd(env, "OLDPWD", oldpwd);
	}
	return (0);
}

int		ft_env(t_env *env)
{
	t_env *curr;

	curr = env;
	while (curr->next != NULL)
	{
		printf("%s=%s\n",curr->varname, curr->value);
		curr = curr->next;
	}
	return (0);
}

int		is_digit(char *str)
{
	int	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] == '\0')
		return (0);
	else 
		return (1);
}

int		ft_exit(t_cmd *cmds, t_env *env)
{
	int		ex;

	if (!cmds->cmd[1])
		exit(0);
	if (!is_digit(cmds->cmd[1]))
	{
		ex = ft_atoi(cmds->cmd[1]);
		printf("exiting...\n");
		exit(ex);
	}
	if (cmds->cmd[2])
	{
		printf("too many argument\n");
		exit(1);
	}
	if (is_digit(cmds->cmd[1]))
	{
		printf("%s: numeric argument required\n", cmds->cmd[1]);
		exit(1);
	}
}

int		check_built_in(t_cmd *cmds, t_env *envp)
{
	if (!ft_strncmp(cmds->cmd[0], "echo", 4))
		return (ft_echo(cmds));
	else if (!ft_strncmp(cmds->cmd[0], "pwd", 3))
		return (ft_pwd(envp));
	else if (!ft_strncmp(cmds->cmd[0], "export", 6))
		return (ft_export(cmds, envp));
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5))
		return (ft_unset(envp));
	else if (!ft_strncmp(cmds->cmd[0], "cd", 2))
		return (ft_cd(cmds, envp));
	else if (!ft_strncmp(cmds->cmd[0], "env", 3))
		return (ft_env(envp));
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4))
		return (ft_exit(cmds, envp));
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
			check_built_in(cmds);
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