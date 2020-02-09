/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:21:15 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 11:56:19 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		handle_editor_keys(t_main *s)
{
	handle_global_keys(s);
	if (s->display_mode == editor)
		handle_editor_mode_keys(s);
	if (s->display_mode == game)
		handle_game_mode_keys(s);
	if (s->display_mode == save)
	{
		ft_reset_color_screen(s->sdl->save->content, WIDTH * HEIGHT);
		ft_save_map(s);
		update_image(s, s->sdl->save);
	}
}

void		handle_editor_mouse_wheel_event(t_main *s)
{
	if (s->sdl->event.wheel.y > 0 && s->editor->zoom < 15 && !s->display_mode)
	{
		ft_zoom(s, 5);
		s->editor->zoom++;
	}
	else if (s->sdl->event.wheel.y < 0 && s->editor->zoom > -3 &&
		!s->display_mode)
	{
		ft_zoom(s, -5);
		s->editor->zoom--;
	}
	if (s->display_mode == game)
	{
		if (s->sdl->event.wheel.y > 0)
			change_wall_texture(s, 1);
		else
			change_wall_texture(s, 0);
	}
}

int			handle_editor_keyboard_event(t_main *s)
{
	int		remove_achr;

	if (s->display_mode == editor)
	{
		if ((remove_achr = key_controls_edi(s,
			s->sdl->event.key.keysym.sym)) == 0)
			return (0);
		else if (remove_achr == 2 && s->editor->selected2 == 1)
		{
			remove_anchor(s, s->editor->id);
			s->editor->remove = 1;
			s->editor->id = 0;
		}
	}
	else if (s->display_mode == game)
	{
		if (key_controls_game(s, s->sdl->event.key.keysym.sym) == 0)
			return (0);
	}
	else if (s->display_mode == save)
		key_controls_save(s, s->sdl->event.key.keysym.sym);
	return (1);
}

void		poll_event_out(t_main *s)
{
	if (s->display_mode == editor && s->editor->mode == sprite)
		move_sprite(s);
	handle_editor_keys(s);
	if (s->editor->tmp_mode != s->editor->mode)
		deselect_vertex(s);
	s->wall_fk_id = 0;
}

void		editor_handler(t_main *s, int ingame)
{
	s->play_or_editor = 1;
	while (ingame)
	{
		s->editor->tmp_mode = s->editor->mode;
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			if (s->sdl->event.type == SDL_MOUSEMOTION)
				handle_editor_mouse_move_event(s, s->editor);
			if (s->sdl->event.type == SDL_QUIT)
				ingame = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONUP)
				handle_editor_mouse_release_event(s);
			if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN)
				handle_editor_mouse_pressed_event(s);
			if (s->sdl->event.type == SDL_MOUSEWHEEL)
				handle_editor_mouse_wheel_event(s);
			if (s->sdl->event.type == SDL_KEYDOWN)
			{
				if (!handle_editor_keyboard_event(s))
					ingame = 0;
			}
		}
		poll_event_out(s);
	}
}
