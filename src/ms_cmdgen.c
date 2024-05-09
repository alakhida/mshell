/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdgen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 06:38:46 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/09 07:46:53 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void get_redir(t_cmd **cmd)
{
	t_cmd *head = *cmd;
	int i = 0;
	while(head)
	{
		i = 0;
		while(head->cmd[i])
		{
			
			head->red = malloc(sizeof(e_type));
			if(!strcmp(head->cmd[i],">") && strcmp(head->cmd[i],">>"))
			{
				head->red->file = head->cmd[i + 1];
				printf("file %s\n",head->red->file);
				head->red->type = RREDIR;
			}
			else if(!strcmp(head->cmd[i],"<") && strcmp(head->cmd[i],"<<"))
			{
				head->red->file = head->cmd[i - 1];
				printf("file %s\n",head->red->file);
				head->red->type = LREDIR;
			}
			else if(!strcmp(head->cmd[i],"<<"))
			{
				head->red->file = head->cmd[i - 1];
				printf("file %s\n",head->red->file);
				head->red->type = HEREDOC;
			}
			else if(!strcmp(head->cmd[i],">>"))
			{
				
				head->red->file = head->cmd[i + 1];
				printf("file %s\n",head->red->file);
				head->red->type = APPEND;
			}
			i++;
		}
		
		head = head->next;
	}
	
}
t_cmd	*ms_cmdgen(char **cmd)
{
	t_cmd *head = NULL;
	t_cmd *current = NULL;
	int checkpoint = 0;

	int i = 0;
	current = (t_cmd *)malloc(sizeof(t_cmd));
	while (cmd && cmd[i])
	{
		if (ms_ctrlop(cmd[i]) == PIPE || cmd[i + 1] == NULL)
		{
			// printf("check: %d   i: %d\n",checkpoint, i + 1);
			if (cmd[i + 1] == NULL) 
				current->cmd = ft_arrslice(cmd, checkpoint, i + 1);
			else 
				current->cmd = ft_arrslice(cmd, checkpoint, i);
				if (checkpoint == 0)
					head = current;
			checkpoint = i + 1;
			current->next = NULL;
			if (cmd[i + 1] != NULL) {
					current->next = (t_cmd *)malloc(sizeof(t_cmd));
					ft_bzero(current->next, sizeof(t_cmd));
					current = current->next;
			}
			i = checkpoint;
		}
		else
			i++;
	}
	get_redir(&head);
	return head;
}

