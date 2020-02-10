/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:04:31 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 14:10:52 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		vtx_is_in_sct(t_main *s, int id)
{
	t_sector	*sct;
	t_int		*vtx;
	int			i;

	sct = s->sector;
	while (sct)
	{
		vtx = sct->vertex;
		i = 0;
		while (i++ < sct->vertex->prev->id)
		{
			if (vtx->ptr->id == id)
				return (1);
			vtx = vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

int		is_dest_valid(t_main *s, int id)
{
	t_vertex *vertex;

	vertex = s->vertex;
	while (vertex)
	{
		if (vertex->id == id)
			return (1);
		vertex = vertex->next;
	}
	return (0);
}

void	check_map_portals2(t_int *wall)
{
	wall->vtx_dest->vtx_dest = NULL;
	wall->vtx_dest->sct_dest = 0;
	wall->vtx_dest->wall_value = -1;
	wall->vtx_dest->selected = 0;
	wall->vtx_dest = NULL;
	wall->sct_dest = 0;
	wall->wall_value = -1;
	wall->selected = 0;
}

int		check_portal_boundary(t_int *wall)
{
	if (wall->next->wall_value != -1 || wall->prev->wall_value != -1)
		return (0);
	return (1);
}

void	check_map_portals(t_main *s)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	i = 0;
	while (sct != NULL)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->vtx_dest != NULL)
			{
				if (!check_walls_lenght(wall->vtx_dest, wall)
				|| !wall->vtx_dest->vtx_dest || !check_portal_boundary(wall)
				|| wall->vtx_dest->vtx_dest->ptr->id != wall->ptr->id
				|| !is_dest_valid(s, wall->vtx_dest->ptr->id)
				|| !vtx_is_in_sct(s, wall->vtx_dest->ptr->id))
					check_map_portals2(wall);
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}
