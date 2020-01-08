#include "doom.h"

void	display_croix_rouge(t_main *s, int i, int j, t_pos crd)
{
	int			px;
	int			stopi;
	int			stopj;

	px = 0;
	stopi = i + s->savemap->croix_rouge->w;
	stopj = j + s->savemap->croix_rouge->h;
	while ((crd.x = i) < stopi)
	{
		j = 0;
		while (j < stopj)
		{
			crd.y = j++;
			px = (int)(((double)crd.y / (double)stopj)
			* (double)s->savemap->croix_rouge->h) * s->savemap->croix_rouge->w
			+ (int)(((double)crd.x / (double)stopi)
			* (double)s->savemap->croix_rouge->w);
			if (px >= 0 && px < s->savemap->croix_rouge->w
				* s->savemap->croix_rouge->h)
				set_pixel(s->sdl->save, s->savemap->croix_rouge->tex[px], crd);
		}
		i++;
	}
}

void	ft_click_save(t_main *s)
{
	if ((s->ft_mouse.x > 0 && s->ft_mouse.x < s->savemap->croix_rouge->w)
	&& (s->ft_mouse.y > 0 && s->ft_mouse.y < s->savemap->croix_rouge->h))
	{
		s->display_mode = 0;
		change_mode(s, MOVE);
	}
}

void	ft_draw_rect_text(t_main *s)
{
	t_pos		coord;
	int			stopx;
	int			stopy;

	coord.x = 230;
	coord.y = 450;
	stopx = coord.x + 500;
	stopy = coord.y + 40;
	while (coord.y <= stopy)
	{
		while (coord.x <= stopx)
		{
			if ((coord.x == 230 || coord.x == stopx)
			|| (coord.y == 450 || coord.y == stopy))
				set_pixel(s->sdl->save, 0xd23b3bff, coord);
			else
				set_pixel(s->sdl->save, 0x606060ff, coord);
			coord.x++;
		}
		coord.y++;
		coord.x = 230;
	}
}

void	ft_draw_write_bar(t_main *s)
{
	int		lg;
	t_pos	coord;
	int		x_end;
	int		y_end;

	lg = ft_strlen(s->savemap->str);
	coord.x = 240 + (lg * 10);
	x_end = coord.x + 3;
	coord.y = 457;
	y_end = coord.y + 25;
	while (coord.x++ < x_end)
	{
		while (coord.y++ < y_end)
			set_pixel(s->sdl->save, 0x45d6daff, coord);
		coord.y = 457;
	}
}

void	ft_save_map(t_main *s)
{
	struct timeval	tv;
	double			mill;
	long			sec;
	t_pos			coord;

	coord.x = 0;
	coord.y = 0;
	gettimeofday(&tv, NULL);
	mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	sec = mill;
	display_croix_rouge(s, 20, 20, coord);
	ft_draw_rect_text(s);
	if (sec % 800 < 400)
		ft_draw_write_bar(s);
}
