/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:01:33 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/17 05:10:20 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	t_strlen(char **str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_strlen(str[i]);
		i++;
	}
	return (size);
}

char	**tarray_copy(char **a)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(char *) * t_strlen(a));
	i = 0;
	while (a[i])
	{
		cpy[i] = ft_strdup(a[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	update_exit(t_env **env, int exit)
{
	t_env	*l9ito;

	l9ito = ms_env_search("?", *env);
	if (l9ito->value)
	{
		free(l9ito->value);
		l9ito->value = ft_itoa(exit);
	}
}
