/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdrender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:28:27 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/16 00:01:27 by alakhida         ###   ########.fr       */
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
	char	*replacement;
	char	*var_name;
	t_env	*var_value;

	i = 0;
	while (command[i] != NULL)
	{
		j = 0;
		while (command[i][j] != '\0')
		{
			if (command[i][j] == '$' && (ft_isalnum(command[i][j + 1])
					|| command[i][j + 1] == '?'))
			{
				var_name = expanded(&command[i][j], exit_status);
				if (var_name != NULL)
				{
					var_value = ms_env_search(var_name, head);
					if (var_value != NULL || string_is_allnum(var_name))
					{
						if (var_value != NULL)
							replacement = ft_strtrim(var_value->value, "\"$\'");
						else
							replacement = var_name;
						command[i] = ft_strreplace_all(command[i], var_name,
								replacement);
						command[i] = ft_strtrim(command[i], "\"$\'");
						j += ft_strlen(replacement);
					}
					else
						command[i] = ft_strreplace(command[i] + 1, var_name,
								"");
					free(var_name);
				}
				else
					break ;
			}
			j++;
		}
		i++;
	}
}