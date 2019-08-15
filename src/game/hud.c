#include "doom.h"

void 	draw_hud(t_main *s)
{
	draw_weapon(s, 0, WIDTH / 2 - (s->player.weapon.image[s->player.weapon.current]->w / 2), HEIGHT - s->player.weapon.image[s->player.weapon.current]->h - s->player.weapon.image[s->player.weapon.current]->h);	
	display_hud(s, 0, 0);
}

void	draw_weapon(t_main *s, double perx, short orig_x, short orig_y)
{
	t_pos	coord;
	t_pos	dest;
	double		pery;
	int			pix_tex;
	t_image		*wp;

	//printf("ok\n");
	wp = s->player.weapon.image[s->player.weapon.current];
	dest.x = WIDTH / 2 + (wp->w / 2);
	dest.y = HEIGHT;// - s->player.weapon.image[s->player.weapon.current]->h;
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

			// printf("%d  ", pix_tex);
			//printf("%d  ", wp->tex[pix_tex]);
			if (pix_tex <= wp->h * wp->w && wp->tex[pix_tex] != 10676224)
				set_pixel(s->sdl->game, wp->tex[pix_tex], coord);
		}
		coord.x++;
	}
	// update_image(s, s->sdl->game);

}


void	display_hud(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;


	coord.x = 0;
	coord.y = 0;
	wp = s->player.hud;
	//wp = s->player.weapon.image[s->player.weapon.current];


	while (i < WIDTH)
	{
		j = 0;
		coord.x = i;
		perx = (double)coord.x / (double)WIDTH;
		while (j < HEIGHT)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)HEIGHT;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
			//  printf("%d  ", px);
			// printf("%d  ", wp->tex[px]);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
	//update_image(s, s->sdl->game);
}
