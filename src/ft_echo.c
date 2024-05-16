/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:15:42 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/16 01:33:29 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option(char *str)
{
	int		i;
	bool	t;

	t = false;
	i = 1;
	if (str[0] == '-')
	{
		if (str[i] == 'n')
			t = true;
		while (str[i] == 'n')
			i++;
	}
	if (str[i] == '\0' && t == true)
		return (1);
	return (0);
}

int	print_string_fd(char *s, int fd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i] > '\0')
	{
		ret = write(fd, &s[i], 1);
		if (ret == -1)
			return (-1);
		i++;
	}
	return (ret);
}

int	ft_echo_norm(t_cmd *cmnd, int i)
{
	while (cmnd->cmd[i])
	{
		if (print_string_fd(cmnd->cmd[i], 1) == -1)
			return (EXIT_FAILURE);
		if (cmnd->cmd[i + 1] != NULL)
			if (print_string_fd(" ", 1) == -1)
				return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(t_cmd *cmnd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (cmnd->cmd[1] != NULL)
	{
		if (check_option(cmnd->cmd[1]) == 1)
		{
			i += 2;
			n = 1;
		}
		else
			i += 1;
		ft_echo_norm(cmnd, i);
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}
