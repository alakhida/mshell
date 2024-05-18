/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdrender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:28:27 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/18 03:32:34 by alakhida         ###   ########.fr       */
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

void	ms_rendercmd_norm(t_env *var_value, t_env *head, t_norm *index,
	char **command)
{
	var_value = ms_env_search(index->var_name, head);
	if (var_value != NULL || string_is_allnum(index->var_name))
	{
		if (var_value != NULL)
			index->replacement = ft_strtrim(var_value->value, "\"$\'");
		else
			index->replacement = ft_strdup(index->var_name);
		command[index->i] = ft_strreplace_all(command[index->i],
				index->var_name, index->replacement);
		index->string = ft_strtrim(command[index->i], "\"$\'");
		index->j += ft_strlen(index->replacement) - 1;
		free(command[index->i]);
		command[index->i] = index->string;
		free(index->replacement);
	}
	else
		command[index->i] = ft_strreplace(command[index->i],
				index->var_name, "");
}

void	ms_rendercmd_norm2(t_env *var_value, t_env *head, t_norm *index,
	char **command)
{
	while (command[index->i][index->j] != '\0')
	{
		if (command[index->i][0] != '\'')
		{
			if (command[index->i][index->j] == '$' && 
				(ft_isalnum(command[index->i][index->j + 1])
					|| command[index->i][index->j + 1] == '?'))
			{
				index->var_name = expanded(&command[index->i][index->j],
						index->ex_stts);
				if (index->var_name != NULL)
					ms_rendercmd_norm(var_value, head, index, command);
				else
					break ;
				free(index->var_name);
			}
		}
		index->j++;
	}
}

void	ms_rendercmd(char **command, t_env *head, int *exit_status,
			t_norm *index)
{
	t_env	*var_value;

	index->i = 0;
	index->ex_stts = exit_status;
	while (command[index->i] != NULL)
	{
		index->j = 0;
		index->replacement = NULL;
		index->string = NULL;
		ms_rendercmd_norm2(var_value, head, index, command);
		index->i++;
	}
}
