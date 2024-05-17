/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:50:53 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/16 23:57:25 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_token(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	check_errors(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if ((is_special(tab[i]) == 1 && is_special(tab[i + 1]) == 1))
		{
			write(2, "minishell : syntax error near unexpected token\n", 48);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_special(char *tab)
{
	if (ms_ctrlop(tab) == RREDIR || ms_ctrlop(tab) == LREDIR
		|| ms_ctrlop(tab) == PIPE || ms_ctrlop(tab) == HEREDOC
		|| ms_ctrlop(tab) == APPEND)
	{
		return (1);
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
