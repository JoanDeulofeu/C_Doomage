/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:52:33 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 18:26:02 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		give_damage(t_main *s, int id)
{
	t_sprite	*cur;

	cur = s->sprite;
	while (cur != NULL)
	{
		if (cur->id == id && cur->life != 0)
		{
			cur->life = 0;
			cur->current = 0;
			break ;
		}
		cur = cur->next;
	}
}

int			check_exist(t_main *s, t_dpos target, int id)
{
	t_sprite	*cur;
	double		hitbox;

	hitbox = 0.5;
	cur = s->sprite;
	while (cur != NULL)
	{
		if (((target.x >= (cur->r_pos.x - hitbox)
			&& target.x <= (cur->r_pos.x + hitbox))
			&& (target.y >= (cur->r_pos.y - hitbox))
			&& target.y <= (cur->r_pos.y + hitbox))
			&& cur->id != id)
		{
			return (cur->id);
		}
		cur = cur->next;
	}
	return (-1);
}

double		found_player(t_main *s, t_sprite *cur)
{
	t_dpos	ctr_l;
	double	angle;
	t_pos	ret;

	angle = 0;
	ctr_l.x = cur->pos.x + cos(to_rad(angle)) * cur->dist;
	ctr_l.y = cur->pos.y - sin(to_rad(angle)) * cur->dist;
	while (angle <= 360)
	{
		ctr_l.x = cur->pos.x + cos(to_rad(angle)) * cur->dist;
		ctr_l.y = cur->pos.y - sin(to_rad(angle)) * cur->dist;
		ret = ft_dpos_to_pos(ctr_l);
		if ((ret.x >= (s->player.pos.x - HITBOX)
			&& ret.x <= (s->player.pos.x + HITBOX))
			&& (ret.y >= (s->player.pos.y - HITBOX)
			&& ret.y <= (s->player.pos.y + HITBOX)))
			break ;
		angle += 0.1;
	}
	return (angle);
}

void		rand_move(t_main *s, double angle, t_sprite *sprite)
{
	t_dpos		target;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->name == storm && sprite->destroy == 0
			&& sprite->a_name == walking)
		{
			target = sprite->r_pos;
			target.x += cos(to_rad(sprite->s_angle)) * SPRITE_MOVE_SPEED;
			target.y -= sin(to_rad(sprite->s_angle)) * SPRITE_MOVE_SPEED;
			while (is_colliding(s, target, sprite->sct_id))
			{
				target = sprite->r_pos;
				angle = fmod(rand(), 360);
				sprite->s_angle = angle;
				target.x += cos(to_rad(sprite->s_angle)) * SPRITE_MOVE_SPEED;
				target.y -= sin(to_rad(sprite->s_angle)) * SPRITE_MOVE_SPEED;
			}
			sprite->r_pos = target;
			set_sprite(s);
		}
		sprite = sprite->next;
	}
}
