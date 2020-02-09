/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:17:41 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 12:05:38 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			set_selected_sprite(t_main *s, t_pos *mouse_save)
{
	int		selected;

	selected = 0;
	s->editor->selected = 1;
	mouse_save->x = s->sdl->event.button.x;
	mouse_save->y = s->sdl->event.button.y;
	s->editor->line.x1 = mouse_save->x;
	s->editor->line.y1 = mouse_save->y;
	return (selected);
}

void		deselect_sprite(t_main *s)
{
	t_sprite	*v;

	v = s->sprite;
	while (v != NULL)
	{
		if (v->selected == 1)
		{
			if (ft_is_in_sector(s, v->m_pos) == 0)
			{
				ft_create_message(s, 2, 200, "sprite must be in sector!");
				v->r_ori = v->old;
				v->r_pos = v->old;
				set_sprite(s);
			}
			v->selected = 0;
		}
		v = v->next;
	}
}

void		move_vertex(t_main *s, t_pos tmp_move, t_pos ori, int id)
{
	t_vertex	*v;

	v = s->vertex;
	tmp_move.x = arround(s->editor->space, s->sdl->event.button.x
		- (s->editor->decal_x % s->editor->space));
	tmp_move.y = arround(s->editor->space, s->sdl->event.button.y
		- (s->editor->decal_y % s->editor->space));
	tmp_move.x -= ori.x;
	tmp_move.y -= ori.y;
	tmp_move.x /= s->editor->space;
	tmp_move.y /= s->editor->space;
	while (v)
	{
		if (v->selec == 1 && v->id != id)
		{
			v->x = v->old.x + tmp_move.x;
			v->y = v->old.y + tmp_move.y;
			v->m_pos.x = v->x * METRE;
			v->m_pos.y = v->y * METRE;
		}
		if (v)
			v = v->next;
	}
}

int			is_sprite_selected(t_main *s)
{
	t_sprite	*v;

	v = s->sprite;
	while (v)
	{
		if (v->selected == 1)
			return (1);
		v = v->next;
	}
	return (0);
}

int			exist_vertex(t_main *s, t_pos *mouse_save)
{
	int		selected;

	selected = 0;
	s->editor->selected = 1;
	mouse_save->x = s->sdl->event.button.x;
	mouse_save->y = s->sdl->event.button.y;
	s->editor->line.x1 = mouse_save->x;
	s->editor->line.y1 = mouse_save->y;
	s->editor->ori.x = arround(s->editor->space, s->sdl->event.button.x
		- (s->editor->decal_x % s->editor->space));
	s->editor->ori.y = arround(s->editor->space, s->sdl->event.button.y
		- (s->editor->decal_y % s->editor->space));
	if (s->editor->ori.x >= 0 && s->editor->ori.x <= WIDTH &&
	s->editor->ori.y >= 0 && s->editor->ori.y <= HEIGHT)
	{
		if ((s->editor->id = anchor_exists(s, s->editor->ori)) != 0)
		{
			selected = 1;
			s->editor->selected = 0;
		}
	}
	return (selected);
}
