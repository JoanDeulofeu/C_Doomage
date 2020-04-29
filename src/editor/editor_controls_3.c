/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_controls_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 11:51:52 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 14:06:37 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		key_controls_edi_2(t_main *s, int key)
{
	if (key == FLOOR)
	{
		if (s->editor->mode_floor == 1)
			s->editor->mode_floor = 0;
		else
			s->editor->mode_floor = 1;
	}
	if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER ||
		key == PORTAL || key == SPRITE)
		change_mode(s, key);
	if (s->display_mode == editor)
	{
		if (s->editor->mode == vertex && (key == DELETE))
			remove_selected_anchor(s);
		if (s->editor->mode == sprite && (key == DELETE))
			remove_selected_sprite(s);
	}
}

int			key_controls_edi(t_main *s, int key)
{
	if (key == SDLK_ESCAPE)
		return (0);
	if (key == SDLK_KP_PLUS)
		s->printf = s->printf ? 0 : 1;
	if ((key == SDLK_RETURN || key == SDLK_KP_ENTER) && s->display_mode < 2)
		s->display_mode = s->display_mode == 1 ? 0 : 1;
	if (s->editor->mode_floor == 1)
	{
		if (key == SDLK_KP_PLUS)
			s->editor->dply_floor = ft_prev_next_floor(s, 1);
		if (key == SDLK_KP_MINUS)
			s->editor->dply_floor = ft_prev_next_floor(s, 2);
	}
	if (key == SAVE)
		s->display_mode = save;
	key_controls_edi_2(s, key);
	if (key == DELETE)
		return (2);
	return (1);
}

void		handle_editor_mode_keys(t_main *s)
{
	ft_reset_color_screen(s->sdl->editor->content, WIDTH * HEIGHT);
	ft_draw_editor(s->editor, s->sdl->editor);
	display_map(s);
	draw_sprites_ori(s);
	ft_draw_all_wall(s);
	if (s->editor->mode_floor == 1)
		s->editor->m_floor.current = 1;
	else
		s->editor->m_floor.current = 0;
	if (s->editor->mode == portal)
		change_over_wall(s);
	draw_editor_menu(s, 0, WIDTH * 0.5
		- (s->editor->menu.image[s->editor->menu.current]->w * 0.5), -1);
	draw_space_menu(s);
	handle_sector_zero(s);
	unset_sprites(s);
	ft_visu_joan(s);
	clear_wall_list(s);
	if (s->editor->select_sprite)
		display_sprite_menu(s, -1, 0, 0);
	update_image(s, s->sdl->editor);
}

void		handle_global_keys(t_main *s)
{
	const Uint8	*keys;

	s->player.sector_id = ft_is_in_sector(s, s->player.m_pos);
	keys = SDL_GetKeyboardState(NULL);
	if ((keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN] || keys[SPRINT])
		&& (s->player.sector_id != 0))
		ft_move_player(s, keys, PLAYER_SPEED);
	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
		rotate_player(s, keys);
	if (s->editor->mode == move && (keys[RIGHT_AR] || keys[LEFT_AR] ||
		keys[UP_AR] || keys[DOWN_AR]))
		move_editor(s, keys);
	if (s->player.jump == 0 && !s->player.fly)
		ft_crouch(s, keys);
	if (!s->player.fly)
		ft_jump(s, keys);
	if (s->transition)
		ft_transition(s);
	if (keys[SDL_SCANCODE_F5])
		ft_activ_fly(s);
	if (s->player.fly)
		ft_fly_mode(s, keys);
}

void		handle_game_mode_keys(t_main *s)
{
	display_sky(s, 0, 0);
	set_player(s);
	handle_sector_zero(s);
	unset_sprites(s);
	ft_visu_joan(s);
	clear_wall_list(s);
	animate_weapon(s);
	update_image(s, s->sdl->game);
}
