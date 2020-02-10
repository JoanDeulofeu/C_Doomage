/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wp_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:28:16 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/10 10:36:30 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_anim				load_gun_anim(t_main *s, t_anim data)
{
	ft_bzero((void *)&data, sizeof(t_anim));
	data.image[0] = load_tga(s, "images/weapons/gun/00.tga");
	data.image[1] = load_tga(s, "images/weapons/gun/01.tga");
	data.image[2] = load_tga(s, "images/weapons/gun/02.tga");
	return (data);
}

t_anim				load_shotgun_anim(t_main *s, t_anim data)
{
	ft_bzero((void *)&data, sizeof(t_anim));
	data.image[0] = load_tga(s, "images/weapons/shotgun/shotgun1.tga");
	data.image[1] = load_tga(s, "images/weapons/shotgun/shotgun_fire.tga");
	data.image[2] = load_tga(s, "images/weapons/shotgun/shotgun_fire.tga");
	data.image[3] = load_tga(s, "images/weapons/shotgun/shotgun2.tga");
	data.image[4] = load_tga(s, "images/weapons/shotgun/shotgun3.tga");
	data.image[5] = load_tga(s, "images/weapons/shotgun/shotgun4.tga");
	data.image[6] = load_tga(s, "images/weapons/shotgun/shotgun5.tga");
	return (data);
}

t_anim				load_kick_anim(t_main *s, t_anim data)
{
	ft_bzero((void *)&data, sizeof(t_anim));
	data.image[0] = NULL;
	data.image[1] = load_tga(s, "images/weapons/kick/01.tga");
	data.image[2] = load_tga(s, "images/weapons/kick/02.tga");
	data.image[3] = load_tga(s, "images/weapons/kick/01.tga");
	return (data);
}

t_anim_wp			load_wp_anims(t_main *s)
{
	ft_bzero((void *)&s->wp_anims, sizeof(t_anim_wp));
	s->wp_anims.gun = load_gun_anim(s, s->wp_anims.gun);
	s->wp_anims.shotgun = load_shotgun_anim(s, s->wp_anims.shotgun);
	s->wp_anims.kick = load_kick_anim(s, s->wp_anims.kick);
	return (s->wp_anims);
}
