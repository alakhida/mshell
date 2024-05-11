/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:16:08 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/11 11:04:49 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env **env)
{
	t_env	*curr;

	if (!env || !(*env))
		return ;
	curr = *env;
	while (curr != NULL)
	{
		if (curr->value != NULL && curr->value[0] != '\0')
			printf("%s=%s\n", curr->varname, curr->value);
		curr = curr->next;
	}
}


void	ft_export(t_cmd *cmds, t_env **envp)
{
	if (!cmds->cmd[1])
		ft_env_export(envp);
	else
		exporting(cmds, envp);
}