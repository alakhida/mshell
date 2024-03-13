/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:15:48 by alakhida          #+#    #+#             */
/*   Updated: 2022/10/27 17:40:10 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f) (unsigned int, char*))
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*void myf(unsigned int i , char *mys)
{
	if(i > 2)
	{
		mys[i] = 'X';
	}

}

int main()
{
	char str[]="HASSAN";
	ft_striteri(str , myf);
	printf("%s\n",str);
}*/
