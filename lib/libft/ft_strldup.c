/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 06:32:13 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/15 06:32:14 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(char *s1, int len)
{
	char	*dst;
	int		i;

	dst = ((char *)malloc(sizeof(char) * (len + 1)));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
