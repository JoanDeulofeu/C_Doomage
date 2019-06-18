/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:51:17 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/19 17:50:22 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *liste;

	if (!(liste = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		liste->content = NULL;
		liste->content_size = 0;
	}
	else
	{
		if (!(liste->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(liste->content, (void *)(content),
		content_size);
		liste->content_size = content_size;
	}
	liste->next = NULL;
	return (liste);
}
