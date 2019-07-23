#include "doom.h"

void  	ft_zoom(t_main *s, t_pos pos, int space)
{
	t_pos ori;
	t_pos p_ori;
	t_pos diff;
	t_dpos 		r_pos;
	t_editor 	*edi;

	edi = s->editor;
	ori.x = arround(s->editor->space, pos.x - (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, pos.y - (s->editor->decal_y % s->editor->space));
	p_ori.x = pos.x - ori.x;
	p_ori.y = pos.y - ori.y;
	ori = get_abs_pos(s,ori);
	r_pos.x = (double)ori.x + ((double)p_ori.x / edi->space);
	r_pos.y = (double)ori.y + ((double)p_ori.y / edi->space);
	s->editor->space += space;
	diff.x = r_pos.x * (-space);
	diff.y = r_pos.y * (-space);
	s->editor->decal_x += diff.x;
	s->editor->decal_y += diff.y;
}
