/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:16:08 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/05 07:16:09 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_env(t_env **env)
{
	t_env *curr;

	if (!env)
        return ;
	curr = *env;
	if (!curr)
		return ;
	while (curr != NULL)
	{
		if (curr->value != NULL)
			printf("%s=%s\n",curr->varname, curr->value);
		curr = curr->next;
	}
}