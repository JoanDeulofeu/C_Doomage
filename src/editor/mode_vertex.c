/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:24:40 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/09 21:15:14 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	move_anchor(t_main *s, int id)
{
	t_vertex	*temp;
	t_pos		ori;
	t_pos		abs;

	temp = (s->vertex) ? s->vertex : NULL;
	ori.x = arround(s->editor->space, s->ft_mouse.x
		- (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, s->ft_mouse.y
		- (s->editor->decal_y % s->editor->space));
	abs = get_abs_pos(s, ori);
	while (temp)
	{
		if (temp->id == id && ft_check_vertex(s, abs.x, abs.y))
		{
			temp->pos = ori;
			temp->x = abs.x;
			temp->y = abs.y;
			temp->m_pos.x = temp->x * METRE;
			temp->m_pos.y = temp->y * METRE;
			check_map_portals(s);
			return ;
		}
		temp = temp->next;
	}
}

void	draw_anchor(t_main *s, t_pos ori, Uint32 color)
{
	t_dpos		init;
	t_dpos		dest;
	short		size;

	size = s->editor->anchor_size;
	init.x = ori.x - size;
	init.y = ori.y - size;
	dest.x = ori.x + size;
	dest.y = ori.y + size;
	draw_rect(s->sdl->editor, init, dest, color);
}

int		ft_check_wall_lenght(t_sector *sct, int i)
{
	t_int		*wall;
	int			stop;
	t_pos		vtx1;
	t_pos		vtx2;
	int			dist;

	wall = sct->vertex;
	stop = wall->prev->id;
	while (i++ < stop)
	{
		vtx1.x = wall->ptr->x * METRE;
		vtx1.y = wall->ptr->y * METRE;
		vtx2.x = wall->next->ptr->x * METRE;
		vtx2.y = wall->next->ptr->y * METRE;
		if ((dist = ft_dist_t_pos(vtx1, vtx2)) > 2000)
			return (1);
		wall = wall->next;
	}
	return (0);
}

void	ft_check_move_vertex_validity2(t_main *s, t_sector *sct, t_int *wall)
{
	t_pos		abs;
	t_vertex	*vtx;

	vtx = get_vertex_by_id(s, wall->ptr->id);
	if (ft_check_wall_that_intersect(s, sct)
	|| ft_check_wall_lenght(sct, 0) || ft_check_sector_sens(sct, 0))
	{
		vtx->x = vtx->old.x;
		vtx->y = vtx->old.y;
		wall->ptr->pos.x = vtx->x * s->editor->space;
		wall->ptr->pos.y = vtx->y * s->editor->space;
		wall->ptr->m_pos.x = wall->ptr->x * METRE;
		wall->ptr->m_pos.y = wall->ptr->y * METRE;
	}
	else
	{
		vtx->old.x = vtx->x;
		vtx->old.y = vtx->y;
	}
}

void	ft_check_move_vertex_validity(t_main *s, int id)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	while (sct)
	{
		wall = sct->vertex;
		i = 0;
		while (i++ < sct->vertex->prev->id)
		{
			ft_check_move_vertex_validity2(s, sct, wall);
			wall = wall->next;
		}
		sct = sct->next;
	}
}
