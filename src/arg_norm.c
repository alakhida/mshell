/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 01:40:55 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/17 08:51:25 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	arg_norm_error(t_cmd *cmd, int i)
{
	t_cmd	*head;

	head = cmd;
	if (head->cmd[i + 1] == NULL)
	{
		write(2, SYNT_ERR, 57);
		head->flag = 1;
		return (true);
	}
	return (false);
}

bool	varname_ok(char *string)
{
	int	i;

	i = 0;
	while ((string && !ft_isdigit(string[0]) && 
			ft_isalnum(string[i])) || string[i] == '=')
	{
		if (!string[i + 1])
			return (true);
		i++;
	}
	printf("export: bad argument\n");
	return (false);
}

bool	arg_norm_error2(t_cmd *cmd, int i)
{
	t_cmd	*head;

	head = cmd;
	if (ms_ctrlop(head->cmd[i + 1]) != NONE)
	{
		write(2, "minishell : syntax error near unexpected token `",
			48);
		write(2, head->cmd[i], ft_strlen(head->cmd[i]));
		write(2, "'\n", 2);
		head->flag = 1;
		return (true);
	}
	return (false);
}

void	arg_norm_error3(t_cmd *cmd, int i)
{
	t_cmd	*head;

	head = cmd;
	if (!head->red)
	{
		head->red = malloc(sizeof(t_red));
		head->red->file = ft_strdup(head->cmd[i + 1]);
		head->red->type = ms_ctrlop(head->cmd[i]);
		head->red->next = NULL;
	}
	else
	{
		add_node_back(&(head->red), malloc(sizeof(t_red)),
			ft_strdup(head->cmd[i + 1]),
			ms_ctrlop(head->cmd[i]));
	}
	return ;
}
