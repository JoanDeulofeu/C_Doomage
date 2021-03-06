/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_storm_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:31:45 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/10 10:47:58 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_anim				load_prof_back_storm(t_main *s, t_anim data)
{
	ft_bzero((void*)(&data), sizeof(t_anim));
	data.image[0] = load_tga(s,
		"images/ressources/trooper/profback/standing.tga");
	data.image[1] = load_tga(s,
		"images/ressources/trooper/profback/walking1.tga");
	data.image[2] = load_tga(s,
		"images/ressources/trooper/profback/walking2.tga");
	data.image[3] = load_tga(s,
		"images/ressources/trooper/profback/walking3.tga");
	data.image[4] = load_tga(s,
		"images/ressources/trooper/profback/walking4.tga");
	data.image[5] = load_tga(s,
		"images/ressources/trooper/profback/walking5.tga");
	data.image[6] = load_tga(s,
		"images/ressources/trooper/profback/walking6.tga");
	return (data);
}

t_anim				load_prof_face_storm(t_main *s, t_anim data)
{
	data.image[0] = load_tga(s,
		"images/ressources/trooper/profface/standing.tga");
	data.image[1] = load_tga(s,
		"images/ressources/trooper/profface/walking1.tga");
	data.image[2] = load_tga(s,
		"images/ressources/trooper/profface/walking2.tga");
	data.image[3] = load_tga(s,
		"images/ressources/trooper/profface/walking3.tga");
	data.image[4] = load_tga(s,
		"images/ressources/trooper/profface/walking4.tga");
	data.image[5] = load_tga(s,
		"images/ressources/trooper/profface/walking5.tga");
	data.image[6] = load_tga(s,
	"images/ressources/trooper/profface/walking6.tga");
	return (data);
}

t_anim				load_dying_storm(t_main *s, t_anim data)
{
	ft_bzero((void*)(&data), sizeof(t_anim));
	data.image[0] = load_tga(s, "images/ressources/trooper/dying/dying1.tga");
	data.image[1] = load_tga(s, "images/ressources/trooper/dying/dying2.tga");
	data.image[2] = load_tga(s, "images/ressources/trooper/dying/dying3.tga");
	data.image[3] = load_tga(s, "images/ressources/trooper/dying/dying4.tga");
	data.image[4] = load_tga(s, "images/ressources/trooper/dying/dying5.tga");
	data.image[5] = load_tga(s, "images/ressources/trooper/dying/dying6.tga");
	data.image[6] = load_tga(s, "images/ressources/trooper/dying/dying7.tga");
	data.image[7] = load_tga(s, "images/ressources/trooper/dying/dying8.tga");
	return (data);
}

t_anim				load_shooting_storm(t_main *s, t_anim data)
{
	ft_bzero((void*)(&data), sizeof(t_anim));
	data.image[0] = load_tga(s,
	"images/ressources/trooper/shooting/shoot1.tga");
	data.image[1] = load_tga(s,
	"images/ressources/trooper/shooting/shoot2.tga");
	return (data);
}

t_anim_enemy		load_storm_anim(t_main *s)
{
	ft_bzero((void*)(&s->stormtrooper), sizeof(t_anim_enemy));
	s->stormtrooper.face = load_face_storm(s, s->stormtrooper.face);
	s->stormtrooper.back = load_back_storm(s, s->stormtrooper.back);
	s->stormtrooper.prof = load_prof_storm(s, s->stormtrooper.prof);
	s->stormtrooper.prof_back = load_prof_back_storm(s,
	s->stormtrooper.prof_back);
	s->stormtrooper.prof_face = load_prof_face_storm(s,
	s->stormtrooper.prof_face);
	s->stormtrooper.dying = load_dying_storm(s, s->stormtrooper.dying);
	s->stormtrooper.shooting = load_shooting_storm(s, s->stormtrooper.shooting);
	return (s->stormtrooper);
}
