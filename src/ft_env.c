/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:16:08 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/09 04:11:56 by alakhida         ###   ########.fr       */
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