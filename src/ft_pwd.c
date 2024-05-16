/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 06:47:08 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/16 01:03:58 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_cmd *cmds)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (buff != NULL)
		printf("%s\n", buff);
	free(buff);
	return (0);
}
