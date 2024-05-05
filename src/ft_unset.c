/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:16:16 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/05 07:16:17 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_unset_norm(t_cmd *cmds, t_env *curr)
{
    t_env *tmp;
    int     i;

    i = 1;
    while (curr->next)
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

int		ft_unset(t_cmd *cmds, t_env **env)
{
	t_env *curr;
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
			ft_unset_norm(cmds, curr);
		i++;
		curr = *env;
	}
	return (0);
}