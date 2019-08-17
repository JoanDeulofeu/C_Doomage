#include "doom.h"

void display_crosshair(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;


	coord.x = 0;
	coord.y = 0;
	wp = s->player.crosshair;
	//wp = s->player.weapon.image[s->player.weapon.current];
	//coord.x = WIDTH / 2 - (wp->w / 2);

	while (i < wp->w)
	{
		j = 0;//dont touch
		coord.x = i ;

		perx = (double)coord.x / (double)wp->w;
		coord.x += WIDTH/2;

		while (j < wp->h)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)wp->h;
			coord.y += HEIGHT/2;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
}

void 	shoot(t_main *s, int press)
{
	struct timeval 	tv;
	t_time 			t;
	long            curr_time;

	gettimeofday(&tv, (void *)t.v0id);
	curr_time = tv.tv_sec * 1000000 + tv.tv_usec;
	if (press == 1 && s->player.t.fin_time < curr_time)
	{

		t.fin_time = curr_time + 1100000;
		t.tmp_time = curr_time;
		s->player.t.recoil.y = 0;
		s->player.t.recoil.x = 0;
		s->player.t = t;

	}
	if (s->player.t.tmp_time + 150000 > curr_time )
	{
		s->player.weapon.current = 0;
		s->player.t.recoil.y = 50;
		s->player.t.recoil.x = 100;
	}
	else if (s->player.t.tmp_time + 151000 > curr_time )
	{
		s->player.weapon.current = 0;
		s->player.t.recoil.y = 0;
		s->player.t.recoil.x = 0;
	}
	else if (s->player.t.tmp_time + 300000  > curr_time)
		s->player.weapon.current = 1;
	else if (s->player.t.tmp_time + 450000  > curr_time)
		s->player.weapon.current = 2;
	else if (s->player.t.tmp_time + 500000  > curr_time)
		s->player.weapon.current = 3;
	else if (s->player.t.tmp_time + 650000  > curr_time)
		s->player.weapon.current = 4;
	else if (s->player.t.tmp_time + 800000  > curr_time)
		s->player.weapon.current = 5;
	else if (s->player.t.tmp_time + 950000  > curr_time)
		s->player.weapon.current = 4;
	else if (s->player.t.tmp_time + 1080000  > curr_time)
		s->player.weapon.current = 3;
	else
		s->player.weapon.current = 1;
}

void 	draw_hud(t_main *s)
{
	shoot(s,-1);
	draw_weapon(s, 0, WIDTH / 2 - (s->player.weapon.image[s->player.weapon.current]->w / 2 ), HEIGHT - s->player.weapon.image[s->player.weapon.current]->h - s->player.weapon.image[s->player.weapon.current]->h);
	//draw_weapon(s, 0, WIDTH / 2 - (s->player.weapon.image[s->player.weapon.current]->w / 2), HEIGHT - s->player.weapon.image[s->player.weapon.current]->h - s->player.weapon.image[s->player.weapon.current]->h);
	display_crosshair(s, 0, 0);

	display_hud(s, 0, 0);
}

void	draw_weapon(t_main *s, double perx, short orig_x, short orig_y)
{
	t_pos	coord;
	t_pos	dest;
	double		pery;
	int			pix_tex;
	t_image		*wp;

	//printf("recoil = %d\n",s->player.t.recoil);
	wp = s->player.weapon.image[s->player.weapon.current];
	dest.x = WIDTH / 2 + (wp->w / 2) + 100;
	dest.y = HEIGHT ;
	coord.x = orig_x;
	//coord.x += s->player.t.recoil.x;

	while (coord.x < dest.x)
	{
		coord.y = orig_y;
		perx = percent(coord.x - orig_x , dest.x - orig_x);// - s->player.t.recoil;
	//	coord.y += s->player.t.recoil.y;
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
