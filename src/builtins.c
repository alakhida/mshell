/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:29:33 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/05 03:21:28 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int		ft_pwd(t_cmd *cmds)
{
	char    *buff;

    if (cmds->cmd[1])
    {
        printf("%s: too many arguments\n", cmds->cmd[0]);
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
		if (s[i] == c)
			break;
		i++;
	}
	return (i);
}

t_env	*add_node(char *var, char *value)
{
	t_env* new = (t_env*)malloc(sizeof(t_env));
    if (new == NULL)
        return (NULL);
    new->varname = var;
    new->value = value;
    new->next = NULL;
	return (new);
}

void add_node_to_back(t_env **envp, t_env *node)
{
	t_env *current;

	current = *envp;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

void		ft_env_export(t_env **env)
{
	t_env *curr;

	if (!env)
        return ;
	curr = *env;
	if (!curr)
		return ;
	while (curr != NULL)
	{
		if (curr->varname)
		printf("declare -x %s",curr->varname);
		if (curr->value)
			printf("=%s", curr->value);
		printf("\n");
		curr = curr->next;
	}
}

void	ft_export_var(char *var, t_env **envp, t_env *current)
{
	while (current)
			{
				if (var == current->varname)
				{
					current->varname = var;
					current->value = NULL;
					break;
				}
				else
				{
					current = add_node(var, NULL);
					add_node_to_back(envp, current);
					break;
				}
			current = current->next;
			}
}

void ft_export(t_cmd *cmds, t_env **envp)
{
	int		i;
	int		j;
	t_env	*current;
	char	*var;
	char	*value;

	i = 1;
	j = 0;
	current = *envp;
	if (!cmds->cmd[1])
		ft_env_export(envp);
	while (cmds->cmd[i] != NULL)
	{
		j = ft_strchar(cmds->cmd[i], '=');
		var = (char *)malloc(j + 1 * sizeof(char));
		ft_strlcpy(var, cmds->cmd[i], j + 1);
		if (!var)
			return ;
		if (j != ft_strlen(cmds->cmd[i]))
		{
			value = (char *)malloc((ft_strlen(cmds->cmd[i]) - j) * sizeof(char));
			if (j != 0)
			{
				if (!value)
					return ;
				ft_strlcpy(value, (cmds->cmd[i] + j + 1), ft_strlen(cmds->cmd[i]) - j);
				while (current)
				{
					if (!ft_strcmp(var, current->varname))
					{
						free(current->value);
						current->value = value;
						break;
					}
					else if (current->next == NULL)
					{
						current->next = add_node(var, value);
						break;
					}
					current = current->next;
				}
			}
			else
			{
				printf("%s : not a valid identifier\n", cmds->cmd[i]);
				return ;
			}
		}
		else if (j == ft_strlen(cmds->cmd[i]))
			ft_export_var(var, envp, current);
		current = *envp;
		i++;
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

int		exec_built_in(t_cmd *cmds, t_env **envp)
{
	if (!ft_strncmp(cmds->cmd[0], "echo", 4))
		ft_echo(cmds);
	else if (!ft_strncmp(cmds->cmd[0], "env", 3))
        ft_env(envp);
	else if (!ft_strncmp(cmds->cmd[0], "pwd", 3))
		ft_pwd(cmds);
	else if (!ft_strncmp(cmds->cmd[0], "export", 6))
		ft_export(cmds, envp);
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5))
		ft_unset(cmds, envp);
	else if (!ft_strncmp(cmds->cmd[0], "cd", 2))
		ft_cd(cmds, envp);
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4))
		ft_exit(cmds);
    return (0);
}