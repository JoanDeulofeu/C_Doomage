#include "doom.h"

void	ft_gridx(t_texture *tex, t_dpos *orig, t_dpos *dest, t_pos *coord)
{
	int			x;
	int			y;
	Uint32		color = 0x4c4c4c7F;

	x = orig->x;
	y = orig->y;
	while (y <= dest->y)
	{
		while (x <= dest->x)
		{
			coord->x = x;
			coord->y = y;
			set_pixel(tex, color, *coord);
			x++;
		}
		x = orig->x;
		y += G_SPACE;
	}
}

void	ft_gridy(t_texture *tex, t_dpos *orig, t_dpos *dest, t_pos *coord)
{
	int			x;
	int			y;
	Uint32		color = 0x4c4c4c7F;

	x = orig->x;
	y = orig->y;
	while (x <= dest->x)
	{
		while (y <= dest->y)
		{
			coord->x = x;
			coord->y = y;
			set_pixel(tex, color, *coord);
			y++;
		}
		y = orig->y;
		x += G_SPACE;
	}
}

void	ft_draw_grid(t_texture *tex)
{
	t_dpos		orig;
	t_dpos		dest;
	// int			nbcase = 32;
	t_pos		coord;

	// espx = (WIDTH - 20) / nbcase;
	// espy = (HEIGHT - 20) / nbcase;
	orig.x = GRID_SIDE_MARGIN;
	orig.y = GRID_TOP_MARGIN;
	dest.x = WIDTH - GRID_SIDE_MARGIN;
	dest.y = HEIGHT - GRID_SIDE_MARGIN;

	ft_gridx(tex, &orig, &dest, &coord);
	ft_gridy(tex, &orig, &dest, &coord);

}

void	draw_wall(t_main *s, t_pos ori)
{
	s->line.x1 = ori.x;
	s->line.y1 = ori.y;
	get_line(s, WHITE);
}
