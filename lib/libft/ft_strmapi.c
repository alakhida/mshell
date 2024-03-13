/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:09:58 by alakhida          #+#    #+#             */
/*   Updated: 2024/02/13 02:32:30 by lhorbax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	size_t				i;
	size_t				len;
	char				*result;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen((char *)s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// char f(unsigned int  x, char f)
// {
// 	return('r');
// }
// int main()
// {
// 	char *r  = ft_strmapi("ayoub", f);
// 	printf("%s\n", r);
// }
