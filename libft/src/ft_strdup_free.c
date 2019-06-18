/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:18:53 by ydonse            #+#    #+#             */
/*   Updated: 2018/12/21 15:07:01 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup_free(char **s1)
{
	int		len;
	char	*str;
	int		i;

	if (!*s1)
		return (NULL);
	len = ft_strlen(*s1);
	i = 0;
	str = malloc(sizeof(**s1) * len + 1);
	if (!str)
		return (NULL);
	while (s1[0][i])
	{
		str[i] = s1[0][i];
		i++;
	}
	str[i] = '\0';
	ft_strdel(s1);
	return (str);
}
