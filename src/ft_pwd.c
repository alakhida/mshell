/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 06:47:08 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/15 09:22:25 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_cmd *cmds)
{
	char	*buff;

	if (cmds->cmd[1])
	{
		printf("%s: too many arguments\n", cmds->cmd[0]);
		return (0);
	}
	buff = getcwd(NULL, 0);
	if (buff != NULL)
		printf("%s\n", buff);
	free(buff);
	return (0);
}
