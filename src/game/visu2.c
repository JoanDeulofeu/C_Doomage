/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:30:37 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 20:12:34 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_visu		ft_place_view_plan(t_dpos player, double angle)
{
	t_dpos	ctr_p;
	t_visu	vs;

	ft_bzero(&vs, sizeof(t_visu));
	ctr_p.x = player.x + cos(to_rad(angle)) * METRE;
	ctr_p.y = player.y - sin(to_rad(angle)) * METRE;
	vs.left_plan.x = ctr_p.x + cos(to_rad(angle + 90))
	* (WIDTH / DIVPLAN) * 0.5;
	vs.left_plan.y = ctr_p.y - sin(to_rad(angle + 90))
	* (WIDTH / DIVPLAN) * 0.5;
	vs.right_plan.x = ctr_p.x + cos(to_rad(angle - 90))
	* (WIDTH / DIVPLAN) * 0.5;
	vs.right_plan.y = ctr_p.y - sin(to_rad(angle - 90))
	* (WIDTH / DIVPLAN) * 0.5;
	return (vs);
}

t_visu		get_walls_to_draw(t_main *s, t_dpos player, t_visu vs)
{
	double	l_angle;
	double	r_angle;

	l_angle = vs.angle + s->player.demi_fov;
	l_angle = l_angle > 360 ? l_angle - 360 : l_angle;
	r_angle = vs.angle - s->player.demi_fov;
	r_angle = r_angle < 0 ? r_angle + 360 : r_angle;
	vs.left_point.x = player.x + cos(to_rad(l_angle)) * 10000;
	vs.left_point.y = player.y - sin(to_rad(l_angle)) * 10000;
	vs.begin_wall_id = ft_find_wall(s, player, vs.left_point, vs.sct_id);
	vs.begin = s->tmp_intersect;
	vs.right_point.x = player.x + cos(to_rad(r_angle)) * 10000;
	vs.right_point.y = player.y - sin(to_rad(r_angle)) * 10000;
	vs.end_wall_id = ft_find_wall(s, player, vs.right_point, vs.sct_id);
	if (vs.end_wall_id == 0 && vs.begin_wall_id != 0)
		vs.end_wall_id = get_t_int_by_vertex_id(get_sector_by_id(s,
			vs.sct_id)->vertex, vs.begin_wall_id)->next->ptr->id;
	vs.end = s->tmp_intersect;
	vs.vtx_gauche = get_t_int_by_vertex_id(vs.sct->vertex, vs.begin_wall_id);
	vs.vtx_droite = get_t_int_by_vertex_id(vs.sct->vertex, vs.end_wall_id);
	vs.player = player;
	if (s->player.m_pos.x == player.x && s->player.m_pos.y == player.y
		&& (vs.end_wall_id == 0 || vs.begin_wall_id == 0))
		vs = move_player_near_portal(s, vs, 0);
	return (vs);
}

void		ft_foot_height(t_main *s, t_visu vs)
{
	if (s->player.foot_height == -1)
		s->player.foot_height = vs.sct->floor + s->player.jump_height;
	else
		s->player.foot_height += s->player.jump_height
		- s->player.prev_jump_height;
	if (s->player.foot_height < s->player.floor_height)
		s->player.foot_height = s->player.floor_height;
	s->player.prev_jump_height = s->player.jump_height;
	s->player.ceiling_height = vs.sct->ceiling;
	s->player.floor_height = vs.sct->floor;
}

void		ft_visu_joan(t_main *s)
{
	t_visu	vs;
	t_dpos	player;

	player = s->player.m_pos;
	vs.vtx_droite = NULL;
	vs.vtx_gauche = NULL;
	vs = ft_place_view_plan(player, s->player.angle);
	vs.sct_id = s->player.sector_id;
	vs.sct = get_sector_by_id(s, s->player.sector_id);
	ft_foot_height(s, vs);
	vs.right_ceiling_limit.x = WIDTH;
	vs.left_floor_limit.y = HEIGHT;
	vs.right_floor_limit.x = WIDTH;
	vs.right_floor_limit.y = HEIGHT;
	vs.angle = angle_mod(s->player.angle);
	vs = get_walls_to_draw(s, player, vs);
	ft_draw_visu(s, get_sector_by_id(s, s->player.sector_id), vs);
}
