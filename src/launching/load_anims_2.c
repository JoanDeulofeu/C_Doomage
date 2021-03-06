/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_anims_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:52:44 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/10 10:35:29 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_sprite_list(t_main *s)
{
	ft_bzero((void *)&s->editor->all_sprite, sizeof(t_anim));
	s->editor->all_sprite.image[storm] = s->stormtrooper.face.image[0];
	s->editor->all_sprite.image[table] = s->items.table.image[0];
	s->editor->all_sprite.image[lamp] = s->items.lamp.image[0];
	s->editor->all_sprite.image[o_gun] = s->items.gun.image[0];
	s->editor->all_sprite.image[o_shotgun] = s->items.shotgun.image[0];
	s->editor->all_sprite.image[big_g_ammo] = s->items.big_g_ammo.image[0];
	s->editor->all_sprite.image[big_s_ammo] = s->items.big_s_ammo.image[0];
	s->editor->all_sprite.image[jetpack] = s->items.jetpack.image[0];
	s->editor->all_sprite.image[bomb] = s->items.bomb.image[0];
}

void	fill_texture_list(t_main *s)
{
	t_editor *edi;

	edi = s->editor;
	ft_bzero((void *)&s->editor->all_texture, sizeof(t_anim));
	edi->all_texture.image[0] = load_tga(s, "images/textures/02.tga");
	edi->all_texture.image[1] = load_tga(s, "images/textures/01.tga");
	edi->all_texture.image[2] = load_tga(s, "images/textures/03.tga");
	edi->all_texture.image[3] = load_tga(s, "images/textures/04.tga");
	edi->all_texture.image[4] = load_tga(s, "images/textures/05.tga");
	edi->all_texture.image[5] = load_tga(s, "images/textures/06.tga");
	edi->all_texture.image[6] = load_tga(s, "images/textures/07.tga");
	edi->all_texture.image[7] = load_tga(s, "images/textures/08.tga");
	edi->all_texture.image[8] = load_tga(s, "images/textures/09.tga");
	edi->all_texture.image[9] = load_tga(s, "images/textures/10.tga");
	edi->all_texture.image[10] = load_tga(s, "images/textures/11.tga");
	edi->all_texture.image[11] = load_tga(s, "images/textures/12.tga");
}
