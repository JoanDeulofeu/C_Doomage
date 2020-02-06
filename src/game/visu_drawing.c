/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:59:33 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 14:59:36 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		print_wall_or_sprite2(t_main *s, t_walls *wall, t_sprite *farthest)
{
	t_4dpos		pos;

	if (wall->l_dist > farthest->dist || wall->b_dist > farthest->dist)
	{
		pos.pos1 = wall->left;
		pos.pos2 = wall->right;
		pos.pos3 = wall->player;
		pos.pos4 = farthest->m_pos;
		if (ft_find_intersection(s, pos, 1) && wall->wall_or_portal == 'w')
		{
			print_sprite(s, farthest);
			return (0);
		}
		else
		{
			ft_print_wall(s, wall);
			return (1);
		}
	}
	else
	{
		print_sprite(s, farthest);
		return (0);
	}
}

int		print_wall_or_sprite(t_main *s, t_walls *wall)
{
	t_sprite	*sprite;
	t_sprite	*farthest;
	int			dist;

	sprite = s->sprite;
	farthest = NULL;
	dist = 0;
	while (sprite)
	{
		if (sprite->set && sprite->displayed && sprite->dist > dist
			&& sprite->destroy == 0)
		{
			farthest = sprite;
			dist = farthest->dist;
		}
		sprite = sprite->next;
	}
	if (!farthest)
	{
		ft_print_wall(s, wall);
		return (1);
	}
	if (print_wall_or_sprite2(s, wall, farthest))
		return (1);
	return (0);
}

void	ft_init_diff_and_min(t_walls *wall)
{
	wall->diffx_ceiling = ft_abs(wall->left_ceiling_limit.x
	- wall->right_ceiling_limit.x);
	wall->diffy_ceiling = ft_abs(wall->left_ceiling_limit.y
	- wall->right_ceiling_limit.y);
	wall->minx_ceiling = wall->left_ceiling_limit.x
	< wall->right_ceiling_limit.x ? wall->left_ceiling_limit.x
	: wall->right_ceiling_limit.x;
	wall->miny_ceiling = wall->left_ceiling_limit.y
	< wall->right_ceiling_limit.y ? wall->left_ceiling_limit.y
	: wall->right_ceiling_limit.y;
	wall->diffx_floor = ft_abs(wall->left_floor_limit.x
	- wall->right_floor_limit.x);
	wall->diffy_floor = ft_abs(wall->left_floor_limit.y
	- wall->right_floor_limit.y);
	wall->minx_floor = wall->left_floor_limit.x < wall->right_floor_limit.x
	? wall->left_floor_limit.x : wall->right_floor_limit.x;
	wall->miny_floor = wall->left_floor_limit.y < wall->right_floor_limit.y
	? wall->left_floor_limit.y : wall->right_floor_limit.y;
}

void	ft_print_wall(t_main *s, t_walls *wall)
{
	double	l_pct;
	double	r_pct;
	double	l_height_wall;
	double	r_height_wall;

	l_pct = (ft_dist_t_dpos(wall->player, wall->left) * 100.0)
	/ ft_dist_t_dpos(wall->player, wall->l_plan);
	r_pct = (ft_dist_t_dpos(wall->player, wall->right) * 100.0)
	/ ft_dist_t_dpos(wall->player, wall->r_plan);
	l_height_wall = HEIGHT / ((l_pct * 0.001) * 4)
	* (double)abs(wall->floor_height - wall->ceiling_height) * HEIGHT_MULT;
	r_height_wall = HEIGHT / ((r_pct * 0.001) * 4)
	* (double)abs(wall->floor_height - wall->ceiling_height) * HEIGHT_MULT;
	ft_init_diff_and_min(wall);
	ft_multi_threading(s, wall, l_height_wall, r_height_wall,
	wall->screen_width_wall);
}

void	ft_draw_visu(t_main *s, t_sector *sct, t_visu vs)
{
	t_walls		*wall;
	t_int		*vtx;

	vtx = sct->vertex;
	vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	if (!(vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id)))
		return ;
	create_all_walls(s, vtx, &vs, 1);
	set_visible_sprites(s, &vs);
	wall = s->walls;
	while (wall)
		if (print_wall_or_sprite(s, wall) == 1)
			wall = wall->next;
	display_sprites(s);
	s->portal_nb = 0;
}
