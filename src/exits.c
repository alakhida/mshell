/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 05:46:15 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/12 07:07:51 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exits(int code)
{
	if (code == 1)
	{
		printf("minishell: syntax error\n");
		// exit(0);
	}
	if (code == 2)
	{
		printf("minishell: syntax error\n");
		// exit (0);
	}
}
