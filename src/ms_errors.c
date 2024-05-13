/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:27 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/13 16:25:28 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ms_errors(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i + 1])
	{
		if (ms_ctrlop(cmd[i]) != NONE && ms_ctrlop(cmd[i + 1]) != NONE)
		{
			printf("minishell: syntax error\n");
			return (false);
		}
		i++;
	}
	if (ms_ctrlop(cmd[i + 1]) != NONE)
	{
		printf("minishell: syntax error\n");
		return (false);
	}
	return (true);
}
