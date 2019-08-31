#include "doom.h"

void	trace_vertical(t_main *s, Uint32 color, int w)
{
	int sens_x;
	int sens_y;
	t_pos coord;
	int		i;

	// i = 0;
	s->line.e = s->line.y2 > s->line.y1 ? s->line.y2 - s->line.y1 : s->line.y1 - s->line.y2;
	sens_x = s->line.x2 > s->line.x1 ? 1 : -1;
	sens_y = s->line.y2 > s->line.y1 ? 1 : -1;
	s->line.dy = s->line.e * 2;
	s->line.dx = s->line.x2 > s->line.x1 ? (s->line.x2 - s->line.x1) * 2 : (s->line.x1 - s->line.x2) * 2;
	s->line.pixel_o = s->line.y1;
	while (s->line.y1 != s->line.y2)
	{
		for (i = 0; i < w; i++)
		{
			coord.x = s->line.x1 + i;
			coord.y = s->line.y1 + i;
			set_pixel(s->sdl->editor, color, coord);
			coord.x = s->line.x1 - i;
			coord.y = s->line.y1 - i;
			set_pixel(s->sdl->editor, color, coord);
		}
		s->line.y1 += sens_y;
		if ((s->line.e -= s->line.dx) <= 0)
		{
			s->line.x1 += sens_x;
			s->line.e += s->line.dy;
		}
	}
}

void	get_line(t_main *s, Uint32 color, int w)
{
		s->line.e = s->line.x2 > s->line.x1 ? s->line.x2 - s->line.x1 : s->line.x1 - s->line.x2;
		s->line.dy = s->line.y2 > s->line.y1 ? (s->line.y2 - s->line.y1) * 2 : (s->line.y1 - s->line.y2) * 2;
		s->line.dx = s->line.e * 2;
		trace_line(s, color, w);
}

int		trace_line(t_main *s, Uint32 color, int w)
{
	int sens_x;
	int sens_y;
	// int perct;
	t_pos coord;
	int		i;

	// i = 0;
	sens_x = s->line.x2 > s->line.x1 ? 1 : -1;
	sens_y = s->line.y2 > s->line.y1 ? 1 : -1;
	if (s->line.dx < s->line.dy)
		trace_vertical(s, color, w);
	s->line.pixel_o = s->line.x1;
	while (s->line.x1 != s->line.x2)
	{
		for (i = 0; i < w; i++)
		{
			coord.x = s->line.x1 + i;
			coord.y = s->line.y1 + i;
			set_pixel(s->sdl->editor, color, coord);
			coord.x = s->line.x1 - i;
			coord.y = s->line.y1 - i;
			set_pixel(s->sdl->editor, color, coord);
		}
		s->line.x1 += sens_x;
		if ((s->line.e -= s->line.dy) <= 0)
		{
			s->line.y1 += sens_y;
			s->line.e += s->line.dx;
		}
	}
	return (0);
}
