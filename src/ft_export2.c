/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:27:22 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/17 08:36:27 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_node_to_back(t_env **envp, t_env *node)
{
	t_env	*current;

	current = *envp;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

void	ft_env_export(t_env **env)
{
	t_env	*curr;

	if (!env)
		return ;
	curr = *env;
	if (!curr)
		return ;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->varname, "?"))
		{
			if (curr->varname)
				printf("declare -x %s", curr->varname);
			if (curr->value)
				printf("=%s", curr->value);
			printf("\n");
		}
		curr = curr->next;
	}
}

void	export_to_list(t_env *current, char *var, char *value)
{
	while (current)
	{
		if (!ft_strcmp(var, current->varname))
		{
			free(current->value);
			current->value = value;
			free(var);
			break ;
		}
		else if (current->next == NULL)
		{
			current->next = add_node(var, value);
			break ;
		}
		current = current->next;
	}
}

char	*cpy_value(char *cmd, char *var, char *value, int j)
{
	int	i;

	i = ft_strlen(cmd);
	if (i <= 0)
		return (NULL);
	value = val_malloc(cmd, var, j);
	if (!value)
		return (NULL);
	ft_strlcpy(value, (cmd + j + 1), i - j + 1);
	return (value);
}

void	ft_export_var(char *var, t_env **envp, t_env *current)
{
	while (current)
	{
		if (var == current->varname)
		{
			current->varname = var;
			current->value = NULL;
			break ;
		}
		else
		{
			current = add_node(var, NULL);
			add_node_to_back(envp, current);
			break ;
		}
		current = current->next;
	}
}
