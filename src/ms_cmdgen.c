/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdgen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 06:38:46 by calmouht          #+#    #+#             */
/*   Updated: 2024/03/08 08:23:29 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ms_cmdgen(char **cmd)
{
	int i;
	int checkpoint;
	t_cmd *head;
	t_cmd *current;

	head = (t_cmd *)malloc(sizeof(t_cmd));
	current = head;
	checkpoint = 0;
	i = 0;
	while (cmd && cmd[i] != NULL)
	{
		if (ms_ctrlop(cmd[i]) == PIPE || cmd[i + 1] == NULL)
		{
			if (cmd[i + 1] == NULL)
				i++;
			printf("check: %d   i: %d\n",checkpoint, i);
			current->cmd = ft_arrslice(cmd, checkpoint, i);
			checkpoint = i + 1;
			current->next = (t_cmd *)malloc(sizeof(t_cmd));
			current = current->next;
			current->next = NULL;
		}
		i++;
	}
	return (head);
}