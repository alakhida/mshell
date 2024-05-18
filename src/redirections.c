/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:28:51 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/18 02:48:15 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	arg_norm(t_cmd *cmd, char *tmp)
{
	t_cmd	*head;
	int		i;

	head = cmd;
	i = 0;
	while (head->cmd && head->cmd[i])
	{
		if (head->cmd[i] && (is_special(head->cmd[i]) == 1))
		{
			tmp = head->cmd[i];
			head->cmd[i] = NULL;
			head->args = tarray_copy(head->cmd);
			head->cmd[i] = tmp;
			return ;
		}
		i++;
	}
}

void	get_new_args(t_cmd **cmd)
{
	t_cmd	*head;
	char	*tmp;
	int		i;

	head = *cmd;
	tmp = NULL;
	i = 0;
	while (head)
	{
		head->args = NULL;
		if (head->red)
			arg_norm(head, tmp);
		else
			head->args = tarray_copy(head->cmd);
		if (head->cmd)
			free_dbl_ptr(head->cmd);
		head->cmd = head->args;
		head = head->next;
	}
}

void	add_node_back(t_red **red, t_red *new, char *file, t_type type)
{
	t_red	*current;

	current = *red;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	current->next->file = file;
	current->next->type = type;
	current->next->next = NULL;
}

void	get_redir(t_cmd **cmd)
{
	t_cmd	*head;
	int		i;

	head = *cmd;
	i = 0;
	while (head)
	{
		i = 0;
		head->red = NULL;
		arg_norm2(head);
		head = head->next;
	}
	get_new_args(cmd);
}

void	arg_norm2(t_cmd *cmd)
{
	t_cmd	*head;
	int		i;

	head = cmd;
	i = 0;
	while (head->cmd[i] != NULL)
	{
		if (ms_ctrlop(head->cmd[i]) != NONE
			&& ms_ctrlop(head->cmd[i]) != PIPE)
		{
			if (arg_norm_error(head, i) == 1)
				return ;
			else if (arg_norm_error2(head, i) == 1)
				return ;
			else
				arg_norm_error3(head, i);
			i += 2;
		}
		else
			i++;
	}
}
