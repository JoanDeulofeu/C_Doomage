/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_sprite3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:52:24 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 13:53:19 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		display_sprite_menu(t_main *s, int i, int j, int px)
{
	double		perx;
	t_pos		coord;
	t_pos		ori;
	t_anim		m;

	m = s->editor->sprite_menu;
	coord.x = WIDTH * 0.5 - m.image[0]->w * 0.5;
	coord.y = HEIGHT * 0.5 - m.image[0]->h * 0.5;
	ori = coord;
	while (++i < m.image[0]->w)
	{
		j = -1;
		coord.x = ori.x + i;
		perx = (double)i / (double)m.image[0]->w;
		while (++j < m.image[0]->h)
		{
			coord.y = ori.y + j;
			px = (int)(((double)j / (double)m.image[0]->h)
			* (double)m.image[m.current]->h) * m.image[m.current]->w
			+ (int)(perx * (double)m.image[m.current]->w);
			if (px >= 0 && px < m.image[m.current]->w * m.image[m.current]->h)
				set_pixel(s->sdl->editor, m.image[m.current]->tex[px], coord);
		}
	}
	draw_sprite_list(s);
}

void		select_sprite_in_menu2(t_main *s, t_name *name, t_name *max_name)
{
	if (s->editor->sprite_menu.current == 0)
	{
		*name = storm;
		*max_name = storm;
	}
	else if (s->editor->sprite_menu.current == 1)
	{
		*name = table;
		*max_name = lamp;
	}
	else
	{
		*name = o_gun;
		*max_name = big_s_ammo;
	}
}

void		select_sprite_in_menu(t_main *s)
{
	t_name	name;
	t_name	max_name;
	t_pos	pos;
	t_image *img;

	select_sprite_in_menu2(s, &name, &max_name);
	while (name <= max_name)
	{
		pos = s->editor->m_sprite_pos[name];
		img = s->editor->all_sprite.image[name];
		if (s->ft_mouse.x > pos.x && s->ft_mouse.x < pos.x + img->w
			&& s->ft_mouse.y > pos.y && s->ft_mouse.y < pos.y + img->h)
		{
			s->editor->sprite_selected = name;
			break ;
		}
		name++;
	}
}

void		draw_sprites_ori(t_main *s)
{
	t_sprite	*tmp;
	t_dpos		pos;
	Uint32		color;

	tmp = s->sprite;
	while (tmp)
	{
		if (tmp->type == enemy)
			color = YELLOW;
		else if (tmp->type == obstacle)
			color = S_RED;
		else
			color = S_PINK;
		pos.x = tmp->r_ori.x * METRE;
		pos.y = tmp->r_ori.y * METRE;
		draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, pos)), color);
		tmp = tmp->next;
	}
}

void		add_sprite_to_sector(t_main *s, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*tmp;
	t_lsprite	*liste;

	sct = get_sector_by_id(s, sprite->sct_id);
	if ((liste = malloc(sizeof(t_lsprite))) == NULL)
		handle_error(s, MALLOC_ERROR);
	liste->sprite = sprite;
	liste->next = NULL;
	if (sct->liste == NULL)
		sct->liste = liste;
	else
	{
		tmp = sct->liste;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = liste;
	}
}
