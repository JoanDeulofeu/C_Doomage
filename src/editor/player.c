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
	s->player.r_pos.x = s->player.pos.x - edi->decal_x;
	s->player.r_pos.x = (s->player.r_pos.x / edi->space);
	s->player.r_pos.y = s->player.pos.y - edi->decal_y;
	s->player.r_pos.y = (s->player.r_pos.y / edi->space);
	if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT) && s->player.set == 1)
	{
		draw_anchor(s, pos, BLUE);
		trace_direction(s);
	}

}

void 	rotate_player(t_main *s , const Uint8 *keys)
{
	double angle;

	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
	{
		angle = s->player.angle + (keys[RIGHT_NUM] - keys[LEFT_NUM]) * ROTATE_SPEED / 10 + 360;
		s->player.angle = (int)angle % 360;

	}
}

void 	trace_direction(t_main *s)
{

	s->player.line.x1 = s->player.pos.x;
	s->player.line.y1 = s->player.pos.y;
	s->player.line.x2 = s->player.line.x1 + cos(to_rad(s->player.angle)) * 20;
	s->player.line.y2 = s->player.line.y1 - sin(to_rad(s->player.angle)) * 20;
	//printf("direction.line = (%d,%d)\n",s->player.line.x2,s->player.line.y2);

	//s->player.line.x2 = s->ft_mouse.x;
	//s->player.line.y2 = s->ft_mouse.y;
	ft_get_line(s, s->player.line, BLUE);

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
	return (target);
}

void	ft_move_player(t_main *s, const Uint8 *keys)
{
	t_dpos	target;
	double	speed;
  	int     move_speed;

  	move_speed = 2;
	speed = move_speed * move_speed * 0.5;
	if ((keys[UP] || keys[DOWN]) && (keys[LEFT] || keys[RIGHT]))
		speed /= 1.5;
	if (keys[SPRINT] && keys[UP])
		speed *= 3;
	target.x = s->player.pos.x;
	target.y = s->player.pos.y;
	target = get_direction(s, keys, speed, target);
	s->col_pos = get_direction(s, keys, speed + 10, s->player.pos);
	// printf("player.x = %f, player.y = %f\n", s->player.pos.x, s->player.pos.y);
	// printf("col.x = %f, col.y = %f\n", s->col_pos.x, s->col_pos.y);
	// draw_anchor(s, ft_dpos_to_pos(s->col_pos), BLUE);
	// update_image(s, s->sdl->editor);
	//printf("sector = %d\n",ft_is_in_sector(s, ft_dpos_to_pos(target)));
	if (!is_colliding(s))
	{
		s->player.pos.x = target.x;
		s->player.pos.y = target.y;
	}
	if (is_colliding(s) > 0)
		teleport_player(s, keys);
}

void	ft_trace_vertical(t_main *s, t_line line, Uint32 color)
{
	int sens_x;
	int sens_y;
	t_pos coord;
	int px;

	px = -1;
	line.e = line.y2 > line.y1 ? line.y2 - line.y1 : line.y1 - line.y2;
	sens_x = line.x2 > line.x1 ? 1 : -1;
	sens_y = line.y2 > line.y1 ? 1 : -1;
	line.dy = line.e * 2;
	line.dx = line.x2 > line.x1 ? (line.x2 - line.x1) * 2 : (line.x1 - line.x2) * 2;
	line.pixel_o = line.y1;
	while (line.y1 != line.y2 && ++px < 20)
	{
		coord.x = line.x1;
		coord.y = line.y1;
		set_pixel(s->sdl->editor, color, coord);
		line.y1 += sens_y;
		if ((line.e -= line.dx) <= 0)
		{
			line.x1 += sens_x;
			line.e += line.dy;
		}
	}
}

int		ft_trace_line(t_main *s, t_line line, Uint32 color)
{
	int sens_x;
	int sens_y;
	t_pos coord;

	sens_x = line.x2 > line.x1 ? 1 : -1;
	sens_y = line.y2 > line.y1 ? 1 : -1;
	if (line.dx < line.dy)
	{
		ft_trace_vertical(s, line, color);
		return (0);
	}
	line.pixel_o = line.x1;
	while (line.x1 != line.x2)
	{
		coord.x = line.x1;
		coord.y = line.y1;
		set_pixel(s->sdl->editor, color, coord);
		line.x1 += sens_x;
		if ((line.e -= line.dy) <= 0)
		{
			line.y1 += sens_y;
			line.e += line.dx;
		}
	}
	return (0);
}

void	ft_get_line(t_main *s, t_line line, Uint32 color)
{
		line.e = line.x2 > line.x1 ? line.x2 - line.x1 : line.x1 - line.x2;
		line.dy = line.y2 > line.y1 ? (line.y2 - line.y1) * 2 : (line.y1 - line.y2) * 2;
		line.dx = line.e * 2;
		ft_trace_line(s, line, color);
}
