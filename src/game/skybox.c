#include "doom.h"

void			display_sky(t_main *s)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image 	*wp;
	double		value;

	wp = s->skybox;
	value = wp->w / 360;
	value = value * (s->player.angle);
	coord.x = -1;
	while (coord.x++ < WIDTH)
	{
		coord.y = -1;
		perx = (double)(coord.x + value) / (double)WIDTH;
		while (coord.y++ < HEIGHT)
		{
			pery = (double)coord.y / (double)HEIGHT;
			px = (int)(pery * (double)wp->h) * wp->w + (int)
				(perx * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h)
			set_pixel(s->sdl->game, wp->tex[px], coord);
		}
	}
}
