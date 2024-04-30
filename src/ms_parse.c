/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:12 by calmouht          #+#    #+#             */
/*   Updated: 2024/02/19 03:18:13 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ms_skip_sep(char *s)
{
	int		i;
	char	quotation_type;

	i = 0;
	quotation_type = s[i];
	while (s[i] == quotation_type && s[i] != '\0' && i < 2)
		i++;
	return (i);
}

static int	ms_lexlen(char *s)
{
	char	quotation_type;
	int		i;

	i = 0;
	if (ft_strchr("><|", s[i]) != NULL)
		i += ms_skip_sep(s);
	else
	{
		while (ft_strchr("><| \t\0", s[i]) == NULL)
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				quotation_type = s[i++];
				while (s[i] != quotation_type && s[i] != '\0')
					i++;
			}
			i++;
		}
	}
	return (i);
}

int	ms_count(char *s)
{
	int	iter;
	int	count;

	iter = 0;
	count = 0;
	// iterates over the whole string
	while (s[iter] != '\0')
	{
		// skips spaces
		while (s[iter] == ' ' || s[iter] == '\t')
			iter++;
		// well if the string is empty cut it out
		if (s[iter] != '\0')
			count++;
		// now we skip the parsable part
		iter += ms_lexlen(&s[iter]);
	}
	return (count);
}

char	**ms_parse(char *cmd)
{
	char	**lexed;
	int		i;
	int		lexed_i;

	i = 0;
	lexed_i = 0;
	if (cmd == NULL)
		return (NULL);
	lexed = (char **)malloc((ms_count(cmd) + 1) * sizeof(char *));
	ft_bzero(lexed, (ms_count(cmd) + 1) * sizeof(char *));
	while (cmd[i] != '\0')
	{
		while (cmd[i] != '\0' && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == '\0')
			break ;
		lexed[lexed_i] = malloc(ms_lexlen(&cmd[i]) + 1);
		ft_strlcpy(lexed[lexed_i++], &cmd[i], ms_lexlen(&cmd[i]) + 1);
		i += ms_lexlen(&cmd[i]);
	}
	return (lexed);
}
