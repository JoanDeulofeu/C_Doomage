/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:50:45 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 17:35:54 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		play_g_o_anim(t_main *s)
{
	t_pos	pos;
	int		time;

	pos.x = 0;
	pos.y = 0;
	if (s->time->g_o_ms == 0)
		s->time->g_o_ms = s->time->time_ms;
	time = s->time->time_ms - s->time->g_o_ms;
	if (time < 250)
		draw_plain_sprite(s, pos, s->gameover.image[0], s->sdl->game);
	else if (time >= 250 && time < 500)
		draw_plain_sprite(s, pos, s->gameover.image[1], s->sdl->game);
	else if (time >= 500 && time < 750)
		draw_plain_sprite(s, pos, s->gameover.image[2], s->sdl->game);
	else if (time >= 750 && time < 1000)
		draw_plain_sprite(s, pos, s->gameover.image[3], s->sdl->game);
	else if (time >= 1000 && time < 1250)
		draw_plain_sprite(s, pos, s->gameover.image[4], s->sdl->game);
	else if (time >= 1250 && time < 1500)
		draw_plain_sprite(s, pos, s->gameover.image[5], s->sdl->game);
	else if (time >= 1500 && time < 2000)
	{
		draw_plain_sprite(s, pos, s->gameover.image[6], s->sdl->game);
	}
}

void		select_weapon_anim(t_main *s)
{
	if (s->player.wp_name == kick)
		s->player.weapon = s->wp_anims.kick;
	else if (s->player.wp_name == gun)
		s->player.weapon = s->wp_anims.gun;
	else if (s->player.wp_name == shotgun)
		s->player.weapon = s->wp_anims.shotgun;
	s->player.weapon.current = 0;
}

void		sprite_shooting(t_main *s, t_sprite *cur)
{
	if (cur->anim.image[cur->current] == NULL)
		return ;
	if (cur->r_dist < STORM_RANGE &&
			!ft_find_wall(s, s->player.m_pos, cur->m_pos, s->player.sector_id))
	{
		cur->current = 1;
		if (s->time->time_ms - cur->shoot_ms > 1000)
		{
			cur->shoot_ms = s->time->time_ms;
			Mix_PlayChannel(6, s->sdl->sounds.blaster, 0);
			if (s->player.armor > 0)
				s->player.armor -= 20;
			else
			{
				s->player.health -= 10;
				if (s->player.health <= 0)
					s->player.dead = 1;
			}
		}
	}
	else
	{
		cur->a_name = walking;
		cur->current = 0;
	}
}

void		kill_anim(t_main *s, t_sprite *sprite)
{
	if (s->time->time_ms - sprite->anim_ms > 50)
	{
		sprite->current++;
		if (!sprite->anim.image[sprite->current])
		{
			sprite->destroy = 1;
			sprite->set = 0;
			sprite->displayed = 0;
			sprite->current = 0;
		}
		sprite->anim_ms = s->time->time_ms;
	}
}

void		select_anim(t_main *s, t_sprite *sprite)
{
	t_walls		*wall;
	double		angle;

	wall = s->walls;
	while (wall && wall->sct_id != sprite->sct_id)
		wall = wall->next;
	if (wall->angle > 360)
		wall->angle = fmod(wall->angle, 360);
	if (sprite->s_angle > 360)
		sprite->s_angle = fmod(sprite->s_angle, 360);
	angle = wall->angle - sprite->s_angle;
	if (angle > 180 || (angle > -180 && angle < 0))
		sprite->inverse = 0;
	else
		sprite->inverse = 1;
	get_anim_by_angle(s, sprite, angle);
}
