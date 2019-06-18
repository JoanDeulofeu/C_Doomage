/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:53:54 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/19 11:25:37 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (s)
	{
		while (*s == ' ' || *s == '\n' || *s == '\t')
			s++;
		i = ft_strlen(s) - 1;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i--;
		i++;
		i = (i < 0) ? 0 : i;
		if (!(str = malloc(sizeof(char) * i + 1)))
			return (NULL);
		while (j < i)
		{
			str[j] = s[j];
			j++;
		}
		str[j] = '\0';
		return (str);
	}
	return (NULL);
}
