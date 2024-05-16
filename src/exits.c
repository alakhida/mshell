/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 05:46:15 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/16 00:58:49 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exits(int code)
{
	if (code == 1)
		ft_putstr_fd("minishell: syntax error\n", 2);
	if (code == 2)
		ft_putstr_fd("minishell: syntax error\n", 2);
}
