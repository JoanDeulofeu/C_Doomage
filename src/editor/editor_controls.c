/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:21:15 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 10:46:39 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		click_editor_menu(t_main *s, t_anim menu, int x)
{
	int		case_size;
	int		ori_x;

	ori_x = WIDTH* 0.5 - (s->editor->menu.image[s->editor->menu.current]->w* 0.5);
	case_size = menu.image[0]->w / 7;
	if (s->display_mode)
		return ;
	if (x < ori_x + case_size)
		change_mode(s, MOVE);
	else if (x < ori_x + (case_size * 2) && x > ori_x + case_size)
		change_mode(s, VERTEX);
	else if (x < ori_x + (case_size * 3) && x > ori_x + (case_size * 2))
		change_mode(s, WALL);
	else if (x < ori_x + (case_size * 4) && x > ori_x + (case_size * 3))
		change_mode(s, PLAYER);
	else if (x < ori_x + (case_size * 5) && x > ori_x + (case_size * 4))
		change_mode(s, PORTAL);
	else if (x < ori_x + (case_size * 6) && x > ori_x + (case_size * 5))
		change_mode(s, SPRITE);
	else if (x < ori_x + (case_size * 7) && x > ori_x + (case_size * 5))
		change_mode(s, SAVE);
	else if (x < ori_x + (case_size * 8) && x > ori_x + (case_size * 6)
		&& s->editor->mode_floor == 0)
		s->editor->mode_floor = 1;
	else if (x < ori_x + (case_size * 8) && x > ori_x + (case_size * 7)
		&& s->editor->mode_floor != 0)
		s->editor->mode_floor = 0;
}

int			check_click_menu(t_main *s)
{
	int		x;
	int		y;
	int		ori_x;
	int		dest_x;
	int		case_size;

	x = s->ft_mouse.x;
	y = s->ft_mouse.y;
	case_size = s->editor->menu.image[0]->w / 7;
	ori_x = WIDTH* 0.5 - (s->editor->menu.image[s->editor->menu.current]->w* 0.5);
	dest_x = ori_x + s->editor->menu.image[s->editor->menu.current]->w;
	if (x >= ori_x && y >= 0 && x < dest_x + case_size && y <
		s->editor->menu.image[s->editor->menu.current]->h)
		return (1);
	else
		return (0);
}

int			key_controls_save(t_main *s, int key)
{
	if (key == SDLK_ESCAPE)
	{
		s->display_mode = 0;
		change_mode(s, MOVE);
	}
	if ((key >= SDLK_a && key <= SDLK_z) || key == MINUS || key == 32)
	{
		ft_add_letter_to_savemap(s, key);
	}
	if (key == DEL)
	{
		ft_del_letter_to_savemap(s);
	}
	if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
	{
		if (s->savemap->str[2] == '\0')
			ft_save_msg(s, 1);
		else
			ft_write_file(s);
	}
	return (1);
}

void		ft_change_height(t_main *s, int key)
{
	t_sector *sct;

	sct = get_sector_by_id(s, s->player.sector_id);
	if (key == PAGE_DOWN && sct->floor > 0)
	{
		sct->floor--;
		ft_create_message(s, 0, 1000, "Floor down");
	}
	else if (key == END && sct->ceiling > 0 && sct->ceiling > sct->floor + 1)
	{
		sct->ceiling--;
		ft_create_message(s, 0, 1000, "Ceiling down");
	}
	else if (key == PAGE_UP && sct->floor < 10 && sct->ceiling > sct->floor + 1)
	{
		sct->floor++;
		ft_create_message(s, 0, 1000, "Floor up");
	}
	else if (key == HOME && sct->ceiling < 10)
	{
		sct->ceiling++;
		ft_create_message(s, 0, 1000, "Ceiling up");
	}
}

