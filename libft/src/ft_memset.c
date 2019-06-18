/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:36:10 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/20 14:17:47 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tab;
	int				i;
	unsigned char	d;
	int				size;

	i = 0;
	tab = b;
	d = c;
	size = len;
	while (i < size)
	{
		tab[i] = d;
		i++;
	}
	return (tab);
}
