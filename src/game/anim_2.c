/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:13:44 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 17:36:29 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	enemy_walk_anim(t_main *s, t_sprite *sprite)
{
	if (s->time->time_ms - sprite->anim_ms > 200)
	{
		sprite->current++;
		if (!sprite->anim.image[sprite->current])
			sprite->current = 1;
		sprite->anim_ms = s->time->time_ms;
	}
}

void	check_sprite_shooting(t_main *s, t_sprite *sprite)
{
	if (sprite->r_dist < STORM_RANGE && sprite->a_name != dying)
	{
		sprite->current = 0;
		sprite->anim = s->stormtrooper.shooting;
		sprite->a_name = shooting;
	}
}

void	get_anim_by_angle(t_main *s, t_sprite *sprite, double angle)
{
	if ((angle >= 0 && angle <= 23) || (angle >= 338 && angle <= 360)
	|| (angle >= -23 && angle <= 0) || (angle >= -360 && angle <= -338))
		sprite->anim = s->stormtrooper.back;
	else if ((angle >= 203 && angle <= 248) || (angle >= -158 && angle <= -113)
		|| (angle >= 113 && angle <= 158) || (angle >= -248 && angle <= -203))
	{
		sprite->anim = s->stormtrooper.prof_face;
		check_sprite_shooting(s, sprite);
	}
	else if ((angle >= 248 && angle <= 293) || (angle >= -113 && angle <= -68)
		|| (angle >= 68 && angle <= 113) || (angle >= -293 && angle <= -248))
		sprite->anim = s->stormtrooper.prof;
	else if ((angle >= 23 && angle <= 68) || (angle >= 293 && angle <= 338)
		|| (angle >= -338 && angle <= -293) || (angle >= -68 && angle <= -23))
		sprite->anim = s->stormtrooper.prof_back;
	else if ((angle >= 158 && angle <= 203) || (angle >= -203 && angle <= -158))
	{
		sprite->anim = s->stormtrooper.face;
		check_sprite_shooting(s, sprite);
	}
}

void	play_sprites_anims(t_main *s)
{
	t_sprite *sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->name == storm)
		{
			if (sprite->a_name == shooting && !sprite->destroy)
			{
				sprite->current = 0;
				sprite->anim = s->stormtrooper.shooting;
				sprite_shooting(s, sprite);
			}
			if (sprite->a_name == walking && !sprite->destroy)
			{
				if (sprite->set)
					select_anim(s, sprite);
				enemy_walk_anim(s, sprite);
			}
			else if (sprite->a_name == dying && !sprite->destroy)
				kill_anim(s, sprite);
		}
		sprite = sprite->next;
	}
}
