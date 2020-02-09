/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_left_click.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 10:35:42 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 10:53:29 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_left_click_1(t_main *s)
{
	if (check_click_menu(s))
		click_editor_menu(s, s->editor->menu, s->ft_mouse.x);
	else if (s->editor->mode == sprite)
	{
		if (!is_sprite_selected(s) && !s->editor->select_sprite)
			s->editor->selected2 = select_sprite(s);
		else if (!is_sprite_selected(s) && s->editor->select_sprite)
			select_sprite_type(s);
	}
	else if (s->editor->mode == portal)
		edit_portal(s);
	else if (s->editor->mode == vertex)
	{
		s->editor->selected2 = exist_vertex(s, &s->editor->mouse_save);
		s->save_coord_vtx.x = s->editor->ori.x;
		s->save_coord_vtx.y = s->editor->ori.y;
	}
}

void	check_left_click_2(t_main *s)
{
	if (s->editor->mode == move)
	{
		s->editor->tmp.x = s->editor->decal_x;
		s->editor->tmp.y = s->editor->decal_y;
		s->editor->mouse_save.x = s->sdl->event.button.x;
		s->editor->mouse_save.y = s->sdl->event.button.y;
		s->editor->selected2 = 1;
	}
	else if (s->editor->mode == sector)
	{
		s->editor->ori.x = arround(s->editor->space,
			s->sdl->event.button.x -
			(s->editor->decal_x % s->editor->space));
		s->editor->ori.y = arround(s->editor->space,
			s->sdl->event.button.y -
			(s->editor->decal_y % s->editor->space));
		if (s->editor->ori.x >= 0 && s->editor->ori.x <= WIDTH
			&& s->editor->ori.y >= 0 && s->editor->ori.y <= HEIGHT)
		{
			if ((s->editor->id = anchor_exists(s, s->editor->ori)) != 0)
				set_selected(s, s->editor->ori, s->editor->color_sector);
		}
		s->editor->color_sector = ft_sector_mode(s,
		s->sdl->event.button.x, s->sdl->event.button.y);
	}
}

void	check_left_click_3(t_main *s)
{
	if (s->editor->mode == player)
	{
		s->editor->tmp2 = get_abs_r_pos(s, s->ft_mouse);
		s->editor->tmp2.x *= METRE;
		s->editor->tmp2.y *= METRE;
		if (ft_is_in_sector(s, s->editor->tmp2) != 0)
		{
			s->player.r_ori.x = s->editor->tmp2.x / METRE;
			s->player.r_ori.y = s->editor->tmp2.y / METRE;
			s->player.r_pos = s->player.r_ori;
			s->player.set = 1;
			s->player.correc = 0;
			s->player.m_pos = s->editor->tmp2;
			s->editor->tmp_floor =
			get_sector_by_id(s, s->player.sector_id)->floor;
			s->player.sector_id = ft_is_in_sector(s, s->player.m_pos);
			s->player.foot_height =
			get_sector_by_id(s, s->player.sector_id)->floor;
			if (s->editor->tmp_floor > s->player.foot_height)
				s->player.jump_height =
				s->editor->tmp_floor - s->player.foot_height;
			s->player.jump = 3;
		}
	}
}

void	handle_editor_mouse_pressed_event(t_main *s)
{
	if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
	{
		if (s->display_mode == editor && (s->editor->mode == sprite
			|| s->editor->mode == sprite || s->editor->mode == portal
			|| s->editor->mode == vertex))
			check_left_click_1(s);
		else if (s->display_mode == editor && (s->editor->mode == move
			|| s->editor->mode == sector))
			check_left_click_2(s);
		else if (s->display_mode == editor && s->editor->mode == player)
			check_left_click_3(s);
		else if (s->display_mode == game)
			shoot(s);
		else if (s->display_mode == save)
			ft_click_save(s);
	}
	else if (s->sdl->event.button.button == SDL_BUTTON_RIGHT)
	{
		if (s->editor->mode == sprite && !s->editor->select_sprite)
			s->editor->select_sprite = 1;
		else if (s->editor->mode == sprite
			&& s->editor->select_sprite)
			s->editor->select_sprite = 0;
	}
}
