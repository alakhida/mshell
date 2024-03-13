/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:07:52 by alakhida          #+#    #+#             */
/*   Updated: 2022/10/25 11:44:18 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char		*tm;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (start > j)
	{
		start = j;
		len = 0;
	}
	else if (j < start + len)
		len = j - start;
	tm = ft_calloc(len + 1, sizeof(char));
	if (!tm)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		tm[i] = s[start + i];
		i++;
	}
	tm[i] = '\0';
	return (tm);
}
