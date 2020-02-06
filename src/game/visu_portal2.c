/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_portal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:03:15 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 17:03:18 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		check_portal_validity2(t_main *s, t_int *vtx, t_visu *vs, int gap)
{
	t_4dpos pos;

	pos.pos1 = vs->left_point;
	pos.pos2 = vs->player;
	pos.pos3 = (gap == METRE) ? vtx->next->ptr->m_pos : vtx->ptr->m_pos;
	pos.pos4 = (gap == METRE) ? vtx->ptr->m_pos : vtx->next->ptr->m_pos;
	if (ft_find_intersection(s, pos, 1) > 0)
		pos.pos1 = s->tmp_intersect;
	else
		pos.pos1 = pos.pos3;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
}

void		check_portal_validity3(t_main *s, t_int *vtx, t_visu *vs, int gap)
{
	t_4dpos pos;

	pos.pos1 = vs->right_point;
	pos.pos3 = (gap == METRE) ? vtx->next->ptr->m_pos : vtx->ptr->m_pos;
	pos.pos4 = (gap == METRE) ? vtx->ptr->m_pos : vtx->next->ptr->m_pos;
	if (ft_find_intersection(s, pos, 1) > 0)
		pos.pos1 = s->tmp_intersect;
	else
		pos.pos1 = pos.pos4;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
}

int			check_portal_validity(t_main *s, t_int *vtx, t_visu *vs, int gap)
{
	t_dpos	l_plan;
	t_dpos	r_plan;

	check_portal_validity2(s, vtx, vs, gap);
	l_plan = s->tmp_intersect;
	check_portal_validity3(s, vtx, vs, gap);
	r_plan = s->tmp_intersect;
	if (ft_dist_t_dpos(l_plan, vs->left_plan)
	<= ft_dist_t_dpos(r_plan, vs->left_plan)
	&& abs(ceil(ft_dist_t_dpos(r_plan, vs->player))
	- ceil(ft_dist_t_dpos(vs->left_plan, vs->player)) < gap))
		return (1);
	return (0);
}

int			check_walls_lenght(t_int *wall1, t_int *wall2)
{
	t_dpos	beg1;
	t_dpos	beg2;
	t_dpos	end1;
	t_dpos	end2;

	end1 = wall1->next->ptr->m_pos;
	end2 = wall2->next->ptr->m_pos;
	beg1 = wall1->ptr->m_pos;
	beg2 = wall2->ptr->m_pos;
	if (ft_dist_t_dpos(beg1, end1) == ft_dist_t_dpos(beg2, end2))
		return (1);
	return (0);
}

double		ft_find_angle_portal(t_dpos *left, t_dpos *right,
	t_dpos *third, int needed)
{
	double	angle;
	double	left_right;
	double	right_third;
	double	left_third;
	t_dpos	tmp_third;

	angle = 0;
	if (!third)
	{
		third = &tmp_third;
		third->x = left->x + 100;
		third->y = left->y;
	}
	left_third = ft_dist_t_dpos(*third, *left);
	right_third = ft_dist_t_dpos(*third, *right);
	left_right = ft_dist_t_dpos(*left, *right);
	if (needed == 1)
		angle = ft_find_angle_plan(left_third, left_right, right_third);
	else if (needed == 2)
		angle = ft_find_angle_plan(left_right, right_third, left_third);
	else if (needed == 3)
		angle = ft_find_angle_plan(left_third, right_third, left_right);
	return (angle);
}
