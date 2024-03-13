/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:29:08 by alakhida          #+#    #+#             */
/*   Updated: 2024/02/13 02:35:27 by lhorbax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	schar(const char *s, char c, size_t b)
{
	while (s[b] && s[b] == c)
		b++;
	return (b);
}

static size_t	echar(const char *s, char c, size_t l)
{
	while (s[l] && s[l] != c)
		l++;
	return (l);
}

static size_t	count(char const *s, char c)
{
	size_t		i;
	size_t		b;
	size_t		cnt;

	i = 0;
	cnt = 0;
	while (i < (size_t) ft_strlen((char *) s))
	{
		i = schar(s, c, i);
		b = echar(s, c, i);
		if (i < b)
			cnt++;
		i = b;
	}
	return (cnt);
}

static void	split(char **r, char const *s, char c)
{
	size_t	cnt;
	size_t	i;
	size_t	b;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		i = schar(s, c, i);
		b = echar(s, c, i);
		if (i < b)
			r[cnt++] = ft_substr((char *)s, i, (b - i));
		i = b;
	}
	r[cnt] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**rslt;

	if (!s)
		return (NULL);
	rslt = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!rslt)
		return (NULL);
	split(rslt, s, c);
	return (rslt);
}
