/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:30:57 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/30 15:00:22 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1)))
			return (NULL);
		while (s1[j])
		{
			str[i++] = s1[j++];
		}
		j = 0;
		while (s2[j])
		{
			str[i++] = s2[j++];
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
