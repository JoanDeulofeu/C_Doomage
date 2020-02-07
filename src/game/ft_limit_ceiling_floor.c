/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limit_ceiling_floor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:58:53 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 20:12:17 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_limit_ceiling_floor2(t_main *s, t_ft_limit_ceiling_floor l)
{
	l.pos.pos1 = l.vs->left_point;
	if (ft_find_intersection(s, l.pos, 1) > 0)
		l.x = 0;
	else
		l.x = (ft_dist_t_dpos(l.vs->left_plan, l.l_plan) / (WIDTH / DIVPLAN))
		* WIDTH;
	s->player.eyesight = s->player.foot_height
	- l.vs->sct->floor + s->player.size;
	l.l_height_wall_diff = ft_get_diff_height_pxl(s->player.eyesight,
	l.vs->sct->ceiling, l.vs->sct->floor, l.l_height_wall);
	l.r_height_wall_diff = ft_get_diff_height_pxl(s->player.eyesight,
	l.vs->sct->ceiling, l.vs->sct->floor, l.r_height_wall);
	l.vs->left_ceiling_limit.x = (int)l.x;
	l.vs->left_ceiling_limit.y = (HEIGHT * 0.5) - (l.l_height_wall)
	+ s->player.y_eye + l.l_height_wall_diff;
	l.vs->left_floor_limit.x = (int)l.x;
	l.vs->left_floor_limit.y = (HEIGHT * 0.5) + s->player.y_eye
	+ l.l_height_wall_diff;
	l.vs->right_ceiling_limit.x = l.x + ((WIDTH * ((ft_dist_t_dpos(l.l_plan,
	l.r_plan) * 100.0) / (WIDTH / DIVPLAN))) * 0.01);
	l.vs->right_ceiling_limit.y = (HEIGHT * 0.5) - (l.r_height_wall)
	+ s->player.y_eye + l.r_height_wall_diff;
	l.vs->right_floor_limit.x = l.vs->right_ceiling_limit.x;
	l.vs->right_floor_limit.y = (HEIGHT * 0.5) + s->player.y_eye
	+ l.r_height_wall_diff;
}

void	ft_limit_ceiling_floor3(t_main *s, t_dpos left, t_dpos right,
	t_ft_limit_ceiling_floor *l)
{
	if (l->swich == 1 || l->swich == 4)
	{
		l->l_plan = l->vs->left_plan;
		l->pos.pos1 = l->l_plan;
		l->pos.pos3 = left;
		l->pos.pos4 = right;
		ft_find_intersection(s, l->pos, 1);
		l->l_big_dist = (ft_dist_t_dpos(l->vs->player, s->tmp_intersect)
		/ METRE);
	}
	else
	{
		l->pos.pos1 = left;
		l->pos.pos3 = l->vs->left_plan;
		l->pos.pos4 = l->vs->right_plan;
		ft_find_intersection(s, l->pos, 1);
		l->l_plan = s->tmp_intersect;
		l->l_big_dist = (ft_dist_t_dpos(l->vs->player, left) / METRE);
	}
}

void	ft_limit_ceiling_floor4(t_main *s, t_dpos left, t_dpos right,
	t_ft_limit_ceiling_floor *l)
{
	if (l->swich == 3 || l->swich == 4)
	{
		l->r_plan = l->vs->right_plan;
		l->pos.pos1 = l->r_plan;
		l->pos.pos3 = left;
		l->pos.pos4 = right;
		ft_find_intersection(s, l->pos, 1);
		l->r_big_dist = (ft_dist_t_dpos(l->vs->player, s->tmp_intersect)
		/ METRE);
	}
	else
	{
		l->pos.pos1 = right;
		l->pos.pos3 = l->vs->left_plan;
		l->pos.pos4 = l->vs->right_plan;
		ft_find_intersection(s, l->pos, 1);
		l->r_plan = s->tmp_intersect;
		l->r_big_dist = (ft_dist_t_dpos(l->vs->player, right) / METRE);
	}
}

void	ft_limit_ceiling_floor(t_main *s, t_4dpos pos, t_visu *vs, char swich)
{
	t_ft_limit_ceiling_floor l;

	l.vs = vs;
	l.pos.pos2 = vs->player;
	l.swich = swich;
	ft_limit_ceiling_floor3(s, pos.pos1, pos.pos2, &l);
	ft_limit_ceiling_floor4(s, pos.pos1, pos.pos2, &l);
	l.l_small_dist = (ft_dist_t_dpos(l.vs->player, l.l_plan) / METRE);
	l.r_small_dist = (ft_dist_t_dpos(l.vs->player, l.r_plan) / METRE);
	l.l_height_wall = HEIGHT / ((((l.l_big_dist * 100.0)
	/ l.l_small_dist) * 0.001) * 4)
	* ft_abs(l.vs->sct->floor - l.vs->sct->ceiling) * HEIGHT_MULT;
	l.r_height_wall = HEIGHT / ((((l.r_big_dist * 100.0)
	/ l.r_small_dist) * 0.001) * 4)
	* ft_abs(l.vs->sct->floor - l.vs->sct->ceiling) * HEIGHT_MULT;
	l.pos.pos3 = pos.pos1;
	l.pos.pos4 = pos.pos2;
	ft_limit_ceiling_floor2(s, l);
}
