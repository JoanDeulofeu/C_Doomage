#include "doom.h"

int		arround(int space, int nb)
{
	int res;
	int res2;

	res = nb / space;
	res2 = res + 1;
	return (nb - (space * res) > space * res2
	- nb ? space * res2 : space * res);
}

t_pos	get_abs_pos(t_main *s, t_pos ori)
{
	t_pos	res;
	int		correc_x;
	int		correc_y;

	res.x = 0;
	res.y = 0;
	correc_x = 0;
	correc_y = 0;
	if (s->editor->decal_x % s->editor->space != 0 && s->editor->decal_x < 0)
		correc_x = -1;
	if (s->editor->decal_y % s->editor->space != 0 && s->editor->decal_y < 0)
		correc_y = -1;
	res.x = s->editor->ref.x + (ori.x / s->editor->space) + correc_x;
	res.y = s->editor->ref.y + (ori.y / s->editor->space) + correc_y;
	return (res);
}

Uint32	get_pixel_color(t_texture *text, int x, int y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (text->content[x + y * WIDTH]);
	else
		return (2);
}
