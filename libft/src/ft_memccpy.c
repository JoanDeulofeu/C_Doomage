/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:53:57 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/09 11:15:27 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tabsrc;
	unsigned char	*tabdest;
	unsigned char	d;
	int				size;
	int				i;

	tabsrc = (unsigned char *)(src);
	tabdest = dst;
	d = c;
	size = n;
	i = 0;
	while (i < size)
	{
		tabdest[i] = tabsrc[i];
		if (tabsrc[i] == d)
			return (&(tabdest[i + 1]));
		i++;
	}
	return (NULL);
}
