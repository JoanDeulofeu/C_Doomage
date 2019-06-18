/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:30:32 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/19 14:28:11 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tab;
	unsigned char	lt;
	size_t			i;

	tab = (unsigned char *)(s);
	lt = c;
	i = 0;
	while (i < n)
	{
		if ((tab[i]) == lt)
			return (&(tab[i]));
		i++;
	}
	return (NULL);
}
