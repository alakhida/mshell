/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:28:51 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/12 08:12:26 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int t_strlen(char **str)
{
	int i = 0;
	int size = 0;
	while(str[i])
	{
		size += ft_strlen(str[i]);
		i++;
	}
	return size;

}
char **tarray_copy(char **a)
{
	char **cpy = malloc(sizeof(char *) * t_strlen(a));
	int i = 0;
	while(a[i])
	{
		cpy[i] = ft_strdup(a[i]);
		i++;
	}
	cpy[i] = NULL;
	return cpy;
}

void get_new_args(t_cmd **cmd)
{
	t_cmd *head = *cmd;
	char *tmp = NULL;
	int i = 0;
	while(head)
	{
		if(head->red)
		{ 
			while(head->cmd && head->cmd[i])
			{
				if(head->cmd[i] && (!strcmp(head->cmd[i],">>") || !strcmp(head->cmd[i],">") || !strcmp(head->cmd[i],"<<") || !strcmp(head->cmd[i],"<")))
				{
					tmp = head->cmd[i];
					head->cmd[i] = NULL;
					head->args = tarray_copy(head->cmd);
					head->cmd[i] = tmp; 
					break;
				}
				i++;
			}
		}
		else
		{
			head->args = tarray_copy(head->cmd);
		}
		// fe had ster gha bdelt cmd b args bash n testy makhnach nkhdmo hka khask tsift args l serghini o tfreeeyi **cmd o **args
		head->cmd = head->args;
		head = head->next;
	}
	
}

int is_special(char *tab)
{
	if (ms_ctrlop(tab) == RREDIR  || ms_ctrlop(tab) == LREDIR || 
		ms_ctrlop(tab) == PIPE|| ms_ctrlop(tab) == HEREDOC ||
		ms_ctrlop(tab) == APPEND)
	{
		return 1;
	}
	
	return 0;
}

int check_errors(char **tab)
{
	int i = 0;
	while (tab[i])
	{
		// printf("%d ;; %s\n", i , tab[i]);
		if ((is_special(tab[i]) == 1 && is_special(tab[i+1]) == 1) ){
				exits(2);
				return 1;
		}
		i++;
		// continue;
	// if (ms_ctrlop(tab[i+1])!= NONE /*|| tab[i+1] == NULL*/)
	// 		{
	// 		if ((is_special(tab[i]) && is_special(tab[i+1])) )
	// 			exits(2);
	// 			return 1;
	// 		}
	// 	i++;
	}
	return 0;
}

void printlist(t_cmd **head)
{
	t_cmd *curr;
	curr = *head;
	int i = 0;
	// printf("count = %d\n ", curr->count);
	while (curr)
	{
		while (i < curr->count)
		{
			printf("%d %s\n", i ,curr->cmd[i] );
			i++;
		}
		i = 0;
		curr = curr->next;
	}
}

void get_redir(t_cmd **cmd)
{
	t_cmd *head = *cmd;
	head->red = NULL;
	int i = 0;
	while(head)
	{
		i = 0;
		while(head->cmd[i])
		{
			if ((!strcmp((head)->cmd[i],"|") || !strcmp((head)->cmd[i],">")|| !strcmp((head)->cmd[i],">>")|| !strcmp((head)->cmd[i],"<")|| !strcmp((head)->cmd[i],"<<")) && head->count == 1)
			{
				printf("idkfih\n");
				head->flag = 1;
				return;
				// exit(1);
			}
			if ((!strcmp((head)->cmd[i],">") || !strcmp((head)->cmd[i],"<") ) && !(head)->cmd[i+1])
			{
				printf("tabnk\n");
				head->flag = 1;
				return;

				// exit(1);
			}
			if(!strcmp((head)->cmd[i],">") && strcmp(head->cmd[i],">>"))
				{	
					head->red = malloc(sizeof(t_red));
					head->red->file = ft_strdup(head->cmd[i + 1]);
					head->red->type = RREDIR;
					head->red->next  = NULL;
				}
			else if(!strcmp(head->cmd[i],"<") && strcmp(head->cmd[i],"<<"))
				{
					head->red = malloc(sizeof(t_red));
					head->red->file = ft_strdup(head->cmd[i + 1]);
					head->red->type = LREDIR;
					head->red->next  = NULL;
				}

			else if(!strcmp(head->cmd[i],"<<"))
				{
					head->red = malloc(sizeof(t_red));
					head->red->file = ft_strdup(head->cmd[i + 1]);
					head->red->type = HEREDOC;
					head->red->next  = NULL;
				}
			else if(!strcmp(head->cmd[i],">>"))
				{
					head->red = malloc(sizeof(t_red));
					head->red->file = ft_strdup(head->cmd[i + 1]);
					head->red->type = APPEND;
					head->red->next  = NULL;
				}
			i++;
		}
		head = head->next;
	}
	get_new_args(cmd);
	
}

int ma3rftch(t_cmd **cmd)
{
	t_cmd *head = *cmd;
	head->red = NULL;
	int i = 0;
	while(head)
	{
		i = 0;
		while(head->cmd[i])
		{
			if ((!strcmp((head)->cmd[i],"|") || !strcmp((head)->cmd[i],">")|| !strcmp((head)->cmd[i],">>")|| !strcmp((head)->cmd[i],"<")|| !strcmp((head)->cmd[i],"<<")) && head->count == 1)
			{
				printf("idkfih\n");
				return 1;
			}
			if ((!strcmp((head)->cmd[i],">") || !strcmp((head)->cmd[i],"<") ) && !(head)->cmd[i+1])
			{
				printf("tabnk\n");
								return 1;

			}
			i++;
		}
		head = head->next;
	}
	return 					0						;
}