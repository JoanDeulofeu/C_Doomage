/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:48:32 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/19 11:15:29 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*memory;
	size_t	i;

	i = 0;
	if (!(memory = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	while (i < size)
	{
		memory[i] = 0;
		i++;
	}
	return ((void *)(memory));
}
