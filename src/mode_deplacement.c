#include "doom.h"

void	mouse_grid(t_main *s, t_pos save)
{
	s->editor->decal_x += save.x;
	s->editor->decal_y += save.y;
	//printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);
	//printf("save X = %d et save Y = %d\n", save.x, save.y);
	//printf("ref X = %d et ref Y = %d\n", s->editor->ref.x, s->editor->ref.y);
	//printf("decal X = %d et decal Y = %d\n", s->editor->decal_x, s->editor->decal_y);
	// printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);
}
