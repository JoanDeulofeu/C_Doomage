/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:29:38 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 12:29:42 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			test_new_pos(t_main *s, t_visu *vs, t_dpos player)
{
	double	l_angle;
	double	r_angle;
	t_visu	save;

	save = *vs;
	l_angle = vs->angle + s->player.demi_fov;
	l_angle = l_angle > 360 ? l_angle - 360 : l_angle;
	r_angle = vs->angle - s->player.demi_fov;
	r_angle = r_angle < 0 ? r_angle + 360 : r_angle;
	vs->left_point.x = player.x + cos(to_rad(l_angle)) * 10000;
	vs->left_point.y = player.y - sin(to_rad(l_angle)) * 10000;
	vs->begin_wall_id = ft_find_wall(s, player, vs->left_point, vs->sct_id);
	vs->right_point.x = player.x + cos(to_rad(r_angle)) * 10000;
	vs->right_point.y = player.y - sin(to_rad(r_angle)) * 10000;
	vs->end_wall_id = ft_find_wall(s, player, vs->right_point, vs->sct_id);
	if (vs->end_wall_id == 0 && vs->begin_wall_id != 0)
		vs->end_wall_id = get_t_int_by_vertex_id(get_sector_by_id(s,
			vs->sct_id)->vertex, vs->begin_wall_id)->next->ptr->id;
	if (s->portal_nb == 0 && (vs->end_wall_id == 0 || vs->begin_wall_id == 0))
	{
		*vs = save;
		return (0);
	}
	else
		return (1);
}

int			move_player_near_portal2(t_main *s, t_visu *vs, int nb)
{
	t_dpos	curr;

	curr.y = s->player.m_pos.y - nb;
	curr.x = s->player.m_pos.x - nb;
	if (test_new_pos(s, vs, curr))
		return (1);
	curr.x = s->player.m_pos.x + nb;
	if (test_new_pos(s, vs, curr))
		return (1);
	curr.y += nb * 2;
	if (test_new_pos(s, vs, curr))
		return (1);
	curr.x -= nb * 2;
	if (test_new_pos(s, vs, curr))
		return (1);
	return (0);
}

t_visu		move_player_near_portal(t_main *s, t_visu vs, int nb)
{
	t_dpos	curr;

	while (++nb < 100)
	{
		curr = s->player.m_pos;
		curr.x = s->player.m_pos.x + nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.x = s->player.m_pos.x - nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.x = s->player.m_pos.x;
		curr.y = s->player.m_pos.y + nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.y = s->player.m_pos.y - nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		if (move_player_near_portal2(s, &vs, nb))
			return (vs);
	}
	return (vs);
}

void		ft_find_wall2(t_main *s, t_ft_find_wall *f, int sct_id)
{
	f->dist = 100000;
	f->new_dist = 0;
	f->sct = s->sector;
	if (sct_id == 0)
		handle_error(s, SECTOR_ERROR);
	while (sct_id != f->sct->id)
		f->sct = f->sct->next;
	f->s_vtx = f->sct->vertex;
	f->id_wall = 0;
	f->i = 0;
	s->count_wall = 0;
}

int			ft_find_wall(t_main *s, t_dpos player, t_dpos point, int sct_id)
{
	t_ft_find_wall f;

	ft_find_wall2(s, &f, sct_id);
	while (f.i++ < f.sct->vertex->prev->id)
	{
		f.pos.pos1 = f.s_vtx->ptr->m_pos;
		f.pos.pos2 = f.s_vtx->next->ptr->m_pos;
		f.pos.pos3 = point;
		f.pos.pos4 = player;
		if ((f.new_dist = ft_find_intersection(s, f.pos, 1)) > 0)
		{
			s->count_wall++;
			if (f.new_dist < f.dist && f.new_dist != 0 && f.new_dist != -1)
			{
				f.id_wall = f.s_vtx->ptr->id;
				f.dist = f.new_dist;
			}
		}
		f.s_vtx = f.s_vtx->next;
	}
	return (f.id_wall);
}
