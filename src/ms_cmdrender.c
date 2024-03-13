/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdrender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:28:27 by calmouht          #+#    #+#             */
/*   Updated: 2024/03/08 08:06:26 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_rendercmd(char **command, t_env *head)
{
	int		i;
	char	*var_name;
	t_env	*var_value;

	i = 0;
	while (command[i] != NULL)
	{
		var_name = expanded(command[i]);
		while (var_name != NULL)
		{
			var_value = ms_env_search(var_name, head);
			if (var_value == NULL)
				ft_strreplace(command[i], var_name, "");
			else
				ft_strreplace_all(command[i], var_name, var_value->value);
			var_name = expanded(command[i]);
		}
		i++;
	}
}
