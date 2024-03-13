/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:12:15 by alakhida          #+#    #+#             */
/*   Updated: 2022/10/15 21:31:04 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t l)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)src;
	i = 0;
	if (l > 0)
	{
		while (ptr[i] && i < l - 1)
		{
			dst[i] = ptr[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}
