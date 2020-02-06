/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:27:02 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 16:32:13 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_zoom(t_main *s, int space)
{
	t_pos		ori;
	t_pos		p_ori;
	t_pos		diff;

	ori.x = arround(s->editor->space, s->ft_mouse.x
		- (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, s->ft_mouse.y
		- (s->editor->decal_y % s->editor->space));
	p_ori.x = s->ft_mouse.x - ori.x;
	p_ori.y = s->ft_mouse.y - ori.y;
	ori = get_abs_pos(s, ori);
	s->player.pos.x -= s->editor->decal_x;
	s->player.pos.y -= s->editor->decal_y;
	s->player.pos.x /= (double)(s->editor->space);
	s->player.pos.y /= (double)(s->editor->space);
	s->editor->space += space;
	s->player.pos.x *= (double)(s->editor->space);
	s->player.pos.y *= (double)(s->editor->space);
	diff.x = (double)ori.x + ((double)p_ori.x / s->editor->space) * (-space);
	diff.y = (double)ori.y + ((double)p_ori.y / s->editor->space) * (-space);
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
	s->player.abs_angle = (int)(s->player.abs_angle
	+ (-s->sdl->event.motion.xrel)
		* ROTATE_SPEED / 50 + 360) % 360;
	s->player.y_eye = (s->player.y_eye + (-s->sdl->event.motion.yrel)
		* ROTATE_SPEED * 0.1);
	if (s->player.y_eye > 1000)
		s->player.y_eye = 1000;
	else if (s->player.y_eye < -1000)
		s->player.y_eye = -1000;
}

void		ft_crouch(t_main *s, const Uint8 *keys)
{
	if (keys[LCTRL])
	{
		if ((s->time->time_ms > s->time->crouch_ms + 25)
		&& s->player.size > 1.05)
		{
			s->player.size -= 0.1;
			s->time->crouch_ms = s->time->time_ms;
		}
	}
	else
	{
		if ((s->time->time_ms > s->time->crouch_ms + 25)
		&& s->player.size < PLAYER_SIZE)
		{
			s->player.size += 0.1;
			s->time->crouch_ms = s->time->time_ms;
		}
	}
}

void		jump_2(t_main *s)
{
	if (s->player.jump == 1 && (s->time->time_ms > s->time->jump_ms + 10))
	{
		if (s->player.jump_height < 0.5)
			s->player.jump_height += 0.2;
		else
			s->player.jump_height += 0.1;
		s->time->jump_ms = s->time->time_ms;
		if (s->player.jump_height >= JUMP_SIZE)
			s->player.jump = 3;
	}
	if (s->player.jump == 2 && (s->time->time_ms > s->time->jump_ms + 10)
	&& s->player.jump_height + 0.1 > 0)
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

void		ft_jump(t_main *s, const Uint8 *keys)
{
	if (s->player.fly == 0 && (s->player.jetpack == 0 || s->play_or_editor == 1)
	&& keys[SDL_SCANCODE_SPACE] && s->player.jump == 0 && (s->player.size
	+ JUMP_SIZE - 0.1 <= s->player.ceiling_height - s->player.floor_height))
		s->player.jump = 1;
	if (s->player.jump == 1 || s->player.jump == 2)
		jump_2(s);
	if (s->player.jump == 3 && (s->time->time_ms > s->time->jump_ms + 10)
	&& s->player.jump_height > 0)
	{
		s->player.jump_height -= 0.6 * s->player.tumble;
		s->player.tumble += 0.15;
		s->time->jump_ms = s->time->time_ms;
		if (s->player.jump_height <= 0)
		{
			s->player.tumble = 0;
			s->player.jump = 0;
			s->player.jump_height = 0;
		}
	}
}
