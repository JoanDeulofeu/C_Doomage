/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:26:59 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 17:27:30 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	get_wall_distance(t_walls *wall, t_visu *vs)
{
	int	dist1;
	int dist2;

	dist1 = ft_dist_t_dpos(wall->left, vs->player);
	dist2 = ft_dist_t_dpos(wall->right, vs->player);
	if (dist1 <= dist2)
	{
		wall->l_dist = dist1;
		wall->b_dist = dist2;
	}
	else
	{
		wall->l_dist = dist2;
		wall->b_dist = dist1;
	}
}

void	ft_draw_column(t_pos coord, int end, t_multithread *mt)
{
	if (mt->s->sct_without_ceiling != mt->wall->sct_id)
		coord.y = ft_draw_ceiling(mt->s, mt->wall, coord);
	if (((mt->wall->wall_or_portal == 'w') || (mt->wall->wall_or_portal == 'p'
		&& (mt->wall->floor_height_dest > mt->wall->floor_height
		|| mt->wall->ceiling_height_dest < mt->wall->ceiling_height)))
		&& coord.y < HEIGHT)
	{
		if (mt->wall->image)
			draw_texture(mt, coord, end);
		else
		{
			if (coord.y < 0)
				coord.y = -1;
			while (coord.y++ < end)
				set_pixel(mt->s->sdl->game, 0xb0842fff, coord);
		}
	}
	coord.y = end - 1;
	if (coord.y < HEIGHT)
		ft_draw_floor(mt->s, mt->wall, coord);
}

int		ft_get_diff_height_pxl(double eyesight, int ceiling_height,
	int floor_height, int height_wall)
{
	int		ig_height_wall;
	double	pct_eyesight;

	ig_height_wall = ceiling_height - floor_height;
	pct_eyesight = (eyesight * 100 / ig_height_wall);
	return ((pct_eyesight * height_wall) * 0.01);
}
