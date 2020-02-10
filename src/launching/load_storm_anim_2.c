/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_storm_anim_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:31:37 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/10 10:35:19 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_anim				load_face_storm(t_main *s, t_anim data)
{
	ft_bzero((void*)(&data), sizeof(t_anim));
	data.image[0] = load_tga(s, "images/ressources/trooper/face/standing.tga");
	data.image[1] = load_tga(s, "images/ressources/trooper/face/walking1.tga");
	data.image[2] = load_tga(s, "images/ressources/trooper/face/walking2.tga");
	data.image[3] = load_tga(s, "images/ressources/trooper/face/walking3.tga");
	data.image[4] = load_tga(s, "images/ressources/trooper/face/walking4.tga");
	data.image[5] = load_tga(s, "images/ressources/trooper/face/walking5.tga");
	data.image[6] = load_tga(s, "images/ressources/trooper/face/walking6.tga");
	return (data);
}

t_anim				load_back_storm(t_main *s, t_anim data)
{
	ft_bzero((void*)(&data), sizeof(t_anim));
	data.image[0] = load_tga(s, "images/ressources/trooper/back/standing.tga");
	data.image[1] = load_tga(s, "images/ressources/trooper/back/walking1.tga");
	data.image[2] = load_tga(s, "images/ressources/trooper/back/walking2.tga");
	data.image[3] = load_tga(s, "images/ressources/trooper/back/walking3.tga");
	data.image[4] = load_tga(s, "images/ressources/trooper/back/walking4.tga");
	data.image[5] = load_tga(s, "images/ressources/trooper/back/walking5.tga");
	data.image[6] = load_tga(s, "images/ressources/trooper/back/walking6.tga");
	return (data);
}

t_anim				load_prof_storm(t_main *s, t_anim data)
{
	ft_bzero((void*)(&data), sizeof(t_anim));
	data.image[0] = load_tga(s, "images/ressources/trooper/prof/standing.tga");
	data.image[1] = load_tga(s, "images/ressources/trooper/prof/walking1.tga");
	data.image[2] = load_tga(s, "images/ressources/trooper/prof/walking2.tga");
	data.image[3] = load_tga(s, "images/ressources/trooper/prof/walking3.tga");
	data.image[4] = load_tga(s, "images/ressources/trooper/prof/walking4.tga");
	data.image[5] = load_tga(s, "images/ressources/trooper/prof/walking5.tga");
	data.image[6] = load_tga(s, "images/ressources/trooper/prof/walking6.tga");
	return (data);
}
