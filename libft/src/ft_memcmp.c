/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:57:05 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/09 11:14:48 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*str2;
	int				len;
	int				i;

	str = (unsigned char *)(s1);
	str2 = (unsigned char *)(s2);
	len = n;
	i = 0;
	while (i < len)
	{
		if (str[i] - str2[i] != 0)
			return (str[i] - str2[i]);
		i++;
	}
	return (0);
}
