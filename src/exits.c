/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 05:46:15 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/15 06:15:45 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exits(int code)
{
	if (code == 1)
	{
		printf("minishell: syntax error\n");
	}
	if (code == 2)
	{
		printf("minishell: syntax error\n");
	}
}
