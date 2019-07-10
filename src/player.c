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

void 	rotate_player(t_main *s , const Uint8 *keys)
{
	double angle;

	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
	{
		angle = s->player.angle + (keys[LEFT_NUM] - keys[RIGHT_NUM]) * ROTATE_SPEED / 10 + 360;
		s->player.angle = (int)angle % 360;

	}
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

double  to_rad(double angle)
{
    return (angle * M_PI / 180.0);
}

t_dpos	get_direction(t_main *s, const Uint8 *keys, double speed, t_dpos target)
{
	if (keys[UP])
	{
		target.x += cos(to_rad(s->player.angle)) * speed;
		target.y -= sin(to_rad(s->player.angle)) * speed;
	}
	if (keys[DOWN])
	{
		target.x -= cos(to_rad(s->player.angle * -1)) * speed;
		target.y -= sin(to_rad(s->player.angle * -1)) * speed;
	}
	if (keys[LEFT])
	{
		target.x += cos(to_rad(s->player.angle + 90)) * speed;
		target.y -= sin(to_rad(s->player.angle + 90)) * speed;
	}
	if (keys[RIGHT])
	{
		target.x += cos(to_rad(s->player.angle - 90)) * speed;
		target.y -= sin(to_rad(s->player.angle - 90)) * speed;
	}
	//printf("angle = %d\n",s->player.angle);

	//printf("target.x = %f\ntarget.y = %f\n",target.x,target.y);
	return (target);
}

void	ft_ft_move_player(t_main *s, const Uint8 *keys, char sprint)
{
	t_dpos	target;
	double	speed;
  	int     move_speed;

  	move_speed = 2;
	speed = move_speed + sprint * move_speed * 0.5;
	if ((keys[UP] || keys[DOWN]) && (keys[LEFT] || keys[RIGHT]))
		speed /= 2;
	target.x = s->player.pos.x;//position en pixel ou origine
	target.y = s->player.pos.y;
	target = get_direction(s, keys, speed, target);
//	if (check_collisions(s, target) == 0)
//	{
//	tmp = target.x;
//	target.x = s->player.pos.x;
//		if (check_collisions(s, target) == 0)
//		{
//	target.x = tmp;
//	target.y = s->player.pos.y;
//			if (check_collisions(s, target) == 0)
//				return ;
//		}
//	}
	//s->player.pos.x = target.x > WIDTH - 1 ? WIDTH - 1 : target.x;
	//s->player.pos.y = target.y > HEIGHT - 1 ? HEIGHT - 1 : target.y;
	s->player.pos.x = target.x;
	s->player.pos.y = target.y;
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
