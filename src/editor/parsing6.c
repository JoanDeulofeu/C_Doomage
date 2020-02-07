/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:04:22 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 14:20:07 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_int	*get_t_int_from_vertex(t_main *s, int vtx_id)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	while (sct)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->ptr->id == vtx_id)
				return (wall);
			wall = wall->next;
		}
		sct = sct->next;
	}
	return (NULL);
}

void	add_portal_ptr(t_main *s, t_int *wall, int i, t_sector *sct)
{
	while (sct != NULL)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			wall->sct = sct->id;
			if (wall->wall_value != -1 && wall->vtx_dest == NULL)
			{
				wall->vtx_dest = get_t_int_from_vertex(s, wall->wall_value);
				if (wall->vtx_dest != NULL)
				{
					wall->vtx_dest->vtx_dest = wall;
					wall->vtx_dest->sct_dest = wall->sct;
					wall->sct_dest = wall->vtx_dest->sct;
					wall->vtx_dest->wall_value = wall->ptr->id;
				}
				else
					wall->wall_value = -1;
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}
