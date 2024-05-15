/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:16:08 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/15 06:16:01 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_env **env)
{
	t_env	*curr;

	if (!env || !(*env))
		return (-1);
	curr = *env;
	while (curr != NULL)
	{
		if (curr->value != NULL && curr->value[0] != '\0')
			printf("%s=%s\n", curr->varname, curr->value);
		curr = curr->next;
	}
	return (0);
}

int	ft_export(t_cmd *cmds, t_env **envp)
{
	if (!cmds->cmd[1])
		ft_env_export(envp);
	else
		exporting(cmds, envp);
	return (0);
}