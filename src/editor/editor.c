/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:58:17 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 15:59:56 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_image(t_texture *texture, t_pos ori, t_pos dest, t_image *image)
{
	t_pos		coord;
	double		pery;
	double		perx;
	int			pix_tex;

	coord.x = ori.x;
	while (coord.x < dest.x)
	{
		coord.y = ori.y;
		perx = percent(coord.x - ori.x, dest.x - ori.x);
		while (coord.y < dest.y)
		{
			coord.y++;
			pery = percent(coord.y - ori.y, dest.y - ori.y);
			pix_tex = (int)(pery * image->h - 1) * image->w +
				(int)(perx * image->w);
			set_pixel(texture, image->tex[pix_tex], coord);
		}
		coord.x++;
	}
}

void	draw_space_menu(t_main *s)
{
	t_pos ori;
	t_pos dest;

	ori.x = WIDTH * 0.5 + (s->editor->menu.image[0]->w * 0.5) + 1;
	ori.y = -1;
	dest.x = ori.x + s->editor->m_floor.image[0]->w;
	dest.y = ori.y + s->editor->m_floor.image[0]->h + 1;
	draw_image(s->sdl->editor, ori, dest,
			s->editor->m_floor.image[s->editor->m_floor.current]);
}

void	draw_editor_menu(t_main *s, double perx, short orig_x, short orig_y)
{
	t_pos		coord;
	t_pos		dest;
	double		pery;
	int			pix_tex;
	t_image		*menu;

	menu = s->editor->menu.image[s->editor->menu.current];
	dest.x = WIDTH * 0.5 + (menu->w * 0.5) + 1;
	dest.y = menu->h;
	coord.x = orig_x;
	while (coord.x < dest.x)
	{
		coord.y = orig_y;
		perx = percent(coord.x - orig_x, dest.x - orig_x);
		while (coord.y < dest.y)
		{
			coord.y++;
			pery = percent(coord.y - orig_y, dest.y - orig_y);
			pix_tex = (int)(pery * menu->h - 1) * menu->w +
				(int)(perx * menu->w);
			set_pixel(s->sdl->editor, menu->tex[pix_tex], coord);
		}
		coord.x++;
	}
}
