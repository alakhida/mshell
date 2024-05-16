/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:58:48 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/16 22:25:00 by alakhida         ###   ########.fr       */
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
		rl_redisplay();
	}
	if (status && WIFSIGNALED(status))
		signal_number = signal;
}

void	remove_q(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	char	qtype;

	tmp = ft_calloc(sizeof(char) * (ft_strlen(str) + 1), 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_Q || str[i] == DOUBLE_Q)
		{
			qtype = str[i++];
			while (str[i] && str[i] != qtype)
				tmp[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			tmp[j++] = str[i++];
	}
	ft_strcpy(str, tmp);
	free(tmp);
}
