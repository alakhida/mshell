/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:58:48 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/16 01:42:36 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*s = NULL;
	char		*ret;
	int			i;

	if (str)
		s = str;
	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (ft_strchr(delim, s[i]))
		{
			s[i] = '\0';
			ret = s;
			s = s + i + 1;
			return (ret);
		}
		i++;
	}
	ret = s;
	s = NULL;
	return (ret);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	sig(int signal)
{
	int	status;

	status = 0;
	wait(&status);
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (status && WIFSIGNALED(status))
		signal_number = signal;
	else
		rl_redisplay();
}
