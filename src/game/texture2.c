/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:38:01 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 16:39:19 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	get_total_w_wall(t_walls *wall)
{
	double		dist_screen;
	double		dist_total;
	double		dist_left;
	double		perc;

	dist_screen = ft_dist_t_dpos(wall->right, wall->left);
	dist_total = ft_dist_t_dpos(wall->r_right, wall->r_left);
	dist_left = ft_dist_t_dpos(wall->left, wall->r_left);
	dist_total = (dist_total == 0) ? 1 : dist_total;
	perc = (dist_screen * 100) / dist_total;
	perc = (perc == 0) ? 1 : perc;
	wall->total_width_wall = (100 * wall->screen_width_wall) / perc;
	dist_total = (dist_total == 0) ? 1 : dist_total;
	perc = (dist_left * 100) / dist_total;
	wall->left_void_side = (perc * wall->total_width_wall) * 0.01;
}

void	ft_limit_portal_texture(t_multithread *mt, int end,
	int *limit_ceiling, int *limit_floor)
{
	int	diff_haute;
	int	diff_total;
	int	diff_total_pxl;
	int	diff_basse;

	diff_haute = mt->wall->ceiling_height - mt->wall->ceiling_height_dest;
	diff_basse = mt->wall->floor_height_dest - mt->wall->floor_height;
	diff_total = mt->wall->ceiling_height - mt->wall->floor_height;
	diff_total_pxl = mt->wall_height_tmp;
	*limit_ceiling = (end - mt->wall_height_tmp) + ((diff_haute * 100
		/ diff_total) * diff_total_pxl) * 0.01;
	*limit_floor = end - ((diff_basse * 100 / diff_total)
	* diff_total_pxl) * 0.01;
}

void	draw_texture2(t_multithread *mt, t_pos *coord, int end,
	t_draw_texture *d)
{
	d->limit_ceiling = 0;
	d->limit_floor = 0;
	if (mt->wall->wall_or_portal == 'p')
		ft_limit_portal_texture(mt, end, &d->limit_ceiling, &d->limit_floor);
	d->y = (coord->y < 0) ? 1 + abs(coord->y) : 1;
	d->x = mt->wall->total_width_wall - mt->wall->screen_width_wall
	+ mt->avcm_x;
	if ((mt->wall->left.x == mt->wall->r_left.x) && (mt->wall->left.y
		== mt->wall->r_left.y) && ((mt->wall->right.x != mt->wall->r_right.x)
		|| (mt->wall->right.y != mt->wall->r_right.y)))
		d->x = mt->avcm_x;
	else if (((mt->wall->left.x != mt->wall->r_left.x) || (mt->wall->left.y
		!= mt->wall->r_left.y)) && ((mt->wall->right.x != mt->wall->r_right.x)
		|| (mt->wall->right.y != mt->wall->r_right.y)))
		d->x = mt->wall->left_void_side + mt->avcm_x;
	d->nb_tex_x = (ft_dist_t_dpos(mt->wall->r_left, mt->wall->r_right)
	/ METRE) * 0.5;
	d->nb_tex_y = abs(mt->wall->floor_height - mt->wall->ceiling_height);
	d->tex_size_x = mt->wall->total_width_wall / d->nb_tex_x;
	d->tex_size_y = (end - coord->y) / d->nb_tex_y;
	d->perx = (fmod((double)d->x, d->tex_size_x)) * 100 / d->tex_size_x;
	if (d->limit_floor > HEIGHT)
		d->limit_floor = HEIGHT;
}

void	draw_texture3(t_multithread *mt, t_pos *coord, t_draw_texture *d)
{
	if (coord->y < 0)
		coord->y = 0;
	if ((mt->wall->wall_or_portal == 'p') && (coord->y > d->limit_ceiling))
	{
		coord->y = d->limit_floor;
		if (d->limit_floor < 0)
			d->y = 0 - d->limit_floor;
		else
			d->y = 0;
	}
	if (coord->y < 0)
		coord->y = 0;
}

void	draw_texture(t_multithread *mt, t_pos coord, int end)
{
	t_draw_texture d;

	draw_texture2(mt, &coord, end, &d);
	draw_texture3(mt, &coord, &d);
	while (coord.y < end && coord.y < HEIGHT)
	{
		if (mt->wall->wall_or_portal == 'p')
		{
			if (coord.y == d.limit_ceiling)
			{
				coord.y = d.limit_floor;
				d.y = 0;
			}
		}
		d.pery = (fmod((double)d.y, d.tex_size_y)) * 100 / d.tex_size_y;
		d.px = (int)((d.pery * (double)mt->wall->image->h) * 0.01)
		* mt->wall->image->w
			+ (int)((d.perx * (double)mt->wall->image->w) * 0.01);
		if (d.px >= 0 && d.px < mt->wall->image->w * mt->wall->image->h
			&& mt->wall->image->tex[d.px] != 65280)
			set_pixel(mt->s->sdl->game, mt->wall->image->tex[d.px], coord);
		d.y++;
		coord.y++;
	}
}
