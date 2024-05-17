/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdgen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 06:38:46 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/17 07:04:45 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ms_push_back_node(t_cmd *current)
{
	current->next = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	return (current->next);
}

int	calc(char *curr_tokens, int i)
{
	if (curr_tokens == NULL)
		return (i + 1);
	return (i);
}

t_cmd	*ms_cmdgen(char **cmd)
{
	t_cmd	*head;
	t_cmd	*current;
	int		checkpoint;
	int		i;

	checkpoint = 0;
	i = 0;
	current = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	while (cmd && cmd[i])
	{
		if (ms_ctrlop(cmd[i]) == PIPE || cmd[i + 1] == NULL)
		{
			current->cmd = ft_arrslice(cmd, checkpoint, calc(cmd[i + 1], i));
			if (checkpoint == 0)
				head = current;
			checkpoint = i + 1;
			if (cmd[i + 1] != NULL)
				current = ms_push_back_node(current);
		}
		i++;
	}
	current->count = i;
	get_redir(&head);
	return (head);
}

void	ms_cmdgen_norm(char **cmd, t_cmd *current, int i, int checkpoint)
{
	if (cmd[i + 1] == NULL)
		current->cmd = ft_arrslice(cmd, checkpoint, i + 1);
	else
		current->cmd = ft_arrslice(cmd, checkpoint, i);
	checkpoint = i + 1;
}

void	ms_cmdgen_norm2(char **cmd, t_cmd *current, int i)
{
	if (cmd[i + 1] != NULL)
	{
		current->next = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
		current = current->next;
	}
}
