/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:15 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/17 06:34:19 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	node_count(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*ms_env_new(char **envp)
{
	t_env	*env;
	t_env	*head;
	int		i;

	i = 0;
	head = (t_env *)malloc(sizeof(t_env));
	env = head;
	while (envp[i])
	{
		env->varname = ft_strldup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		env->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (envp[i + 1] != NULL)
		{
			env->next = (t_env *)malloc(sizeof(t_env));
			env = env->next;
		}
		else
			env->next = NULL;
		i++;
	}
	env->next = (t_env *)malloc(sizeof(t_env));
	env->next->varname = ft_strdup("?");
	env->next->value = ft_itoa(0);
	return (head);
}

t_env	*ms_env_search(char *ptr, t_env *head)
{
	while (head)
	{
		if (ft_strcmp(head->varname, ptr) == 0)
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

int	express(char **cmd, int *i, int *k)
{
	if ((*cmd)[*i] == '$' && (*cmd)[(*i) + 1] == '?')
	{
		printf("%c , %c \n", (*cmd)[*i], (*cmd)[(*i) + 1]);
		*k = 2;
		return (1);
	}
	if ((*cmd)[(*i)] == '$')
	{
		(*i)++;
		*k = *i;
		while (ft_isalnum((*cmd)[(*k)]) || ft_strchr("_?=",
				(*cmd)[(*k)]) != NULL)
		{
			(*k)++;
			printf("\1");
		}
		return (1);
	}
	if ((*cmd)[(*i)] == '\'')
	{
		(*i)++;
		while ((*cmd)[(*i)] != '\'')
			(*i)++;
	}
	return (0);
}

char	*expanded(char *cmd, int *exit_status)
{
	int		i;
	int		k;
	int		ex_len;
	char	*l7asol;

	i = -1;
	k = 0;
	while ((cmd[++i]))
	{
		if (cmd[i] == '$' && is_special(&cmd[i + 1]))
			return (NULL);
		if (express(&cmd, &i, &k) == 1)
			break ;
	}
	if (k == 0)
		return (NULL);
	else if (k == 2)
		return (ft_strdup("?"));
	ex_len = k - i;
	l7asol = malloc(sizeof(char) * (ex_len + 1));
	ft_strlcpy(l7asol, &cmd[i], ex_len + 1);
	return (l7asol);
}
