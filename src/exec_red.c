/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 07:23:51 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/13 19:29:24 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_red_out(t_cmd *cmds)
{
	int		fd;

	if (access(cmds->red->file, X_OK) == -1)
		fd = open(cmds->red->file, O_WRONLY | O_CREAT, 0644);
	else
		fd = open(cmds->red->file, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: permission denied\n", 2);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_red_in(t_cmd *cmds)
{
	int	fd;

	if (access(cmds->red->file, F_OK) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		exit(1);
	}
	fd = open(cmds->red->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: permission denied", 2);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_red_append(t_cmd *cmds)
{
	int		fd;

	if (access(cmds->red->file, F_OK) == -1)
		fd = open(cmds->red->file, O_WRONLY | O_CREAT, 0644);
	else
		fd = open(cmds->red->file, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: permission denied\n", 2);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_here_doc(t_cmd *cmds)
{
	char	*str;
	int		pip[2];

	pipe(pip);
	str = readline("> ");
	while (str)
	{
		if (!ft_strcmp(cmds->red->file, str))
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, pip[1]);
		free(str);
		str = readline("> "); 
	}
	close(pip[1]);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
}

void	handle_redirections(t_cmd *cmds)
{
	if (cmds->red->type == RREDIR)
		handle_red_out(cmds);
	else if (cmds->red->type == LREDIR)
		handle_red_in(cmds);
	else if (cmds->red->type == APPEND)
		handle_red_append(cmds);
	else if (cmds->red->type == HEREDOC)
		handle_here_doc(cmds);
}
