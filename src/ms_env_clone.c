/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:10 by calmouht          #+#    #+#             */
/*   Updated: 2024/03/08 08:06:59 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ms_env_dup(t_env *env)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = (char **)malloc(sizeof(char *) * (node_count(env) + 1));
	ft_bzero(ptr, sizeof(char *) * (node_count(env) + 1));
	while (env)
	{
		ptr[i] = malloc(ft_strlen(env->varname) + ft_strlen(env->value) + 2);
		ft_strlcpy(ptr[i], env->varname, ft_strlen(env->varname) + 1);
		ft_strlcat(ptr[i], "=", ft_strlen(env->varname) + 2);
		ft_strlcat(ptr[i], env->value, ft_strlen(env->varname)
				+ ft_strlen(env->value) + 2);
		env = env->next;
		i++;
	}
	return (ptr);
}
