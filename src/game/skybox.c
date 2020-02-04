#include "doom.h"

void 			destroy_planet(t_main *s)
{
		t_pos 	coord;

		coord.x = 0;
		coord.y = 0;
		if (s->skybox.current == 0)
			Mix_PlayChannel(2, s->sdl->sounds.explode, 0);
		if (s->skybox.image[s->skybox.current +1])
			s->skybox.current ++;
		else
			ending(s, 0);
}

void			display_sky(t_main *s)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	double		value;
	int 		j;
	float		w_mul;

	w_mul = 2.6;
	value = (s->skybox.image[s->skybox.current]->w * w_mul * s->player.abs_angle) / 360;
	coord.x = -1;
	while (coord.x < WIDTH)
	{
		j = 0;
		coord.y = -1;
		perx = (double)(coord.x - value) / (double)s->skybox.image[s->skybox.current]->w * w_mul;
		if (perx < 0)
			perx = 0;
		while (coord.y < HEIGHT)
		{
			perx = (double)(coord.x - value)  / ((double)s->skybox.image[s->skybox.current]->w * w_mul);
			pery = ((double)coord.y - s->player.y_eye + HEIGHT * 1.3) / ((double)HEIGHT * 2.6);
			pery = pery > 1.0 ? 1.0 : pery;
			pery = pery < 0.0 ? 0.0 : pery;
			px = (int)(pery * (double)s->skybox.image[s->skybox.current]->h) * s->skybox.image[s->skybox.current]->w + (int)
				(perx * (double)s->skybox.image[s->skybox.current]->w);
			if (px >= 0 && px < s->skybox.image[s->skybox.current]->w * s->skybox.image[s->skybox.current]->h)
				set_pixel(s->sdl->game, s->skybox.image[s->skybox.current]->tex[px], coord);
			coord.y++;
		}
		coord.x++;
	}
}
