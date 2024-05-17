/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 07:23:51 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/17 09:04:34 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_red_out(t_red *red)
{
	int	fd;

	if (access(red->file, F_OK) == -1)
		fd = open(red->file, O_WRONLY | O_CREAT, 0644);
	else
		fd = open(red->file, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: permission denied\n", 2);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_red_in(t_red *red)
{
	int	fd;

	if (access(red->file, F_OK) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (1);
	}
	fd = open(red->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: permission denied", 2);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_red_append(t_red *red)
{
	int	fd;

	if (access(red->file, F_OK) == -1)
		fd = open(red->file, O_WRONLY | O_CREAT, 0644);
	else
		fd = open(red->file, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: permission denied\n", 2);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_here_doc(t_red *red)
{
	char	*str;
	int		pip[2];

	pipe(pip);
	str = readline("> ");
	while (str)
	{
		if (!ft_strcmp(red->file, str))
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, pip[1]);
		free(str);
		str = readline("> ");
	}
	close(pip[1]);
	return (pip[0]);
}
