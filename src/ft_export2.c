/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 07:27:22 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/08 07:38:04 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (curr->varname)
			printf("declare -x %s", curr->varname);
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