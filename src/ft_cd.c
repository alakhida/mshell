/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:15:50 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/11 10:58:25 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_search(char *ptr, t_env *head)
{
	while (head)
	{
		if (ft_strcmp(head->varname, ptr) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	update_pwd(t_env **env, char *var, char *value)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->varname, var))
		{
			free (curr->value);
			curr->value = ft_strdup(value);
			break ;
		}
		if (curr->next == NULL)
		{
			curr->next = add_node("OLDPWD", value);
			break ;
		}
		curr = curr->next;
	}
}

int	check_home(t_env *home)
{
	if (chdir(env_search("HOME", home)) != 0)
	{
		printf("cd: HOME not set\n");
		return (0);
	}
	return (1);
}

void	change_dir(char *cmd, t_env **env, char *pwd, char *oldpwd)
{
	if (access(cmd, F_OK) != 0)
	{
		printf("%s : no such file or directory\n", cmd);
		return ;
	}
	else
	{
		chdir(cmd);
		pwd = getcwd(NULL, 0);
		update_pwd(env, "PWD", pwd);
		update_pwd(env, "OLDPWD", oldpwd);
	}
}

void	ft_cd(t_cmd *cmds, t_env **env)
{
	t_env	*current;
	char	*oldpwd;
	char	*pwd;

	current = *env;
	pwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (cmds->cmd[1] == NULL)
	{
		if (check_home(current) == 1)
		{
			update_pwd(env, "OLDPWD", oldpwd);
			pwd = env_search("HOME", current);
			update_pwd(env, "PWD", pwd);
		}
	}
	else if (cmds->cmd[1])
		change_dir(cmds->cmd[1], env, pwd, oldpwd);
}
