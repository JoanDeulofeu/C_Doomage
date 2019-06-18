/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:48:48 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/19 11:22:07 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	add;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	add = ft_strlen(dst) + ft_strlen(src);
	if (size <= i)
		return (size + (size_t)(ft_strlen(src)));
	while (src[j] && i < (size - 1))
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (add);
}