int			key_controls_game(t_main *s, int key)
{
	if (key == SDLK_ESCAPE)
		return (0);
	if ((!s->player.fly) && (key == HOME || key == END
		|| key == PAGE_UP || key == PAGE_DOWN))
		ft_change_height(s, key);
	if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
		s->display_mode = s->display_mode == 1 ? 0 : 1;
	if (key == SDLK_KP_PLUS)
		{
			s->transition++;
			s->transition_y_eye = s->player.y_eye;
			if (s->player.angle < 0)
				s->player.angle += 360;
			s->transition_angle = (int)s->player.angle % 360;
		}
	return (1);
}

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
	if (key == TAB)
		ft_test_chainlist(s);
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
		return(2);
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
	draw_editor_menu(s, 0, WIDTH* 0.5
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

	if (s->player.jump_height == 0 && !s->player.fly)
		ft_crouch(s, keys);
	if (s->player.size == PLAYER_SIZE && !s->player.fly)
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
	display_sky(s, 0, 0, 0);
	set_player(s);
	handle_sector_zero(s);
	unset_sprites(s);
	ft_visu_joan(s);
	clear_wall_list(s);
	animate_weapon(s);
	update_image(s, s->sdl->game);
}

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

void		handle_editor_mouse_move_event(t_main *s)
{
	s->ft_mouse.x = s->sdl->event.motion.x;
	s->ft_mouse.y = s->sdl->event.motion.y;
	if (s->editor->mode == vertex || s->editor->mode == sprite)
	{
		s->editor->line.x2 = s->sdl->event.motion.x;
		s->editor->line.y2 = s->sdl->event.motion.y;
	}
	if (s->editor->selected2 && s->editor->mode == vertex && !s->display_mode)
	{
		move_anchor(s, s->editor->id);
		move_vertex(s, s->editor->tmp_move, s->editor->ori, s->editor->id);
	}
	if(s->display_mode == game)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		rotate_mouse(s);
		s->editor->mode = move;
	}
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (s->editor->mode == portal &&
		get_pixel_color(s->sdl->editor, s->ft_mouse.x,
			s->ft_mouse.y) == BLACK_SCREEN)
	{
		s->editor->over_portal = 0;
		s->editor->over_sector2 = 0;
		if (s->editor->portal_temp == 1)
		{
			if (s->editor->wall2)
				s->editor->wall2->selected = 0;
			s->editor->wall2 = NULL;
		}
		else if (s->editor->portal_temp == 0)
		{
			if (s->editor->wall && !s->editor->wall2)
			{
				s->editor->wall->selected = 0;
				s->editor->wall = NULL;
			}
			else
				s->editor->over_sector = 0;
		}
	}
	if (s->editor->mode == move && s->editor->selected2 == 1)
	{
		s->player.pos.x -= s->editor->decal_x;
		s->player.pos.y -= s->editor->decal_y;
		s->editor->decal_x = s->editor->tmp.x + s->ft_mouse.x - s->editor->mouse_save.x;
		s->editor->decal_y = s->editor->tmp.y + s->ft_mouse.y - s->editor->mouse_save.y;
		s->player.pos.x += s->editor->decal_x;
		s->player.pos.y += s->editor->decal_y;
	}
}

void		handle_editor_mouse_release_event(t_main *s)
{
	t_pos	diff;

	if (s->sdl->event.button.button == SDL_BUTTON_LEFT && s->display_mode == editor)
	{
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
			if (!s->editor->id && s->editor->mode == vertex
				&& (s->ft_mouse.x == s->editor->mouse_save.x || s->ft_mouse.y
					== s->editor->mouse_save.y) && s->editor->remove == 0)
			{
				create_anchor(s, s->editor->ori);
			}
			s->editor->selected2 = 0;
			if (s->editor->selected == 0)
			{
				deselect_vertex(s);
				ft_check_move_vertex_validity(s, s->editor->id);
			}
			if (s->editor->selected == 1)
			{
				select_vertex(s);
			}
		}
		else if (s->editor->mode == sprite && !s->editor->select_sprite)
		{
			if (!is_sprite_selected(s) && !is_sprite_under_mouse(s) && s->editor->selected2 == 0)
			{
				create_new_sprite(s, none, get_abs_r_pos(s, s->ft_mouse), s->sprite);
			}
			else if (is_sprite_selected(s))
			{
				deselect_sprite(s);
				s->editor->selected2 = 0;
			}
		}
		else if (s->editor->mode == move)
		{
			s->editor->selected2 = 0;
		}
		s->editor->remove = 0;
	}
	else if(s->sdl->event.button.button == SDL_BUTTON_RIGHT)
	{
		if (s->editor->mode == portal)
			remove_portal(s);
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
				handle_editor_mouse_move_event(s);
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
