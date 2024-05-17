/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:38:43 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/17 07:11:02 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_type	ms_ctrlop(char *str)
{
	if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(str, "<") == 0)
		return (LREDIR);
	else if (ft_strcmp(str, ">") == 0)
		return (RREDIR);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else
		return (NONE);
}

char	**ft_arrslice(char **arr, int start, int end)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = (char **)malloc(sizeof(char *) * (end - start + 1));
	while (start < end)
	{
		ptr[i] = ft_strdup(arr[start]);
		start++;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	*ft_strreplace(char *src, char *dst, char *replacement)
{
	char	*ptr;

	if (strstr(src, dst))
	{
		ptr = malloc(sizeof(char) * (ft_strlen(src) - ft_strlen(dst)
					+ ft_strlen(replacement) + 1));
		ft_strlcpy(ptr, src, strstr(src, dst) - src);
		ft_strlcat(ptr, replacement, ft_strlen(ptr) + ft_strlen(replacement)
			+ 1);
		ft_strlcat(ptr, strstr(src, dst) + ft_strlen(dst), ft_strlen(ptr)
			+ ft_strlen(strstr(src, dst) + ft_strlen(dst)) + 1);
	}
	else
		ptr = ft_strdup(src);
	if (src)
		free(src);
	return (ptr);
}

char	*ft_strreplace_all(char *src, char *dst, char *replacement)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_strreplace(src, dst, replacement);
	return (ptr);
}

int	count_var(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
