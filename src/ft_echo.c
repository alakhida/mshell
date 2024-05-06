/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 07:15:42 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/06 08:10:55 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_option(char *str)
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

int		ft_echo(t_cmd *cmnd)
{
	int		i;
	int		n;

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
		while (cmnd->cmd[i])
		{
			ft_putstr_fd(cmnd->cmd[i], 1);
            if (cmnd->cmd[i + 1] != NULL)
                ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}
