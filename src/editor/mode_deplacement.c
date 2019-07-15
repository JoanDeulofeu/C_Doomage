#include "doom.h"

void	mouse_grid(t_main *s, t_pos save)
{
	if (s->editor->decal_x + save.x > INT_MIN && s->editor->decal_x + save.x < INT_MAX)
		s->editor->decal_x += save.x;
	if (s->editor->decal_y + save.y > INT_MIN && s->editor->decal_y + save.y < INT_MAX)
		s->editor->decal_y += save.y;
	//s->player.pos.x += save.x;
	//s->player.pos.y += save.y;

	//printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);
	//printf("save X = %d et save Y = %d\n", save.x, save.y);
	//printf("ref X = %d et ref Y = %d\n", s->editor->ref.x, s->editor->ref.y);
	//printf("decal X = %d et decal Y = %d\n", s->editor->decal_x, s->editor->decal_y);
	// printf("souris X = %f et souris Y = %f\n", s->ft_mouse.x, s->ft_mouse.y);
}

void		move_editor(t_main *s, const Uint8 *keys)
{
	if (keys[RIGHT_AR] && (s->editor->decal_x < INT_MAX) && (s->player.pos.x < INT_MAX))
	{
		s->editor->decal_x += 5;
		s->player.pos.x += 5;
	}
	if (keys[LEFT_AR] && (s->editor->decal_x > INT_MIN) && (s->player.pos.x > INT_MIN))
	{
		s->player.pos.x -= 5;
		s->editor->decal_x -= 5;
	}
	if (keys[UP_AR] && (s->editor->decal_y > INT_MIN) && (s->player.pos.y > INT_MIN))
	{
		s->player.pos.y -= 5;
		s->editor->decal_y -= 5;
	}
	if (keys[DOWN_AR] && (s->editor->decal_y < INT_MAX) && (s->player.pos.y < INT_MAX))
	{
		s->player.pos.y += 5;
		s->editor->decal_y += 5;
	}
}

// void	move_player(t_main *s, int key)
// {
// 	if (key == UP)
// 	{
// 		s->player.pos.y -= 1;
//
// 	}
// 	if (key == DOWN)
// 	{
// 		s->player.pos.y += 1;
//
// 	}
// 	if (key == LEFT)
// 	{
// 		s->player.pos.x -= 1;
//
// 	}
// 	if (key == RIGHT)
// 	{
// 		s->player.pos.x += 1;
//
// 	}
// /*
// 	printf("refx = %d\n", s->player.p_ref.x);
// 	printf("refy = %d\n", s->player.p_ref.y);
// 	printf("player.pos.x = %d\n",s->player.pos.x);
// 	printf("player.pos.y = %d\n",s->player.pos.y);
// 	printf("ori.x = %d\n",s->player.ori.x);
// 	printf("ori.y = %d\n",s->player.ori.y);
// 	printf("p_ori.x = %d\n",s->player.p_ori.x);
// 	printf("p_ori.y = %d\n",s->player.p_ori.y);
//
// 	printf("space = %d\n", s->editor->space );
// 	printf("init_space = %d\n", s->player.init_space);
// 	printf("decalx = %d\n", s->editor->decal_x );
// 	printf("decaly = %d\n", s->editor->decal_y );
// */
//
// }
