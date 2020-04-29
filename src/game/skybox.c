/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:15:06 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/09 12:51:30 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_transition(t_main *s)
{
	int		diff_y_eye;
	double	diff_abs_angle;

	diff_y_eye = abs(s->transition_y_eye - MOON_Y) / TRANSITION_SPEED;
	diff_abs_angle = (double)(abs(s->transition_angle - 70)) / TRANSITION_SPEED;
	if (s->transition_angle < 70)
	{
		s->player.angle += diff_abs_angle;
		s->player.abs_angle += diff_abs_angle;
	}
	else
	{
		s->player.angle -= diff_abs_angle;
		s->player.abs_angle -= diff_abs_angle;
	}
	if (s->transition_y_eye < MOON_Y)
		s->player.y_eye += diff_y_eye;
	else
		s->player.y_eye -= diff_y_eye;
	if (s->transition++ > TRANSITION_SPEED)
		s->transition = 0;
}

void	destroy_planet(t_main *s)
{
	if (s->skybox.current == 0)
		Mix_PlayChannel(3, s->sdl->sounds.explode, 0);
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

void	display_sky(t_main *s, int px, double value)
{
	t_dpos	per;
	t_pos	coord;

	value = (s->skybox.image[s->skybox.current]->w * W_MUL
		* s->player.abs_angle) / 360;
	coord.x = -1;
	while (coord.x < WIDTH)
	{
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
