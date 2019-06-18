/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:18:35 by ydonse            #+#    #+#             */
/*   Updated: 2019/03/06 09:45:48 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin_free(char **s1, char **s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*s1 && *s2)
	{
		if (!(str = malloc(sizeof(char) * (ft_strlen(*s1)
		+ ft_strlen(*s2)) + 1)))
			return (NULL);
		while (s1[0][j])
			str[i++] = s1[0][j++];
		j = 0;
		while (s2[0][j])
			str[i++] = s2[0][j++];
		str[i] = '\0';
		ft_strdel(s1);
		ft_strdel(s2);
		return (str);
	}
	return (NULL);
}
