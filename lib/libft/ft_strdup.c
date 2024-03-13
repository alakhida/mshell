/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:04:28 by alakhida          #+#    #+#             */
/*   Updated: 2022/10/22 23:24:14 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		slen;
	int		i;

	slen = 0;
	while (s1[slen])
		slen++;
	dst = ((char *)malloc(sizeof(char) *(slen + 1)));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < slen)
	{
	dst[i] = s1[i];
	i++;
	}
	dst[i] = '\0';
	return (dst);
}
