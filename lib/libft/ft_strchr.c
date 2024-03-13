/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:21:54 by alakhida          #+#    #+#             */
/*   Updated: 2022/10/15 23:32:36 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	str;
	char	*alt;
	int		i;

	i = 0;
	alt = (char *)s;
	str = c;
	while (alt[i] != str)
	{
		if (alt[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)alt + i);
}
