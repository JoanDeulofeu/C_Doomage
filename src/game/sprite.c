/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:52:36 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 13:39:23 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		display_sprites2(t_main *s, int fai)
{
	t_sprite	*spt;

	spt = s->sprite;
	while (spt)
	{
		if (spt->id == fai && spt->displayed == 1 && spt->set == 1
			&& spt->destroy == 0 && check_if_visible(s, spt))
		{
			play_sprites_anims(s);
			draw_sprite(s, spt);
			spt->displayed = 0;
		}
		spt = spt->next;
	}
}

void		display_sprites(t_main *s, int display, int fad, int fai)
{
	t_sprite	*spt;

	if (!(spt = s->sprite))
		return ;
	while (display)
	{
		display = 0;
		fad = 0;
		fai = 0;
		spt = s->sprite;
		while (spt)
		{
			if (spt->set == 1 && spt->displayed == 1
			&& spt->dist > fad && spt->destroy == 0)
			{
				display = 1;
				fad = spt->dist;
				fai = spt->id;
			}
			spt = spt->next;
		}
		if (!display)
			break ;
		display_sprites2(s, fai);
	}
}

int			ft_get_sprite_height_pxl(t_main *s, t_sprite *sprite, double height)
{
	double		pct_eyesight;
	t_sector	*sct;

	sct = get_sector_by_id(s, sprite->sct_id);
	s->player.eyesight = s->player.foot_height - sct->floor + s->player.size;
	pct_eyesight = (s->player.eyesight * 100 / sprite->size);
	return ((pct_eyesight * height) * 0.01);
}

void		draw_sprite2(t_main *s, t_sprite *cur, t_draw_sprite *d)
{
	while (d->coord.x < cur->x + d->w * 0.5 && d->coord.x >= 0
		&& d->coord.x <= WIDTH)
	{
		d->perx = (double)((d->coord.x - cur->x - d->w * 0.5) * 100) / (d->w);
		d->dhp = ft_get_sprite_height_pxl(s, cur, d->height);
		d->coord.y = (HEIGHT * 0.5) - d->height + s->player.y_eye + d->dhp;
		d->bottom = (HEIGHT * 0.5) + s->player.y_eye + d->dhp;
		d->tmp = d->coord.y;
		while (d->coord.y < d->bottom)
		{
			d->pery = (double)((d->coord.y - d->tmp) * 100) / d->height;
			if (cur->inverse == 0)
				d->px = (int)(d->pery * 0.01 * (double)d->wp->h) * d->wp->w
					+ (int)(d->perx * 0.01 * (double)d->wp->w);
			else
				d->px = (int)(d->pery * 0.01 * (double)d->wp->h) * d->wp->w
					- (int)(d->perx * 0.01 * (double)d->wp->w);
			if (d->px >= 0 && d->px < d->wp->w * d->wp->h
				&& d->wp->tex[d->px] != 65280)
				set_pixel(s->sdl->game, d->wp->tex[d->px], d->coord);
			d->coord.y++;
		}
		d->coord.x++;
	}
}

void		draw_sprite(t_main *s, t_sprite *cur)
{
	t_draw_sprite d;

	d.wp = cur->anim.image[cur->current];
	d.pct = (cur->r_dist * METRE * 100) / cur->l_dist;
	d.height = HEIGHT / ((d.pct * 0.001) * 4) * cur->size * HEIGHT_MULT;
	d.pct = (100 * d.wp->w) / d.wp->h;
	d.w = (d.pct * d.height) * 0.01;
	d.coord.x = cur->x - (d.w * 0.5);
	draw_sprite2(s, cur, &d);
}
