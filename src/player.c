#include "doom.h"


void set_player(t_main *s)
{
	t_pos		pos;
	t_editor 	*edi;
	int 		correc;
	t_dpos 		res;

	correc = 0;
	edi = s->editor;
	s->player.ori.x = arround(s->editor->space, s->player.pos.x - (s->editor->decal_x % s->editor->space));
	s->player.ori.y = arround(s->editor->space, s->player.pos.y - (s->editor->decal_y % s->editor->space));
	s->player.p_ori.x = s->player.pos.x - s->player.ori.x;
	s->player.p_ori.y = s->player.pos.y - s->player.ori.y;
	s->player.ori = get_abs_pos(s,s->player.ori);
	s->player.init_space = s->editor->space;
	s->player.p_ref = get_px_pos(s, s->editor->ref);
	if (s->editor->decal_x <= 0)
		s->player.correc = s->editor->decal_x % s->editor->space != 0 ? 1 : 0;
	else
		s->player.correc = 0;
	s->player.ori.x += s->player.correc;
	if (s->editor->decal_y <= 0)
		s->player.correc = s->editor->decal_y % s->editor->space != 0 ? 1 : 0;
	else
		s->player.correc = 0;
	s->player.ori.y += s->player.correc;

	if (edi->decal_x <= 0)
		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	//s->player.ori.x += correc;
	pos.x = (s->player.ori.x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
	if (edi->decal_y <= 0)
		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (s->player.ori.y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
	res.x = ((double)s->player.p_ori.x / (double)s->player.init_space) * edi->space;
	res.y = ((double)s->player.p_ori.y / (double)s->player.init_space) * edi->space;
	pos.x += (int)res.x - s->player.p_ref.x;
	pos.y += (int)res.y - s->player.p_ref.y;
	s->player.r_pos.x = (double)s->player.ori.x + ((double)s->player.p_ori.x / edi->space);
	s->player.r_pos.y = (double)s->player.ori.y + ((double)s->player.p_ori.y / edi->space);
	if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
		draw_anchor(s, pos, BLUE);
	// printf("r_pos.x = %f\n",s->player.r_pos.x);
	// printf("r_pos.y = %f\n",s->player.r_pos.y);
}

void	ft_move_player(t_main *s, const Uint8 *key)
{
	if (key[UP])
		s->player.pos.y -= 2;
	if (key[DOWN])
		s->player.pos.y += 2;
	if (key[LEFT])
		s->player.pos.x -= 2;
	if (key[RIGHT])
		s->player.pos.x += 2;
}
	/*if (key[RIGHT_NUM])
	if (key[LEFT_NUM])
	if (key[UP_NUM])
	if (key[DOWN_NUM])
*/

/*
	if (key[LEFT_NUM] || key[RIGHT_NUM])
	{
		x = vector->x;
		c = cos(angle);
		s = sin(angle);
		vector->x = vector->x * c - vector->y * s;
		vector->y = x * s + vector->y * c;
		s->player.angle = (double)(s->player.angle + (key[LEFT_AR] - key[RIGHT_AR]) * ROTATE_SPEED / 10 + 360) % 360;

	}*/
