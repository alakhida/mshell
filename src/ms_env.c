/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:15 by calmouht          #+#    #+#             */
/*   Updated: 2024/04/16 15:33:41 by calmouht         ###   ########.fr       */
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
		if (envp[i + 1] != NULL){
			env->next = (t_env *)malloc(sizeof(t_env));
			env = env->next;
		}
		else
			env->next = NULL;
		i++;
	}
	return (head);
}

t_env	*ms_env_search(char *ptr, t_env *head)
{
	while (head)
	{
		if (ft_strcmp(head->varname, ptr) == 0)
		{
			// printf("returned %s %s \n", head->varname, head->value);
			return (head);
		}
		head = head->next;
	}
	printf("return NULL\n");
	return(NULL);
}

char	*expanded(char *cmd)
{
	// printf("expanded =>%s",cmd);
	int		i;
	int		k;
	int		ex_len;
	char	*l7asol;

	i = 0;
	k = 0;
	while ((cmd[i]))
	{
		if (cmd[i] == '$')
		{
			i++;
			k = i;
			while (ft_isalnum(cmd[k]) || cmd[k] == '_' || cmd[k] == '?'
				|| cmd[k] == '=')
				k++;
			break ;
		}
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
				i++;
		}
		i++;
	}
	if (k == 0)
	{
		// printf("return NULL \n");
		return (NULL);
	}
	ex_len = k - i;
	l7asol = malloc(sizeof(char) * (ex_len + 1));
	ft_strlcpy(l7asol, &cmd[i], ex_len + 1);
	// printf("return %s\n",l7asol);
	return (l7asol);
}
