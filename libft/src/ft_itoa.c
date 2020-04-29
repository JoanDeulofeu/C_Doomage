/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:17:40 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/17 15:44:25 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static void		putnb(int i, long l, char *str)
{
	int		j;

	j = l % 10;
	while (l > 9)
	{
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

char			*ft_itoa(int n)
{
	char			*str;
	long			l;
	int				i;
	long			origin;

	l = n;
	i = 1;
	if (n < 0)
	{
		i++;
		l *= -1;
	}
	origin = l;
	while (l > 9)
	{
		l /= 10;
		i++;
	}
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	if (n < 0)
		str[0] = '-';
	putnb(i - 1, origin, str);
	return (str);
}
