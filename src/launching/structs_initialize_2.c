/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_initialize_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:18:01 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 14:46:36 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_pos		get_subline_coord(t_main *s, t_name value)
{
	t_pos	new;
	t_name	name;

	new.x = WIDTH * 0.5 - s->editor->sprite_menu.image[0]->w * 0.5 + 205;
	new.y = 0;
	name = 0;
	if (value < table)
		name = storm;
	else if (value < o_gun)
		name = table;
	else if (value <= big_s_ammo)
		name = o_gun;
	while (name < value)
	{
		if (new.y < s->editor->m_sprite_pos[name].y)
			new.y = s->editor->m_sprite_pos[name].y;
		name++;
	}
	return (new);
}

void		fill_sprite_list_value(t_main *s, t_editor *edi)
{
	t_name	name;
	t_pos	coord;
	t_pos	end;

	coord.x = WIDTH * 0.5 - edi->sprite_menu.image[0]->w * 0.5 + 205;
	coord.y = HEIGHT * 0.5 - edi->sprite_menu.image[0]->h * 0.5 + 5;
	end.x = coord.x + edi->sprite_menu.image[0]->w;
	end.y = coord.y + edi->sprite_menu.image[0]->h;
	name = storm;
	while (name <= big_s_ammo)
	{
		if (name == storm || name == table || name == o_gun)
		{
			coord.x = WIDTH * 0.5 - edi->sprite_menu.image[0]->w * 0.5 + 205;
			coord.y = HEIGHT * 0.5 - edi->sprite_menu.image[0]->h * 0.5 + 5;
		}
		if (coord.x + edi->all_sprite.image[name]->w < end.x)
			edi->m_sprite_pos[name] = coord;
		else
			edi->m_sprite_pos[name] = get_subline_coord(s, name);
		coord.x += edi->all_sprite.image[name]->w + 5;
		name++;
	}
}

void		load_editor_menu(t_main *s)
{
	ft_bzero((void **)&s->editor->menu, sizeof(t_anim));
	s->editor->menu.image[0] = load_tga("images/move.tga", 0, 0, 0);
	s->editor->menu.image[1] = load_tga("images/vertex.tga", 0, 0, 0);
	s->editor->menu.image[2] = load_tga("images/sector.tga", 0, 0, 0);
	s->editor->menu.image[3] = load_tga("images/player.tga", 0, 0, 0);
	s->editor->menu.image[4] = load_tga("images/portal.tga", 0, 0, 0);
	s->editor->menu.image[5] = load_tga("images/sprite.tga", 0, 0, 0);
	s->editor->menu.image[6] = load_tga("images/save.tga", 0, 0, 0);
	s->editor->sprite_menu.image[0] =
	load_tga("images/ressources/sprite_menu/sprite_01.tga", 0, 0, 0);
	s->editor->sprite_menu.image[1] =
	load_tga("images/ressources/sprite_menu/sprite_02.tga", 0, 0, 0);
	s->editor->sprite_menu.image[2] =
	load_tga("images/ressources/sprite_menu/sprite_03.tga", 0, 0, 0);
}

void		load_images(t_main *s)
{
	load_editor_menu(s);
	s->editor->sprite_menu.current = 0;
	s->editor->m_floor.image[0] = load_tga("images/stage.tga", 0, 0, 0);
	s->editor->m_floor.image[1] = load_tga("images/s_enabled.tga", 0, 0, 0);
	ft_bzero((void **)&s->menu, sizeof(t_anim));
	s->menu.image[0] = load_tga("images/menu.tga", 0, 0, 0);
	s->menu.image[1] = load_tga("images/play.tga", 0, 0, 0);
	s->menu.image[2] = load_tga("images/editor.tga", 0, 0, 0);
	s->menu.current = 0;
	s->savemap->croix_rouge = load_tga("images/croix_rouge.tga", 0, 0, 0);
	s->player.hud = load_tga("images/hud_doom.tga", 0, 0, 0);
	s->player.crosshair = load_tga("images/crosshair.tga", 0, 0, 0);
	load_anims(s);
	fill_sprite_list(s);
	fill_sprite_list_value(s, s->editor);
	fill_texture_list(s);
	s->skybox.current = 0;
	s->editor->menu.current = 0;
	s->editor->m_floor.current = 0;
}

t_texture	*initialize_texture(t_sdl *sdl, int width, int height)
{
	t_texture	*text;

	if (!(text = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	if (!(text->content = (Uint32 *)malloc(width * height * sizeof(Uint32))))
		return (NULL);
	if (!(text->texture = SDL_CreateTexture(sdl->prenderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)))
		return (NULL);
	text->color_tmp = 0xFFFFFFFF;
	return (text);
}
