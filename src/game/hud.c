#include "doom.h"

void		animate_shotgun(t_main *s)
{
	long	time;

	if (s->player.shoot == 0)
		return ;
	time = s->time->time_ms - s->time->shotgun_ms;
	if (time >= 0 && time <= 200)
		s->player.weapon.current = 1;
	else if (time > 200 && time <= 300)
		s->player.weapon.current = 2;
	else if (time > 300 && time <= 400)
		s->player.weapon.current = 3;
	else if (time > 400 && time <= 500)
		s->player.weapon.current = 4;
	else if (time > 500 && time <= 600)
		s->player.weapon.current = 5;
	else if (time > 600 && time <= 700)
		s->player.weapon.current = 6;
	else if (time > 700 && time <= 800)
		s->player.weapon.current = 5;
	else if (time > 800 && time <= 900)
		s->player.weapon.current = 4;
	else if (time > 900)
		{
			s->player.weapon.current = 0;
			s->player.shoot = 0;
		}
}

void		animate_gun(t_main *s)
{
	long	time;

	if (s->player.shoot == 0)
		return ;
	time = s->time->time_ms - s->time->shotgun_ms;
	if (time > 100 && time <= 150)
		s->player.weapon.current = 1;
	if (time > 150 && time <= 250)
		s->player.weapon.current = 2;
	if (time > 250)
	{
		s->player.weapon.current = 0;
		s->player.shoot = 0;
	}
}

void		animate_kick(t_main *s)
{
	long	time;

	if (s->player.shoot == 0)
		return ;
	time = s->time->time_ms - s->time->shotgun_ms;
	if (time <= 200)
	s->player.weapon.current = 1;
	else if (time > 200 && time <= 400)
	{
		s->player.weapon.current = 2;
	}
	else if (time > 400 && time <= 600)
	{
		s->player.weapon.current = 3;
	}
	else
	{
		s->player.weapon.current = 0;
		s->player.shoot = 0;
	}

}

void		animate_weapon(t_main *s)
{
	if (s->player.wp_name == shotgun)
		animate_shotgun(s);
	else if (s->player.wp_name == gun)
		animate_gun(s);
	else if (s->player.wp_name == kick)
		animate_kick(s);
}

void		shoot(t_main *s)
{
	if (s->player.shoot == 0)
	{
		s->player.shoot = 1;
		s->time->shotgun_ms = s->time->time_ms;

		fire(s);
		if (s->player.wp_name == gun && s->player.mun_gun > 0)
		{
			Mix_PlayChannel(2, s->sdl->sounds.gun, 0);
			animate_weapon(s);
			s->player.mun_gun--;
		}

		else if (s->player.wp_name == shotgun && s->player.mun_shotgun > 0)
		{
			Mix_PlayChannel(2, s->sdl->sounds.shotgun, 0);
			animate_weapon(s);
			s->player.mun_shotgun--;
		}
		else if (s->player.wp_name == kick)
			animate_weapon(s);
	}
}

void	draw_weapon(t_main *s, double perx, short orig_x, short orig_y)
{
	t_pos	coord;
	t_pos	dest;
	double		pery;
	int			pix_tex;
	t_image		*wp;

	wp = s->player.weapon.image[s->player.weapon.current];
	dest.x = orig_x + wp->w + 100;
	dest.y = HEIGHT - s->player.hud->h ;
	if (s->player.weapon.current == 1 && s->player.wp_name == shotgun)
	{
		orig_y += 50;
		dest.y += 50;
	}

	coord.x = orig_x;
	while (coord.x < dest.x)
	{
		coord.y = orig_y;
		perx = percent(coord.x - orig_x , dest.x - orig_x);
		while (coord.y < dest.y)
		{
			coord.y++;

			pery = percent(coord.y - orig_y, dest.y - orig_y);
			pix_tex = (int)(pery * wp->h) * wp->w + (int)(perx * wp->w);
			if (pix_tex <= wp->h * wp->w && wp->tex[pix_tex] != 10676224)
				set_pixel(s->sdl->game, wp->tex[pix_tex], coord);
		}
		coord.x++;
	}
}

void		draw_hud(t_main *s)
{
	if (s->player.weapon.image[s->player.weapon.current])
		draw_weapon(s, 0, WIDTH* 0.5 + (s->player.weapon.image[s->player.weapon.current]->w), HEIGHT - (s->player.weapon.image[s->player.weapon.current]->h * 2) - s->player.hud->h);
	display_crosshair(s, 0, 0);
	display_hud(s, 0, 0);
}

void		display_crosshair(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;

	coord.x = 0;
	coord.y = 0;
	wp = s->player.crosshair;
	//coord.x = WIDTH* 0.5 - (wp->w* 0.5);
	while (i < wp->w)
	{
		j = 0;//dont touch
		coord.x = i;
		perx = (double)coord.x / (double)wp->w;
		coord.x += WIDTH* 0.5 - (wp->w* 0.5);
		while (j < wp->h)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)wp->h;
			coord.y += HEIGHT* 0.5 - (wp->h* 0.5);
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx
				* (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
}

void		display_hud(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;

	coord.x = 0;
	wp = s->player.hud;
	while (i < WIDTH)
	{
		j = 0;
		coord.y = HEIGHT - 129;
		coord.x = i;
		perx = (double)coord.x / (double)WIDTH;
		while (j < 129)
		{
			pery = (double)j / 129;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx
				* (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
			j++;
			coord.y++;
		}
		i++;
	}
}
