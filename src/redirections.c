/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:28:51 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/16 11:44:53 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	t_strlen(char **str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_strlen(str[i]);
		i++;
	}
	return (size);
}
char	**tarray_copy(char **a)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(char *) * t_strlen(a));
	i = 0;
	while (a[i])
	{
		cpy[i] = ft_strdup(a[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

int	is_special(char *tab)
{
	if (ms_ctrlop(tab) == RREDIR || ms_ctrlop(tab) == LREDIR ||
		ms_ctrlop(tab) == PIPE || ms_ctrlop(tab) == HEREDOC ||
		ms_ctrlop(tab) == APPEND)
	{
		return (1);
	}
	return (0);
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
			while (head->cmd && head->cmd[i])
			{
				if (head->cmd[i] && (is_special(head->cmd[i]) == 1))
				{
					tmp = head->cmd[i];
					head->cmd[i] = NULL;
					head->args = tarray_copy(head->cmd);
					head->cmd[i] = tmp;
					break ;
				}
				i++;
			}
		else
			head->args = tarray_copy(head->cmd);
		if (head->cmd)
			free_dbl_ptr(head->cmd);
		head->cmd = head->args;
		head = head->next;
	}
}


int	check_errors(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if ((is_special(tab[i]) == 1 && is_special(tab[i + 1]) == 1))
		{
			exits(2);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_node_back(t_red **red, t_red *new, char *file, t_type type)
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
		while (head->cmd[i] != NULL)
		{
			if (ms_ctrlop(head->cmd[i]) != NONE
				&& ms_ctrlop(head->cmd[i]) != PIPE)
			{
				if (head->cmd[i + 1] == NULL)
				{
					write(2, "minishell : syntax error near"
								" unexpected token `newline'\n",
							57);
					head->flag = 1;
					return ;
				}
				else if (ms_ctrlop(head->cmd[i + 1]) != NONE)
				{
					write(2, "minishell : syntax error near unexpected token `",
							48);
					write(2, head->cmd[i], ft_strlen(head->cmd[i]));
					write(2, "'\n", 2);
					head->flag = 1;
					return ;
				}
				else
				{
					if (!head->red)
					{
						head->red = malloc(sizeof(t_red));
						head->red->file = ft_strdup(head->cmd[i + 1]);
						head->red->type = ms_ctrlop(head->cmd[i]);
						head->red->next = NULL;
					}
					else
					{
						add_node_back(&(head->red), malloc(sizeof(t_red)), ft_strdup(head->cmd[i + 1]), ms_ctrlop(head->cmd[i]));
					}
				}
				i += 2;
			}
			else
			{
				i++;
			}
		}
		head = head->next;
	}
	get_new_args(cmd);
}
