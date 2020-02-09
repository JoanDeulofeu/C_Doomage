/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 11:20:20 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 11:26:08 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline void	mouse_move_1(t_main *s, t_editor *edi)
{
	if (edi->mode == vertex || edi->mode == sprite)
	{
		edi->line.x2 = s->sdl->event.motion.x;
		edi->line.y2 = s->sdl->event.motion.y;
	}
	if (edi->selected2 && edi->mode == vertex && !s->display_mode)
	{
		move_anchor(s, edi->id);
		move_vertex(s, edi->tmp_move, edi->ori, edi->id);
	}
	if (s->display_mode == game)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		rotate_mouse(s);
		edi->mode = move;
	}
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

static inline void	mouse_move_2(t_main *s, t_editor *edi)
{
	if (edi->mode == portal &&
		get_pixel_color(s->sdl->editor, s->ft_mouse.x,
			s->ft_mouse.y) == BLACK_SCREEN)
	{
		edi->over_portal = 0;
		edi->over_sector2 = 0;
		if (edi->portal_temp == 1)
		{
			if (edi->wall2)
				edi->wall2->selected = 0;
			edi->wall2 = NULL;
		}
		else if (edi->portal_temp == 0)
		{
			if (edi->wall && !edi->wall2)
			{
				edi->wall->selected = 0;
				edi->wall = NULL;
			}
			else
				edi->over_sector = 0;
		}
	}
}

void				handle_editor_mouse_move_event(t_main *s, t_editor *edi)
{
	s->ft_mouse.x = s->sdl->event.motion.x;
	s->ft_mouse.y = s->sdl->event.motion.y;
	mouse_move_1(s, edi);
	mouse_move_2(s, edi);
	if (edi->mode == move && edi->selected2 == 1)
	{
		s->player.pos.x -= edi->decal_x;
		s->player.pos.y -= edi->decal_y;
		edi->decal_x = edi->tmp.x + s->ft_mouse.x - edi->mouse_save.x;
		edi->decal_y = edi->tmp.y + s->ft_mouse.y - edi->mouse_save.y;
		s->player.pos.x += edi->decal_x;
		s->player.pos.y += edi->decal_y;
	}
}
