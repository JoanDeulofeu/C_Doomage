/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:05:38 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/14 11:27:18 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	st;
	size_t	i;

	st = start;
	i = 0;
	if (s)
	{
		if (!(str = malloc(sizeof(char) * len + 1)))
			return (0);
		while (i < len)
		{
			str[i] = s[st];
			i++;
			st++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
