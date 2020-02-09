/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_controls_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 11:50:29 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 11:57:23 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		click_editor_menu(t_main *s, t_anim menu, int x, int ori_x)
{
	int		case_size;

	ori_x = WIDTH * 0.5 - (s->editor->menu.image[s->editor->menu.current]->w
		* 0.5);
	case_size = menu.image[0]->w / 7;
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
	ori_x = WIDTH * 0.5 -
	(s->editor->menu.image[s->editor->menu.current]->w * 0.5);
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
