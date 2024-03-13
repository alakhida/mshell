#include "libft.h"

char	*ft_strldup(char *s1, int len)
{
	char	*dst;
	int		i;

	dst = ((char *)malloc(sizeof(char) *(len + 1)));
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
