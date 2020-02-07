/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_sprite2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:50:36 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 13:51:01 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	select_sprite_type(t_main *s)
{
	t_image	*img;
	t_pos	begin;
	t_pos	end;

	img = s->editor->sprite_menu.image[0];
	begin.x = WIDTH * 0.5 - img->w * 0.5;
	begin.y = HEIGHT * 0.5 - img->h * 0.5;
	end.x = begin.x + img->w;
	end.y = begin.y + img->h;
	if (s->ft_mouse.x >= begin.x && s->ft_mouse.x <= begin.x + 200)
	{
		if (s->ft_mouse.y >= begin.y && s->ft_mouse.y <= begin.y + 60)
			s->editor->sprite_menu.current = 0;
		else if (s->ft_mouse.y > 60 && s->ft_mouse.y <= begin.y + 120)
			s->editor->sprite_menu.current = 1;
		else if (s->ft_mouse.y > 120 && s->ft_mouse.y <= begin.y + 180)
			s->editor->sprite_menu.current = 2;
	}
	if (s->ft_mouse.x > begin.x + 200 && s->ft_mouse.x < end.x
		&& s->ft_mouse.y > begin.y && s->ft_mouse.y < end.y)
		select_sprite_in_menu(s);
}

void	draw_plain_sprite(int i, t_pos coord, t_image *img, t_texture *tex)
{
	double		perx;
	double		pery;
	t_pos		ori;
	int			px;
	int			j;

	ori = coord;
	while (i < img->w)
	{
		j = 0;
		coord.x = ori.x + i;
		perx = (double)i / (double)img->w;
		while (j < img->h)
		{
			coord.y = ori.y + j;
			pery = (double)j / (double)img->h;
			px = (int)(pery * (double)img->h) * img->w +
			(int)(perx * (double)img->w);
			if (px >= 0 && px < img->w * img->h)
				set_pixel(tex, img->tex[px], coord);
			j++;
		}
		i++;
	}
}

void	draw_selected_feedback(t_main *s, t_name name, t_pos pos)
{
	t_dpos	ori;
	t_dpos	dest;

	ori.x = pos.x - 5;
	ori.y = pos.y - 5;
	dest.x = pos.x + s->editor->all_sprite.image[name]->w + 5;
	dest.y = pos.y + s->editor->all_sprite.image[name]->h + 5;
	draw_rect(s->sdl->editor, ori, dest, GREEN);
}

void	draw_sprite_list2(t_main *s, int part, t_name name)
{
	if (part == 1)
	{
		name = table;
		while (name <= lamp)
		{
			if (s->editor->sprite_selected == name)
				draw_selected_feedback(s, name, s->editor->m_sprite_pos[name]);
			draw_plain_sprite(0, s->editor->m_sprite_pos[name],
				s->editor->all_sprite.image[name], s->sdl->editor);
			name++;
		}
	}
	if (part == 2)
	{
		name = o_gun;
		while (name <= big_s_ammo)
		{
			if (s->editor->sprite_selected == name)
				draw_selected_feedback(s, name, s->editor->m_sprite_pos[name]);
			draw_plain_sprite(0, s->editor->m_sprite_pos[name],
				s->editor->all_sprite.image[name], s->sdl->editor);
			name++;
		}
	}
}

void	draw_sprite_list(t_main *s)
{
	t_name	name;

	name = storm;
	if (s->editor->sprite_menu.current == 0)
	{
		name = storm;
		while (name < table)
		{
			if (s->editor->sprite_selected == name)
				draw_selected_feedback(s, name, s->editor->m_sprite_pos[name]);
			draw_plain_sprite(0, s->editor->m_sprite_pos[name],
				s->editor->all_sprite.image[name], s->sdl->editor);
			name++;
		}
	}
	else if (s->editor->sprite_menu.current == 1)
		draw_sprite_list2(s, 1, name);
	else if (s->editor->sprite_menu.current == 2)
		draw_sprite_list2(s, 2, name);
}
