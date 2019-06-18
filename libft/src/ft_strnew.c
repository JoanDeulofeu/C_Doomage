/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:37:22 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/19 14:47:24 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size + 1)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
