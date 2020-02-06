/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:58:09 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 16:38:55 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	change_mode_2(t_main *s, int key)
{
	if (key == PLAYER)
	{
		s->editor->mode = player;
		s->editor->menu.current = 3;
		ft_reset_color_vertex(s);
	}
	else if (key == PORTAL)
	{
		s->editor->mode = portal;
		s->editor->menu.current = 4;
		ft_reset_color_vertex(s);
	}
	else if (key == SAVE)
	{
		s->editor->mode = save_edi;
		s->editor->menu.current = 6;
		ft_reset_color_vertex(s);
		s->display_mode = 2;
	}
	else if (key == SPRITE)
	{
		s->editor->mode = sprite;
		s->editor->menu.current = 5;
		ft_reset_color_vertex(s);
	}
}

void	change_mode(t_main *s, int key)
{
	if (key == MOVE)
	{
		s->editor->mode = move;
		s->editor->menu.current = 0;
		ft_reset_color_vertex(s);
	}
	else if (key == WALL)
	{
		s->editor->mode = sector;
		s->editor->menu.current = 2;
		s->editor->color_sector = 2;
		ft_reset_color_vertex(s);
		ft_memdel((void **)&s->str_vtx);
	}
	else if (key == VERTEX)
	{
		s->editor->mode = vertex;
		s->editor->menu.current = 1;
		ft_reset_color_vertex(s);
	}
	else
		change_mode_2(s, key);
	reset_temp_portals(s);
}

int		ft_find_ref(t_editor *edi, int decal)
{
	if (decal >= 0 && decal < edi->space)
		return (0);
	else if (decal > 0)
		return ((decal / edi->space) * -1);
	else if (decal < 0)
	{
		if (decal % edi->space == 0)
			return ((decal / (edi->space)) * -1);
		else
			return ((decal / (edi->space) - 1) * -1);
	}
	return (0);
}

void	ft_draw_editor(t_editor *edi, t_texture *tex)
{
	t_pos	coord;
	Uint32	color;

	color = 0xaca7a7FF;
	coord.x = edi->decal_x % edi->space;
	coord.y = edi->decal_y % edi->space;
	edi->ref.x = ft_find_ref(edi, edi->decal_x);
	edi->ref.y = ft_find_ref(edi, edi->decal_y);
	if (coord.y < 0)
		coord.y += edi->space;
	while (coord.y < HEIGHT)
	{
		if (coord.x < 0)
			coord.x += edi->space;
		while (coord.x < WIDTH)
		{
			set_pixel(tex, color, coord);
			coord.x += edi->space;
		}
		coord.x = edi->decal_x % edi->space;
		coord.y += edi->space;
	}
}

void	draw_wall(t_main *s, t_pos ori)
{
	s->line.x1 = ori.x;
	s->line.y1 = ori.y;
	get_line(s, WHITE);
}
