#include "doom.h"

void			display_sky(t_main *s)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	double		value;
	int j;

	value = (s->skybox->w * 2 * s->player.abs_angle) / 360;
	coord.x = 0;
	while (coord.x++ < WIDTH)
	{
		j = 0;
		coord.y = -1;
		perx = (double)(coord.x - value) / (double)s->skybox->w;
		while (coord.y < HEIGHT)
		{
			perx = (double)(coord.x - value)  / ((double)s->skybox->w * 2);
			pery = ((double)coord.y - s->player.y_eye + HEIGHT * 1.3) / ((double)HEIGHT * 2.5);
			pery = pery > 1.0 ? 1.0 : pery;
			pery = pery < 0.0 ? 0.0 : pery;
			// coord.y -= HEIGHT / 2 - ((s->player.y_eye + s->player.eyesight));
			px = (int)(pery * (double)s->skybox->h) * s->skybox->w + (int)
				(perx * (double)s->skybox->w);
			if (px >= 0 && px < s->skybox->w * s->skybox->h)
				set_pixel(s->sdl->game, s->skybox->tex[px], coord);
			// set_pixel(s->sdl->game, 0x485050ff, coord);
			coord.y++;
		}
	}
}

// void			display_sky(t_main *s)
// {
//    double		perx;
//    double		pery;
//    t_pos		coord;
//    int			px;
//    t_image 	*wp;
//    double		fov;
//    double		angle_left;
//    double		pct_text;
//    double		pct_begin;
//
//    wp = s->skybox;
//    coord.x = -1;
//    fov = ft_find_angle_portal(&s->sky.player, &s->sky.left_point, &s->sky.right_point, 1);
//    // printf("fov = %.2f\n", fov);
//    angle_left = s->player.angle - (fov / 2);
//    // printf("angle = %.2f\n", angle_left);
//    pct_text = (fov * 100) / 360;
//    // printf("pct = %.2f\n", pct_text);
//    pct_begin = 0;
//    while (coord.x++ < WIDTH)
//    {
// 	   coord.y = -1;
// 	   perx = (double)coord.x / (double)WIDTH;
// 	   while (coord.y++ < HEIGHT)
// 	   {
// 		   pery = (double)coord.y / (double)HEIGHT;
// 		   px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
// 		   if (px >= 0 && px < wp->w * wp->h)
// 			   set_pixel(s->sdl->game, wp->tex[px], coord);
// 	   }
//    }
// }
