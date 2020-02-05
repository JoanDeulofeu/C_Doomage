/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:15:06 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/05 16:15:09 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	destroy_planet(t_main *s)
{
	t_pos	coord;

	coord.x = 0;
	coord.y = 0;
	if (s->skybox.current == 0)
		Mix_PlayChannel(2, s->sdl->sounds.explode, 0);
	if (s->skybox.image[s->skybox.current + 1])
		s->skybox.current++;
	else
		ending(s, 0);
}

int		display_sky2(t_main *s, t_pos *coord, t_dpos *per, double *value)
{
	per->x = (double)(coord->x - *value)
	/ ((double)s->skybox.image[s->skybox.current]->w * W_MUL);
	per->y = ((double)coord->y - s->player.y_eye + HEIGHT * 1.3)
	/ ((double)HEIGHT * W_MUL);
	per->y = per->y > 1.0 ? 1.0 : per->y;
	per->y = per->y < 0.0 ? 0.0 : per->y;
	return ((int)(per->y * (double)s->skybox.image[s->skybox.current]->h)
	* s->skybox.image[s->skybox.current]->w
	+ (int)(per->x * (double)s->skybox.image[s->skybox.current]->w));
}

void	display_sky(t_main *s, int px, int j, double value)
{
	t_dpos	per;
	t_pos	coord;

	value = (s->skybox.image[s->skybox.current]->w * W_MUL
		* s->player.abs_angle) / 360;
	coord.x = -1;
	while (coord.x < WIDTH)
	{
		j = 0;
		coord.y = -1;
		per.x = (double)(coord.x - value)
		/ (double)s->skybox.image[s->skybox.current]->w * W_MUL;
		if (per.x < 0)
			per.x = 0;
		while (coord.y < HEIGHT)
		{
			px = display_sky2(s, &coord, &per, &value);
			if (px >= 0 && px < s->skybox.image[s->skybox.current]->w
				* s->skybox.image[s->skybox.current]->h)
				set_pixel(s->sdl->game,
					s->skybox.image[s->skybox.current]->tex[px], coord);
			coord.y++;
		}
		coord.x++;
	}
}
