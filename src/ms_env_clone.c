/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:10 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/16 22:26:02 by alakhida         ###   ########.fr       */
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
