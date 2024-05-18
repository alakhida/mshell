/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:15:50 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/18 02:08:28 by alakhida         ###   ########.fr       */
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
			free(curr->value);
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
		ft_putendl_fd("bash : cd : HOME not set", 2);
		return (0);
	}
	return (1);
}

int	change_dir(char *cmd, t_env **env, char *pwd, char *oldpwd)
{
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("no such file or directory", 2);
		return (1);
	}
	else
	{
		if (chdir(cmd) != 0)
		{
			ft_putendl_fd("permission denied", 2);
			return (1);
		}
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (perror("getcwd: "), 1);
		update_pwd(env, "PWD", pwd);
		update_pwd(env, "OLDPWD", oldpwd);
		free(pwd);
	}
	return (0);
}

int	ft_cd(t_cmd *cmds, t_env **env)
{
	t_env	*current;
	char	*oldpwd;
	char	*pwd;

	current = *env;
	pwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd: "), 1);
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
		if (change_dir(cmds->cmd[1], env, pwd, oldpwd))
			return (free(oldpwd), 1);
	return (free(oldpwd), 0);
}
