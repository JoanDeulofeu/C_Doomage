/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:17:40 by ydonse            #+#    #+#             */
/*   Updated: 2019/03/04 09:45:15 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static void		putnb(long i, unsigned long long l, char *str)
{
	char	c;
	int		j;

	j = l % 10;
	while (l > 9)
	{
		c = '0' + j;
		str[i] = '0' + j;
		l /= 10;
		j = l % 10;
		i--;
	}
	if (i == 0)
		str[0] = '0' + j;
	else
		str[i] = '0' + j;
}

char			*ft_lutoa(unsigned long n)
{
	char				*str;
	int					i;
	unsigned long		origin;

	i = 0;
	origin = n;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	putnb(i - 1, origin, str);
	return (str);
}
