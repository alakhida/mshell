/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:10:55 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/17 09:04:50 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	heredoc_prevails(t_red *red)
{
	while (red)
	{
		if (red->type == HEREDOC || red->type == LREDIR)
			return (false);
		red = red->next;
	}
	return (true);
}

int	handle_redirections_part_two(t_cmd *cmds, t_red *red)
{
	if (red->type == RREDIR)
	{
		if (handle_red_out(red))
			return (1);
	}
	else if (red->type == LREDIR)
	{
		if (handle_red_in(red))
			return (1);
	}
	else if (red->type == APPEND)
	{
		if (handle_red_append(red))
			return (1);
	}
	else if (red->type == HEREDOC)
	{
		if (heredoc_prevails(red->next))
		{
			dup2(cmds->heredoc, STDIN_FILENO);
			close(cmds->heredoc);
		}
	}
	return (0);
}

int	handle_redirections(t_cmd *cmds)
{
	t_red	*red;

	red = cmds->red;
	while (red)
	{
		if (handle_redirections_part_two(cmds, red))
			return (1);
		red = red->next;
	}
	return (0);
}
