#include "doom.h"

void 			destroy_planet(t_main *s)
{
		if (s->skybox.current == 0)
			Mix_PlayChannel(2, s->sdl->sounds.explode, 0);
		if (s->skybox.image[s->skybox.current +1])
			s->skybox.current ++;
}

void			display_sky(t_main *s)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	double		value;
	int 		j;
	float			w_mul;

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
