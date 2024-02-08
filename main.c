/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:49:14 by alakhida          #+#    #+#             */
/*   Updated: 2024/02/08 00:40:20 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)envp;
	char	*hold;
	(void)av;
	(void)ac; 
	hold = (char *)malloc(sizeof(char));
	char**	split_with_space;
	int		i;

	i = 0;
	while (1)
	{
		hold = readline("shell$:");
		split_with_space = ft_split(hold, ' ');
		while (split_with_space[i] != NULL)
		{
			printf("%s\n", split_with_space[i]);
			i++;
			if (split_with_space[i] == NULL)
				break;
		}
	}
	return (0);
}

