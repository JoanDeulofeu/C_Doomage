#include "doom.h"


void	set_player(t_main *s)
{
	s->player.pos = ft_pos_to_dpos(get_px_r_pos(s,s->player.r_pos));
	s->player.m_pos.x = s->player.r_pos.x * METRE;
	s->player.m_pos.y = s->player.r_pos.y * METRE;
	if (!(s->player.pos.x < 0 || s->player.pos.y < 0 || s->player.pos.x > WIDTH || s->player.pos.y > HEIGHT) && s->player.set == 1)
	{
		draw_anchor(s, ft_dpos_to_pos(s->player.pos), BLUE);
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

void	ft_move_player(t_main *s, const Uint8 *keys, int move_speed)
{
	t_dpos	target;
	double	speed;

	speed = move_speed * move_speed * 0.03;
	if ((keys[UP] || keys[DOWN]) && (keys[LEFT] || keys[RIGHT]))
		speed /= 1.5;
	if (keys[SPRINT] && keys[UP])
		speed *= 1.2;
	target = s->player.r_pos;
	target = get_direction(s, keys, speed, target);
	s->col_pos = get_direction(s, keys, speed + 10, s->player.m_pos);
	// draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, s->col_pos)), BLUE);
	// update_image(s, s->sdl->editor);
	//Si is_colliding renvoie -1, il y a collision, si il renvoie plus que 0 il faut se tp
	if (is_colliding(s) == 0)
	{
		s->player.r_pos.x = target.x;
		s->player.r_pos.y = target.y;
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
