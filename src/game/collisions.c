/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:07:04 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 15:16:49 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		get_item(t_main *s, t_sprite *sprite)
{
	if (sprite->name == o_shotgun)
		s->player.wp_wheel[shotgun] = 1;
	else if (sprite->name == o_gun)
		s->player.wp_wheel[gun] = 1;
	else if (sprite->name == jetpack)
	{
		s->player.jetpack = 1;
		s->time->jetpack_reserve = JET_TIME;
	}
	else if (sprite->name == big_s_ammo)
	{
		s->player.mun_shotgun += 5;
		if (s->player.mun_shotgun > 15)
			s->player.mun_shotgun = 15;
	}
	else if (sprite->name == big_g_ammo)
	{
		s->player.mun_gun += 10;
		if (s->player.mun_gun > 100)
			s->player.mun_gun = 100;
	}
}

void		check_collectible(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->type == item && sprite->destroy == 0 && sprite->r_dist < 2)
		{
			get_item(s, sprite);
			sprite->destroy = 1;
		}
		sprite = sprite->next;
	}
}

int			check_col(t_main *s, t_dpos haut, t_dpos bas, int sct_id)
{
	int			id;
	t_sector	*sct;
	t_int		*wall;

	id = ft_find_wall(s, haut, bas, sct_id);
	if (id != 0)
	{
		sct = get_sector_by_id(s, sct_id);
		wall = get_t_int_by_vertex_id(sct->vertex, id);
		return (wall->wall_value);
	}
	else
		return (0);
}

int			check_diagonale_collision(t_main *s, t_dpos target,
			int sct_id, int value)
{
	t_dpos	haut;
	t_dpos	bas;
	int		id;

	haut.y = target.y - value;
	bas.y = target.y + value;
	haut.x = target.x - value;
	bas.x = target.x + value;
	if ((id = (check_col(s, haut, bas, sct_id))) != 0)
		return (id);
	haut.x = target.x + value;
	bas.x = target.x - value;
	if ((id = (check_col(s, haut, bas, sct_id))) != 0)
		return (id);
	return (0);
}

int			is_colliding(t_main *s, t_dpos target, int sct_id, t_dpos haut)
{
	int			id;
	t_dpos		bas;
	int			value;

	target.x *= METRE;
	target.y *= METRE;
	haut = target;
	bas = target;
	value = s->editor->anchor_size / 1.2;
	haut.x = target.x + value;
	bas.x = target.x - value;
	if ((id = (check_col(s, haut, bas, sct_id))) != 0)
		return (id);
	haut = target;
	bas = target;
	haut.y = target.y - value;
	bas.y = target.y + value;
	if ((id = (check_col(s, haut, bas, sct_id))) != 0)
		return (id);
	if ((id = check_diagonale_collision(s, target, sct_id, value)))
		return (id);
	return (0);
}
