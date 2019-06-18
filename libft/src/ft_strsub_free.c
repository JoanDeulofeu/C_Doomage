/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:44:11 by ydonse            #+#    #+#             */
/*   Updated: 2018/12/03 14:48:22 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub_free(char **s, unsigned int start, size_t len)
{
	char	*str;
	size_t	st;
	size_t	i;

	st = start;
	i = 0;
	if (*s)
	{
		if (!(str = malloc(sizeof(char) * len + 1)))
			return (0);
		while (i < len)
		{
			str[i] = s[0][st];
			i++;
			st++;
		}
		str[i] = '\0';
		ft_strdel(s);
		return (str);
	}
	return (NULL);
}
