#include "doom.h"

void	create_anchor(t_main *s, t_pos ori)
{
	t_vertex	*temp;
	int			correc_x;
	int			correc_y;

	temp = s->vertex;
	correc_x = 0;
	correc_y = 0;
	if (s->editor->decal_x % s->editor->space != 0 && s->editor->decal_x < 0)
		correc_x = -1;
	if (s->editor->decal_y % s->editor->space != 0 && s->editor->decal_y < 0)
		correc_y = -1;
	ori.x = s->editor->ref.x + (ori.x / s->editor->space) + correc_x;
	ori.y = s->editor->ref.y + (ori.y / s->editor->space) + correc_y;
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y)
		{
			temp->selected = 1;
			return;
		}
		temp = temp->next;
	}
	ft_add_vertex(s, ori.x, ori.y);
}

void	draw_anchor(t_main *s, t_pos ori, Uint32 color)
{
	t_dpos		init;
	t_dpos		dest;
	short		size;

	// size = 5;
	size = s->editor->anchor_size;
	init.x = ori.x - size;
	init.y = ori.y - size;
	dest.x = ori.x + size;
	dest.y = ori.y + size;
	draw_rect(s->sdl->editor, init, dest, color);
}
