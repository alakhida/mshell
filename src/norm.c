/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:10:55 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/17 08:00:51 by alakhida         ###   ########.fr       */
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

int	handle_redirections_part_two(t_cmd *cmds)
{
	if (cmds->red->type == RREDIR)
	{
		if (handle_red_out(cmds))
			return (1);
	}
	else if (cmds->red->type == LREDIR)
	{
		if (handle_red_in(cmds))
			return (1);
	}
	else if (cmds->red->type == APPEND)
	{
		if (handle_red_append(cmds))
			return (1);
	}
	else if (cmds->red->type == HEREDOC)
	{
		if (heredoc_prevails(cmds->red->next))
		{
			dup2(cmds->heredoc, STDIN_FILENO);
			close(cmds->heredoc);
		}
	}
	return (0);
}

int	handle_redirections(t_cmd *cmds)
{
	while (cmds->red)
	{
		if (handle_redirections_part_two(cmds))
			return (1);
		cmds->red = cmds->red->next;
	}
	return (0);
}
