/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_anims.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:51:16 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 15:00:41 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	load_skybox(t_main *s)
{
	ft_bzero((void *)&s->skybox, sizeof(t_anim));
	s->skybox.image[0] = load_tga("images/skybox_00.tga", 0, 0, 0);
	s->skybox.image[1] = load_tga("images/skybox_01.tga", 0, 0, 0);
	s->skybox.image[2] = load_tga("images/skybox_02.tga", 0, 0, 0);
	s->skybox.image[3] = load_tga("images/skybox_03.tga", 0, 0, 0);
	s->skybox.image[4] = load_tga("images/skybox_04.tga", 0, 0, 0);
	s->skybox.image[5] = load_tga("images/skybox_05.tga", 0, 0, 0);
	s->skybox.image[6] = load_tga("images/skybox_06.tga", 0, 0, 0);
	s->skybox.image[7] = load_tga("images/skybox_07.tga", 0, 0, 0);
	s->skybox.image[8] = load_tga("images/skybox_08.tga", 0, 0, 0);
	s->skybox.image[9] = load_tga("images/skybox_09.tga", 0, 0, 0);
	s->skybox.image[10] = load_tga("images/skybox_10.tga", 0, 0, 0);
	s->skybox.image[11] = load_tga("images/skybox_11.tga", 0, 0, 0);
	s->skybox.image[12] = load_tga("images/skybox_12.tga", 0, 0, 0);
	s->skybox.image[13] = load_tga("images/skybox_13.tga", 0, 0, 0);
	s->skybox.image[14] = load_tga("images/skybox_14.tga", 0, 0, 0);
	s->skybox.image[15] = load_tga("images/skybox_15.tga", 0, 0, 0);
	s->skybox.image[16] = load_tga("images/skybox_16.tga", 0, 0, 0);
	s->skybox.image[17] = load_tga("images/skybox_17.tga", 0, 0, 0);
}

void	load_items(t_main *s)
{
	ft_bzero((void *)&s->items, sizeof(t_anim));
	s->items.table.image[0] =
	load_tga("images/ressources/static/table.tga", 0, 0, 0);
	s->items.lamp.image[0] =
	load_tga("images/ressources/static/lamp.tga", 0, 0, 0);
	s->items.gun.image[0] =
	load_tga("images/ressources/static/gun.tga", 0, 0, 0);
	s->items.shotgun.image[0] =
	load_tga("images/ressources/static/shotgun.tga", 0, 0, 0);
	s->items.big_s_ammo.image[0] =
	load_tga("images/ressources/static/big_s_ammo.tga", 0, 0, 0);
	s->items.big_g_ammo.image[0] =
	load_tga("images/ressources/static/big_g_ammo.tga", 0, 0, 0);
	s->items.jetpack.image[0] =
	load_tga("images/ressources/static/jetpack.tga", 0, 0, 0);
	s->items.bomb.image[0] =
	load_tga("images/ressources/static/bomb00.tga", 0, 0, 0);
	s->items.bomb.image[1] =
	load_tga("images/ressources/static/bomb01.tga", 0, 0, 0);
}

void	load_cinematic(t_main *s)
{
	ft_bzero((void *)&s->cinematic, sizeof(t_anim));
	s->cinematic.image[0] =
	load_tga("images/ressources/scenar/intro_00.tga", 0, 0, 0);
	s->cinematic.image[1] =
	load_tga("images/ressources/scenar/intro_01.tga", 0, 0, 0);
	s->cinematic.image[2] =
	load_tga("images/ressources/scenar/intro_02.tga", 0, 0, 0);
	s->cinematic.image[3] =
	load_tga("images/ressources/scenar/intro_03.tga", 0, 0, 0);
	s->cinematic.image[4] =
	load_tga("images/ressources/scenar/ending.tga", 0, 0, 0);
}

void	load_game_over(t_main *s)
{
	ft_bzero((void *)&s->gameover, sizeof(t_anim));
	s->gameover.image[0] = load_tga("images/go/00.tga", 0, 0, 0);
	s->gameover.image[1] = load_tga("images/go/01.tga", 0, 0, 0);
	s->gameover.image[2] = load_tga("images/go/02.tga", 0, 0, 0);
	s->gameover.image[3] = load_tga("images/go/03.tga", 0, 0, 0);
	s->gameover.image[4] = load_tga("images/go/04.tga", 0, 0, 0);
	s->gameover.image[5] = load_tga("images/go/05.tga", 0, 0, 0);
	s->gameover.image[6] = load_tga("images/go/06.tga", 0, 0, 0);
}

void	load_anims(t_main *s)
{
	load_skybox(s);
	s->stormtrooper = load_storm_anim(s);
	load_items(s);
	load_game_over(s);
	load_cinematic(s);
	s->wp_anims = load_wp_anims(s);
}
