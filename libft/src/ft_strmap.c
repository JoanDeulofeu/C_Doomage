/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:00:56 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/21 11:00:18 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;
	int		count;

	count = 0;
	if (!s)
		return (NULL);
	while (s[count])
	{
		count++;
	}
	if (!(str = malloc(sizeof(char) * count + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
