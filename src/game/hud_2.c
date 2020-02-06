/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:22:00 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 12:26:53 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		animate_shotgun(t_main *s, long time)
{
	if (s->player.shoot == 0)
		return ;
	time = s->time->time_ms - s->time->shotgun_ms;
	if (time >= 0 && time <= 200)
		s->player.weapon.current = 1;
	else if (time > 200 && time <= 300)
		s->player.weapon.current = 2;
	else if (time > 300 && time <= 400)
		s->player.weapon.current = 3;
	else if (time > 400 && time <= 500)
		s->player.weapon.current = 4;
	else if (time > 500 && time <= 600)
		s->player.weapon.current = 5;
	else if (time > 600 && time <= 700)
		s->player.weapon.current = 6;
	else if (time > 700 && time <= 800)
		s->player.weapon.current = 5;
	else if (time > 800 && time <= 900)
		s->player.weapon.current = 4;
	else if (time > 900)
	{
		s->player.weapon.current = 0;
		s->player.shoot = 0;
	}
}

void		animate_gun(t_main *s)
{
	long	time;

	if (s->player.shoot == 0)
		return ;
	time = s->time->time_ms - s->time->shotgun_ms;
	if (time > 100 && time <= 150)
		s->player.weapon.current = 1;
	if (time > 150 && time <= 250)
		s->player.weapon.current = 2;
	if (time > 250)
	{
		s->player.weapon.current = 0;
		s->player.shoot = 0;
	}
}

void		animate_kick(t_main *s)
{
	long	time;

	if (s->player.shoot == 0)
		return ;
	time = s->time->time_ms - s->time->shotgun_ms;
	if (time <= 200)
		s->player.weapon.current = 1;
	else if (time > 200 && time <= 400)
	{
		s->player.weapon.current = 2;
	}
	else if (time > 400 && time <= 600)
	{
		s->player.weapon.current = 3;
	}
	else
	{
		s->player.weapon.current = 0;
		s->player.shoot = 0;
	}
}

void		animate_weapon(t_main *s)
{
	if (s->player.wp_name == shotgun)
		animate_shotgun(s, 0);
	else if (s->player.wp_name == gun)
		animate_gun(s);
	else if (s->player.wp_name == kick)
		animate_kick(s);
}

void		shoot(t_main *s)
{
	if (s->player.shoot == 0)
	{
		s->player.shoot = 1;
		s->time->shotgun_ms = s->time->time_ms;
		fire(s);
		if (s->player.wp_name == gun && s->player.mun_gun > 0)
		{
			Mix_PlayChannel(2, s->sdl->sounds.gun, 0);
			animate_weapon(s);
			s->player.mun_gun--;
		}
		else if (s->player.wp_name == shotgun && s->player.mun_shotgun > 0)
		{
			Mix_PlayChannel(2, s->sdl->sounds.shotgun, 0);
			animate_weapon(s);
			s->player.mun_shotgun--;
		}
		else if (s->player.wp_name == kick)
			animate_weapon(s);
	}
}
