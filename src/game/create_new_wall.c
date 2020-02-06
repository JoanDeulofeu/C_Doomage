/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:07:32 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 14:08:11 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_create_new_wall2(t_walls *wall, t_int *vtx, t_visu *vs, int part)
{
	if (part == 1)
	{
		ft_bzero((void *)wall, sizeof(t_walls));
		if (vtx->image)
			wall->image = vtx->image;
		wall->nb_tex = vtx->tex_nb;
		wall->player = vs->player;
		wall->angle = vs->angle;
		wall->sct_id = vs->sct_id;
		wall->portal_value = 0;
	}
	else
	{
		wall->left_ceiling_limit = vs->left_ceiling_limit;
		wall->left_floor_limit = vs->left_floor_limit;
		wall->right_ceiling_limit = vs->right_ceiling_limit;
		wall->right_floor_limit = vs->right_floor_limit;
		wall->floor_height = vs->sct->floor;
		wall->ceiling_height = vs->sct->ceiling;
	}
}

t_4dpos		ft_create_new_wall3(t_main *s, t_4dpos pos, t_walls *wall,
	t_visu *vs)
{
	int			dist;

	pos.pos1 = vs->left_point;
	pos.pos2 = vs->player;
	dist = ft_find_intersection(s, pos, 1);
	if (dist > 0)
		wall->left = s->tmp_intersect;
	else
		wall->left = pos.pos3;
	pos.pos1 = wall->left;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	wall->l_plan = s->tmp_intersect;
	if (dist > 0 && !s->walls)
		wall->x = 0;
	else
		wall->x = (ft_dist_t_dpos(pos.pos3, wall->l_plan) / WIDTHPLAN) * WIDTH;
	pos.pos1 = vs->right_point;
	pos.pos2 = vs->player;
	return (pos);
}

int			ft_create_new_wall4(t_main *s, t_4dpos pos, t_visu *vs,
	t_walls *wall)
{
	pos.pos1 = wall->right;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	wall->r_plan = s->tmp_intersect;
	get_wall_distance(wall, vs);
	if (ft_dist_t_dpos(wall->l_plan, vs->left_plan)
	<= ft_dist_t_dpos(wall->r_plan, vs->left_plan)
	&& abs(ceil(ft_dist_t_dpos(wall->r_plan, vs->player))
	- ceil(ft_dist_t_dpos(vs->left_plan, vs->player)) < 1))
		add_wall_to_list(s, wall);
	else
	{
		ft_memdel((void **)&wall);
		return (1);
	}
	return (0);
}

t_walls		*ft_create_new_wall5(t_main *s, t_int *vtx, t_walls *wall,
	char w_or_p)
{
	t_sector	*sct;

	sct = NULL;
	if (w_or_p == 'p')
	{
		sct = get_sector_by_id(s, vtx->sct_dest);
		wall->floor_height_dest = sct->floor;
		wall->ceiling_height_dest = sct->ceiling;
		wall->portal_value = vtx->vtx_dest->ptr->id;
	}
	wall->screen_width_wall = (WIDTH * ((ft_dist_t_dpos(wall->l_plan,
		wall->r_plan) * 100.0) / WIDTHPLAN)) / 100;
	return (wall);
}

t_walls		*ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs, char w_or_p)
{
	t_walls		*wall;
	t_4dpos		pos;

	if (!(wall = (t_walls*)malloc(sizeof(t_walls))))
		handle_error(s, MALLOC_ERROR);
	ft_create_new_wall2(wall, vtx, vs, 1);
	wall->id = ++s->wall_fk_id;
	wall->wall_or_portal = w_or_p;
	wall->r_right = vtx->next->ptr->m_pos;
	wall->r_left = vtx->ptr->m_pos;
	pos.pos3 = vtx->ptr->m_pos;
	pos.pos4 = vtx->next->ptr->m_pos;
	pos = ft_create_new_wall3(s, pos, wall, vs);
	pos.pos3 = vtx->ptr->m_pos;
	pos.pos4 = vtx->next->ptr->m_pos;
	if (ft_find_intersection(s, pos, 1) > 0)
		wall->right = s->tmp_intersect;
	else
		wall->right = vtx->next->ptr->m_pos;
	if (ft_create_new_wall4(s, pos, vs, wall))
		return (NULL);
	ft_create_new_wall2(wall, vtx, vs, 2);
	return (ft_create_new_wall5(s, vtx, wall, w_or_p));
}
