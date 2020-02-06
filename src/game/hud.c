/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:21:56 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 12:25:30 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_weapon_2(t_main *s, short orig_x, short orig_y, t_pos dest)
{
	t_pos		coord;
	int			pix_tex;
	double		pery;
	double		perx;
	t_image		*wp;

	wp = s->player.weapon.image[s->player.weapon.current];
	coord.x = orig_x;
	while (coord.x < dest.x)
	{
		coord.y = orig_y;
		perx = percent(coord.x - orig_x, dest.x - orig_x);
		while (coord.y < dest.y)
		{
			coord.y++;
			pery = percent(coord.y - orig_y, dest.y - orig_y);
			pix_tex = (int)(pery * wp->h) * wp->w + (int)(perx * wp->w);
			if (pix_tex <= wp->h * wp->w && wp->tex[pix_tex] != 10676224)
				set_pixel(s->sdl->game, wp->tex[pix_tex], coord);
		}
		coord.x++;
	}
}

void		draw_weapon(t_main *s, short orig_x, short orig_y)
{
	t_pos		dest;
	t_image		*wp;

	wp = s->player.weapon.image[s->player.weapon.current];
	dest.x = orig_x + wp->w + 100;
	dest.y = HEIGHT - s->player.hud->h;
	if (s->player.weapon.current == 1 && s->player.wp_name == shotgun)
	{
		orig_y += 50;
		dest.y += 50;
	}
	draw_weapon_2(s, orig_x, orig_y, dest);
}

void		draw_hud(t_main *s)
{
	if (s->player.weapon.image[s->player.weapon.current])
		draw_weapon(s, WIDTH * 0.5 +
			(s->player.weapon.image[s->player.weapon.current]->w),
			HEIGHT - (s->player.weapon.image[s->player.weapon.current]->h * 2)
			- s->player.hud->h);
	display_crosshair(s, 0, 0, s->player.crosshair);
	display_hud(s, 0, 0, 0);
}

void		display_crosshair(t_main *s, int i, int j, t_image *wp)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;

	coord.x = 0;
	coord.y = 0;
	while (i < wp->w)
	{
		j = 0;
		coord.x = i;
		perx = (double)coord.x / (double)wp->w;
		coord.x += WIDTH * 0.5 - (wp->w * 0.5);
		while (j < wp->h)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)wp->h;
			coord.y += HEIGHT * 0.5 - (wp->h * 0.5);
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx
					* (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
}

void		display_hud(t_main *s, int i, int j, int px)
{
	double		perx;
	double		pery;
	t_pos		coord;
	t_image		*wp;

	coord.x = 0;
	wp = s->player.hud;
	while (i < WIDTH)
	{
		j = 0;
		coord.y = HEIGHT - 129;
		coord.x = i;
		perx = (double)coord.x / (double)WIDTH;
		while (j < 129)
		{
			pery = (double)j / 129;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx
					* (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
			j++;
			coord.y++;
		}
		i++;
	}
}
