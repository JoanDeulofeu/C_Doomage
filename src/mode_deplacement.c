#include "doom.h"

void mouse_grid(t_main *s, t_pos save)
{
	int diffx;
	int diffy;

	diffx = s->ft_mouse.x - save.x;
	diffy = s->ft_mouse.y - save.y;
	s->editor->decal_x += diffx;
	s->editor->decal_y += diffy;
	// printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);
	// printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);

}
