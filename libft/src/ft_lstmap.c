/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:46:53 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/20 18:01:43 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *origin;

	new = f(lst);
	origin = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = f(lst);
		new = new->next;
	}
	return (origin);
}
