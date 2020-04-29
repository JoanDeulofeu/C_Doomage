/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:01:37 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/21 09:54:23 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verif(const char *haystack, const char *needle, int i)
{
	int j;
	int needle_size;

	j = 0;
	needle_size = ft_strlen(needle);
	while (needle[j])
	{
		if (needle[j] == haystack[i])
		{
			if (j == needle_size - 1)
				return (1);
			j++;
			i++;
		}
		else
			return (0);
	}
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	char	*occ;

	i = 0;
	occ = NULL;
	if (ft_strlen(needle) == 0 || haystack == needle)
		return ((char *)(haystack));
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (verif(haystack, needle, i) == 1)
				return ((char *)(&(haystack[i])));
			if (occ != NULL)
				return (occ);
		}
		i++;
	}
	return (NULL);
}
