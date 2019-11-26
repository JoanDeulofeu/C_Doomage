#include "doom.h"

void		ft_zoom(t_main *s, t_pos mouse, int space)
{
	t_pos		ori;
	t_pos		p_ori;
	t_pos		diff;
	t_dpos		r_pos;
	t_editor	*edi;

	edi = s->editor;
	ori.x = arround(s->editor->space, mouse.x
		- (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, mouse.y
		- (s->editor->decal_y % s->editor->space));
	p_ori.x = mouse.x - ori.x;
	p_ori.y = mouse.y - ori.y;
	ori = get_abs_pos(s, ori);
	r_pos.x = (double)ori.x + ((double)p_ori.x / edi->space);
	r_pos.y = (double)ori.y + ((double)p_ori.y / edi->space);
	s->player.pos.x -= s->editor->decal_x;
	s->player.pos.y -= s->editor->decal_y;
	s->player.pos.x /= (double)(s->editor->space);
	s->player.pos.y /= (double)(s->editor->space);
	s->editor->space += space;
	s->player.pos.x *= (double)(s->editor->space);
	s->player.pos.y *= (double)(s->editor->space);
	diff.x = r_pos.x * (-space);
	diff.y = r_pos.y * (-space);
	s->editor->decal_x += diff.x;
	s->editor->decal_y += diff.y;
	s->player.pos.x += s->editor->decal_x;
	s->player.pos.y += s->editor->decal_y;
}

void		rotate_mouse(t_main *s)
{
	double	angle;

	angle = s->player.angle + (-s->sdl->event.motion.xrel)
		* ROTATE_SPEED / 50 + 360;
	s->player.angle = (int)angle % 360;
	s->player.abs_angle = (int)(s->player.abs_angle + + (-s->sdl->event.motion.xrel)
		* ROTATE_SPEED / 50 + 360) % 360;
	s->player.y_eye = (s->player.y_eye + (-s->sdl->event.motion.yrel)
		* ROTATE_SPEED / 10);
	if (s->player.y_eye > 1000)
		s->player.y_eye = 1000;
	else if (s->player.y_eye < -1000)
		s->player.y_eye = -1000;
}

void	ft_crouch(t_main *s, const Uint8 *keys)
{
	if (keys[LCTRL])
	{
		if ((s->time->time_ms > s->time->crouch_ms + 25) && s->player.size > 1.05)
		{
			s->player.size -= 0.1;
			s->time->crouch_ms = s->time->time_ms;
			// printf("Crouch - \nPlayer size %.2f\n\n", s->player.size);
		}
	}
	else
	{
		if ((s->time->time_ms > s->time->crouch_ms + 25) && s->player.size < PLAYER_SIZE)
		{
			s->player.size += 0.1;
			s->time->crouch_ms = s->time->time_ms;
			// printf("Crouch + \nPlayer size %.2f\n\n", s->player.size);
		}
	}
}

void	ft_jump(t_main *s, const Uint8 *keys)
{
	//pour player->jump, 0 = pas de jump, 1 = phase montante, 2 = descendante
	if (keys[SDL_SCANCODE_SPACE] && s->player.jump == 0)
		s->player.jump = 1;
	if (s->player.jump == 1 && (s->time->time_ms > s->time->jump_ms + 10)
	&& s->player.jump_height < JUMP_SIZE)
	{
		if (s->player.jump_height < 0.5)
			s->player.jump_height += 0.2;
		else
			s->player.jump_height += 0.1;
		s->time->jump_ms = s->time->time_ms;
		if (s->player.jump_height >= JUMP_SIZE)
			s->player.jump = 2;
	}
	if (s->player.jump == 2 && (s->time->time_ms > s->time->jump_ms + 10)
	&& s->player.jump_height > 0)
	{
		if (s->player.jump_height < 0.7)
			s->player.jump_height -= 0.2;
		else
			s->player.jump_height -= 0.1;
		s->time->jump_ms = s->time->time_ms;
		if (s->player.jump_height <= 0)
		{
			s->player.jump = 0;
			s->player.jump_height = 0;
		}
	}
}
