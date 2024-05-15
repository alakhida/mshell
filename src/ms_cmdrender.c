/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdrender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:28:27 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/15 06:23:53 by calmouht         ###   ########.fr       */
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

int	double_expansion(char *str, int *exit_stat)
{
	char *if_dbl_expand;
	int i;

	i = 0;
	if_dbl_expand = expanded(str, exit_stat);
	if (if_dbl_expand == NULL)
		return (0);
	while (if_dbl_expand[i])
	{
		if (if_dbl_expand[i] == '$')
		{
			free(if_dbl_expand);
			return (1);
		}
		i++;
	}
	free(if_dbl_expand);
	return (0);
}