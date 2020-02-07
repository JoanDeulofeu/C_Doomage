/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:54:42 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 15:55:01 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		set_sprite(t_main *s)
{
	t_sprite *tmp;

	tmp = s->sprite;
	while (tmp)
	{
		tmp->pos = get_px_r_pos(s, tmp->r_pos);
		tmp->m_pos.x = tmp->r_pos.x * METRE;
		tmp->m_pos.y = tmp->r_pos.y * METRE;
		tmp = tmp->next;
	}
}

void		reset_statue(t_main *s)
{
	t_sprite *sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->name == bomb)
			sprite->current = 0;
		sprite = sprite->next;
	}
}

void		print_sprite(t_main *s, t_sprite *sprite)
{
	play_sprites_anims(s);
	draw_sprite(s, sprite);
	sprite->displayed = 0;
}

int			check_if_visible(t_main *s, t_sprite *sprite)
{
	t_walls	*wall;
	t_4dpos	pos;

	wall = s->walls;
	while (wall)
	{
		pos.pos1 = wall->player;
		pos.pos3 = wall->left;
		pos.pos4 = wall->right;
		if (wall->wall_or_portal == 'w')
		{
			pos.pos2.x = wall->player.x + cos(to_rad(angle_mod(sprite->angle
				+ wall->angle))) * (sprite->r_dist * METRE);
			pos.pos2.y = wall->player.y - sin(to_rad(sprite->angle
				+ wall->angle)) * (sprite->r_dist * METRE);
			if (ft_find_intersection(s, pos, 1))
			{
				sprite->set = 0;
				sprite->displayed = 0;
				return (0);
			}
		}
		wall = wall->next;
	}
	return (1);
}
