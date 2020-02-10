/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:24:40 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 21:07:45 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_pos	ft_get_ori_move_anchor(t_main *s)
{
	t_pos		ori;

	ori.x = arround(s->editor->space, s->ft_mouse.x
		- (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, s->ft_mouse.y
		- (s->editor->decal_y % s->editor->space));
	return (ori);
}

void	ft_sector_eat_another(t_main *s, t_sector *sct, int sct_id)
{
	t_int	*wall;
	int		i;

	if (sct_id == 0)
		return ;
	while (sct)
	{
		if (sct->id == sct_id)
		{
			sct = sct->next;
			continue;
		}
		wall = sct->vertex;
		i = 0;
		while (i++ < sct->vertex->prev->id)
		{
			if (ft_is_in_sector(s, wall->ptr->m_pos) == sct_id)
			{
				remove_sector(s, wall->value, 0, s->sector);
				ft_putstr("Sector delete: sector is in another\n");
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}

void	move_anchor(t_main *s, int id, int ftiis, t_vertex *temp)
{
	t_pos		ori;
	t_pos		abs;
	t_dpos		mouse;

	ori = ft_get_ori_move_anchor(s);
	abs = get_abs_pos(s, ori);
	mouse.x = abs.x * METRE;
	mouse.y = abs.y * METRE;
	ftiis = fiis(s, mouse, vtx_is_in_sct(s, id), s->sector);
	while (temp)
	{
		if (temp->id == id && ft_check_vertex(s, abs.x, abs.y)
		&& (ftiis == 0 || ftiis == vtx_is_in_sct(s, id)))
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
	t_vertex	*vtx;
	int			sct_id;

	vtx = get_vertex_by_id(s, wall->ptr->id);
	sct_id = ft_is_in_sector(s, vtx->m_pos);
	if (ft_check_wall_that_intersect(s, sct)
	|| (sct_id != 0 && sct_id != sct->id)
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
		if (vtx->old.x != vtx->x || vtx->old.y != vtx->y)
			printf("save des old\n");
		vtx->old.x = vtx->x;
		vtx->old.y = vtx->y;
	}
}

void	ft_save_old_pos_vtx(t_vertex *vtx)
{
	while (vtx)
	{
		vtx->old.x = vtx->x;
		vtx->old.y = vtx->y;
		vtx = vtx->next;
	}
}

void	ft_check_move_vertex_validity(t_main *s)
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
	ft_sector_eat_another(s, s->sector, vtx_is_in_sct(s, s->editor->id));
	ft_save_old_pos_vtx(s->vertex);
}
