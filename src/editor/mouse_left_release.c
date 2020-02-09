/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_left_release.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 10:59:39 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 11:19:40 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline void		left_release(t_main *s)
{
	t_pos	diff;

	if (s->editor->mode == move && s->editor->selected2 == 1)
	{
		s->editor->decal_x = s->editor->tmp.x;
		s->editor->decal_y = s->editor->tmp.y;
		diff.x = s->ft_mouse.x - s->editor->mouse_save.x;
		diff.y = s->ft_mouse.y - s->editor->mouse_save.y;
		mouse_grid(s, diff);
		s->editor->selected2 = 0;
	}
	if (s->editor->mode == vertex)
	{
		if (!s->editor->id && (s->ft_mouse.x == s->editor->mouse_save.x
		|| s->ft_mouse.y == s->editor->mouse_save.y) && s->editor->remove == 0)
			create_anchor(s, s->editor->ori);
		s->editor->selected2 = 0;
		if (s->editor->selected == 0)
		{
			deselect_vertex(s);
			ft_check_move_vertex_validity(s, s->editor->id);
		}
		if (s->editor->selected == 1)
			select_vertex(s);
	}
}

void					handle_editor_mouse_release_event(t_main *s)
{
	if (s->sdl->event.button.button == SDL_BUTTON_LEFT
		&& s->display_mode == editor)
	{
		if (s->editor->mode == move || s->editor->mode == vertex)
			left_release(s);
		else if (s->editor->mode == sprite && !s->editor->select_sprite)
		{
			if (!is_sprite_selected(s) && !is_sprite_under_mouse(s)
			&& s->editor->selected2 == 0)
				create_new_sprite(s, none,
				get_abs_r_pos(s, s->ft_mouse), s->sprite);
			else if (is_sprite_selected(s))
			{
				deselect_sprite(s);
				s->editor->selected2 = 0;
			}
		}
		s->editor->remove = 0;
	}
	else if (s->sdl->event.button.button == SDL_BUTTON_RIGHT)
	{
		if (s->editor->mode == portal)
			remove_portal(s);
	}
}
