/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:10:27 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/10 20:13:24 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		check_bomb(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->name == bomb && sprite->r_dist < 3.5 && sprite->set == 1)
		{
			sprite->current = 1;
			s->sct_without_ceiling = s->player.sector_id;
			s->transition_y_eye = s->player.y_eye;
			s->transition_angle = s->player.angle;
			s->transition = 1;
			s->block_move = 1;
			s->time->explosion_ms = s->time->time_ms;
		}
		sprite = sprite->next;
	}
}

void		tp_first_sector(t_main *s)
{
	t_sector	*sct;
	t_pos		center;

	sct = s->sector;
	if (sct)
	{
		center = ft_find_polygon_center(sct);
		s->player.r_pos.x = (center.x / METRE);
		s->player.r_pos.y = (center.y / METRE);
		set_player(s);
		s->player.jump_height = 0;
		s->player.foot_height = sct->floor + s->player.jump_height;
		if ((s->player.sector_id = ft_is_in_sector(s, s->player.m_pos)) == 0)
			handle_sector_zero(s);
	}
}

static int	check_pos(t_main *s, t_dpos curr)
{
	t_sector *sct;

	if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
	{
		s->player.r_pos.x = curr.x / METRE;
		s->player.r_pos.y = curr.y / METRE;
		set_player(s);
		sct = get_sector_by_id(s, s->player.sector_id);
		if (s->player.foot_height > (double)sct->floor + 0.01)
		{
			s->player.jump_height += s->player.floor_height - (double)sct->floor;
			s->player.prev_jump_height = s->player.jump_height;
			if (s->player.jump == 0 && s->player.fly == 0)
				s->player.jump = 3;
		}
		return (1);
	}
	else
		return (0);
}

int			handle_sector_zero_2(t_main *s, t_dpos *curr, int nb)
{
	(*curr).x = s->player.m_pos.x;
	(*curr).y = s->player.m_pos.y + nb;
	if (check_pos(s, *curr))
		return (1);
	(*curr).y = s->player.m_pos.y - nb;
	if (check_pos(s, *curr))
		return (1);
	(*curr).x = s->player.m_pos.x - nb;
	if (check_pos(s, *curr))
		return (1);
	(*curr).x = s->player.m_pos.x + nb;
	if (check_pos(s, *curr))
		return (1);
	(*curr).y += nb * 2;
	if (check_pos(s, *curr))
		return (1);
	(*curr).x -= nb * 2;
	if (check_pos(s, *curr))
		return (1);
	return (0);
}

int			handle_sector_zero(t_main *s)
{
	int			nb;
	t_dpos		curr;

	nb = 1;
	if (ft_is_in_sector(s, s->player.m_pos) == 0)
	{
		while (nb < 100 * METRE)
		{
			curr = s->player.m_pos;
			curr.x = s->player.m_pos.x + nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.m_pos.x - nb;
			if (check_pos(s, curr))
				return (1);
			if (handle_sector_zero_2(s, &curr, nb))
				return (1);
			nb++;
		}
		tp_first_sector(s);
	}
	return (0);
}
