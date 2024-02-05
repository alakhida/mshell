/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:49:14 by alakhida          #+#    #+#             */
/*   Updated: 2024/02/05 20:58:46 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*hold;
	hold = (char *)malloc(sizeof(char));
	while (1)
	{
		hold = readline("shell$:");
	}
	return (0);
}

