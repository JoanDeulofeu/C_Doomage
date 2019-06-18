/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:09:47 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/21 11:19:57 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tempdst;
	unsigned char	*tempsrc;
	size_t			n;

	tempdst = (unsigned char *)(dst);
	tempsrc = (unsigned char *)(src);
	n = 0;
	while (n < len)
	{
		if ((tempsrc) < (tempdst))
		{
			tempdst[len - 1] = tempsrc[len - 1];
			len--;
		}
		else
		{
			tempdst[n] = tempsrc[n];
			n++;
		}
	}
	return (dst);
}
