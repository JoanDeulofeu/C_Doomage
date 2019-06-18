/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:56:35 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/19 16:42:46 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tabsrc;
	unsigned char	*tabdest;
	int				i;
	int				size;

	tabdest = dest;
	tabsrc = (unsigned char *)(src);
	size = n;
	i = 0;
	while (i < size)
	{
		tabdest[i] = tabsrc[i];
		i++;
	}
	return (dest);
}
