#include "doom.h"

void mouse_grid(t_main *s, t_pos save)
{
	int diffx;
	int diffy;
	t_pos diff;
	t_pos 	ori;

	//ori.x = arround(s->editor->space, 0 - (s->editor->decal_x % s->editor->space));
	//ori.y = arround(s->editor->space, 0 - (s->editor->decal_y % s->editor->space));
	//ori = get_abs_pos(s,s->player.ori);

	//diff.x = s->ft_mouse.x - save.x;
	//diff.y = s->ft_mouse.y - save.y;
	//s->editor->ref = get_abs_pos(s,diff);
	s->editor->decal_x += save.x;
	s->editor->decal_y += save.y;
	//s->editor->ref.x = ft_find_ref(s->editor, s->editor->decal_x);
	//s->editor->ref.y = ft_find_ref(s->editor, s->editor->decal_y);
	printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);
	printf("save X = %d et save Y = %d\n", save.x, save.y);
	printf("ref X = %d et ref Y = %d\n", s->editor->ref.x, s->editor->ref.y);
	printf("decal X = %d et decal Y = %d\n", s->editor->decal_x, s->editor->decal_y);
	// printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);
}
