/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:17:57 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/20 18:29:52 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verif(const char *haystack, const char *needle, int i, int len)
{
	int j;
	int needle_size;
	int count;

	j = 0;
	count = 0;
	needle_size = ft_strlen(needle);
	while (needle[j] && i < len)
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

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*occ;

	i = 0;
	occ = NULL;
	if (ft_strlen(needle) == 0)
		return ((char *)(haystack));
	else if (haystack == needle)
		return ((char *)(haystack));
	if (len == 0)
		return (NULL);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			if (verif(haystack, needle, i, len) == 1)
				return ((char *)(&(haystack[i])));
			if (occ != NULL)
				return (occ);
		}
		i++;
	}
	return (NULL);
}
