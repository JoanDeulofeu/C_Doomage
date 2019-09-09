#include "doom.h"

void	draw_skybox(t_main *s, t_visu vs)
{
	double	angle = 0.0;
	double	pery;
	int		px_tex;

	angle = angle > 360.0 ? angle - 360.0 : angle;
	angle = angle < 0 ? angle + 360.0 : angle;
	angle = (angle / 360.0);
	vs.pixel.y = -1;
	while (++(vs.pixel.y) < vs.begin_wall_id && vs.pixel.y < HEIGHT - s->interface->h)
	{
		pery = (double)(vs.pixel.y - s->viewline + HEIGHT * 1.5) / (HEIGHT * 2.2);
		pery = pery > 1.0 ? 1.0 : pery;
		pery = pery < 0.0 ? 0.0 : pery;
		px_tex = (int)((angle * s->skybox->w) + s->skybox->w
			* (int)(s->skybox->h * pery));
		if (px_tex < s->skybox->w * s->skybox->h && px_tex >= 0)
			vs.color = s->skybox->tex[px_tex];
		set_pixel(s->sdl->game, vs.color, vs.pixel);
	}
}
