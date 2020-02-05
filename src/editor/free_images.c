/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:21:43 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/05 16:22:57 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_image(t_image *img)
{
	if (!img)
		return ;
	ft_memdel((void **)&img->tex);
	ft_memdel((void **)&img);
}

void	free_anim(t_anim anim)
{
	int	i;

	if (!anim.image[0] && anim.image[1])
		i = 0;
	else
		i = -1;
	while (anim.image[++i] != NULL)
		free_image(anim.image[i]);
}

void	free_sprite(t_main *s)
{
	t_sprite	*sprite;
	t_sprite	*tmp;

	sprite = s->sprite;
	while (sprite != NULL)
	{
		tmp = sprite;
		sprite = sprite->next;
		ft_memdel((void **)&tmp);
	}
}

void	free_images_2(t_main *s)
{
	free_anim(s->items.table);
	free_anim(s->items.lamp);
	free_anim(s->items.gun);
	free_anim(s->items.shotgun);
	free_anim(s->items.big_g_ammo);
	free_anim(s->items.big_s_ammo);
	free_anim(s->items.jetpack);
	free_anim(s->items.bomb);
	free_anim(s->editor->all_texture);
	free_anim(s->gameover);
	free_anim(s->cinematic);
	free_anim(s->skybox);
	free_image(s->interface);
	free_image(s->savemap->croix_rouge);
	free_image(s->player.hud);
	free_image(s->player.crosshair);
}

void	free_images_1(t_main *s)
{
	free_anim(s->menu);
	free_anim(s->editor->menu);
	free_anim(s->editor->sprite_menu);
	free_anim(s->editor->m_floor);
	free_anim(s->stormtrooper.face);
	free_anim(s->stormtrooper.back);
	free_anim(s->stormtrooper.prof);
	free_anim(s->stormtrooper.prof_face);
	free_anim(s->stormtrooper.prof_back);
	free_anim(s->stormtrooper.dying);
	free_anim(s->stormtrooper.shooting);
	free_anim(s->wp_anims.gun);
	free_anim(s->wp_anims.shotgun);
	free_anim(s->wp_anims.kick);
	free_images_2(s);
}
