#include "doom.h"

void	ft_draw_editor(t_editor *edi, t_texture *tex)
{
	int		modu;
	t_pos	coord;
	Uint32	color = 0x4c4c4c7F;

	coord.x = edi->decal_x % edi->space;
	coord.y = edi->decal_y % edi->space;
	// edi->ref.x = 11 = (decal_x + (space - coord.x)) / space;
	if (coord.x != 0)
		edi->ref.x = (edi->decal_x > 0) ? (edi->decal_x / edi->space) + 1 : (edi->decal_x / edi->space) - 1;
	if (coord.y != 0)
		edi->ref.y = (edi->decal_y > 0) ? (edi->decal_y / edi->space) + 1 : (edi->decal_y / edi->space) - 1;
	while (coord.y < HEIGHT)
	{
		while (coord.x < WIDTH)
		{
			set_pixel(tex, color, *coord);
			coord.x += edi->space;
		}
		coord.x = edi->decal_x % edi->space;
		coord.y += edi->space;
	}
}

void	draw_wall(t_main *s, t_pos ori)
{
	s->line.x1 = ori.x;
	s->line.y1 = ori.y;
	get_line(s, WHITE);
}
