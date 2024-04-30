#include "../includes/minishell.h"

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
			ft_putstr_fd(cmnd->cmd[i], 1);
            if (cmnd->cmd[i + 1] != NULL)
                ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}

int		ft_pwd(t_cmd *cmds)
{
	char    *buff;

    if (cmds->cmd[1])
    {
        printf("%s: Too many arguments\n", cmds->cmd[0]);
        return (0);
    }
    buff = getcwd(NULL,0);
    if (buff != NULL)
        printf("%s\n", buff);
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
			ft_strlcpy(value, (cmds->cmd[i] + j), ft_strlen(cmds->cmd[i]) - j + 1);
			while (envp->next != NULL)
			{
				if (!ft_strcmp(var, envp->varname))
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
    return (0);
}

int		ft_unset(t_cmd *cmds, t_env **env)
{
	t_env *curr;
	t_env *tmp;
	int		i;

	i = 1;
	curr = *env;
	while (cmds->cmd[i])
	{
		if (!ft_strcmp(cmds->cmd[i], curr->varname))
		{
			free(curr->value);
			free(curr->varname);
			*env = curr->next;
			free(curr);
		}
		else
		{
			while (curr)
			{
				if (!ft_strcmp(cmds->cmd[i], curr->next->varname))
				{
					free(curr->next->value);
					free(curr->next->varname);
					tmp = curr->next;
					if (curr->next->next)
						curr->next = curr->next->next;
					else
						curr->next = NULL;
					free(tmp);
					break;
				}
				curr = curr->next;
			}
		}
		i++;
		curr = *env;
	}
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

void    ft_cd(t_cmd *cmds, t_env *env)
{
	t_env	*current;
	char	*oldpwd;
	char	*pwd;

	current = env;
	oldpwd = getcwd(NULL, 0);
    if (cmds->cmd[1] == NULL)
	{
		chdir(getenv("HOME"));
		pwd = getcwd(NULL,0);
		printf("%s\n", pwd);
		update_pwd(env, "OLDPWD", oldpwd);
	    pwd = getenv("HOME");
		if (!pwd)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		update_pwd(env, "PWD", pwd);
		if (chdir(getenv("HOME")) != 0)
			return ;
	}
	if (cmds->cmd[1])
	{
    if (access(cmds->cmd[1], F_OK) != 0)
	{
		printf("%s : NO such file or directory\n", cmds->cmd[1]);
        return ;
	}
	else
	{
		chdir(cmds->cmd[1]);
		pwd = getcwd(NULL,0);
		update_pwd(env, "PWD", pwd);
		update_pwd(env, "OLDPWD", oldpwd);
	}
	}
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

int    ft_exit(t_cmd *cmds)
{
	int		ex;

	ex = 0;
	if (!cmds->cmd[1])
		exit(0);
	if (cmds->cmd[2])
	{
		printf("too many argument\n");
		exit(ex);
	}
	if (!is_digit(cmds->cmd[1]))
	{
		ex = ft_atoi(cmds->cmd[1]);
		printf("exiting...\n");
		exit(ex);
	}
	if (is_digit(cmds->cmd[1]))
	{
		printf("%s: numeric argument required\n", cmds->cmd[1]);
		exit(1);
	}
    return (0);
}

int		ft_env(t_env *env)
{
	t_env *curr;

	if (!env)
        return (0);
	curr = env;
	while (curr->next != NULL)
	{
		printf("%s=%s\n",curr->varname, curr->value);
		curr = curr->next;
	}
	return (0);
}
int		check_built_in(t_cmd *cmds, t_env **envp)
{
	if (!ft_strncmp(cmds->cmd[0], "echo", 4))
		ft_echo(cmds);
	else if (!ft_strncmp(cmds->cmd[0], "env", 3))
        ft_env(*envp);
	else if (!ft_strncmp(cmds->cmd[0], "pwd", 3))
		ft_pwd(cmds);
	else if (!ft_strncmp(cmds->cmd[0], "export", 6))
		return (ft_export(cmds, *envp));
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5))
		ft_unset(cmds, envp);
	else if (!ft_strncmp(cmds->cmd[0], "cd", 2))
		ft_cd(cmds, *envp);
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4))
		return (ft_exit(cmds));
    return (0);
}