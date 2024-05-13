/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdrender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:28:27 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/13 23:10:10 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	string_is_allnum(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_isdigit(string[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

void	ms_rendercmd(char **command, t_env *head, int *exit_status)
{
	int		i;
	int		j;
	char	*var_name;
	t_env	*var_value;

	i = 0;
	while (command[i] != NULL)
	{
		// var_name = expanded(command[i], exit_status);
		j = 0;
		while (command[i][j])
		{
			if (command[i][j] == '$' && command[i][j + 1] && command[i][j + 1] != '$')
			{
				var_name = expanded(&command[i][j], exit_status);
				var_value = ms_env_search(var_name, head);
				if (var_value == NULL && string_is_allnum(var_name))
				{
					command[i] = ft_strreplace(command[i], "$?", var_name);
				}
				else if (var_value == NULL)
				{
					command[i] = ft_strreplace(command[i] + 1 , var_name, "");
					break;
				}
				else
				{
					command[i] = ft_strreplace_all(command[i] + 1, var_name, var_value->value);
					break;
				}
			}
			j++;
		}
		i++;
	}
	// printf("%s\n****************************\n", command[j]);
}
