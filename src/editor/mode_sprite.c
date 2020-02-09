/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:50:09 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/09 21:45:44 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		get_sprite_info_by_name3(t_main *s, t_sprite *sprite)
{
	if (sprite->name == o_shotgun)
	{
		sprite->size = 0.3;
		sprite->anim = s->items.shotgun;
		sprite->type = item;
	}
	else if (sprite->name == big_g_ammo)
	{
		sprite->size = 0.2;
		sprite->anim = s->items.big_g_ammo;
		sprite->type = item;
	}
	else if (sprite->name == big_s_ammo)
	{
		sprite->size = 0.2;
		sprite->anim = s->items.big_s_ammo;
		sprite->type = item;
	}
	else if (sprite->name == jetpack)
	{
		sprite->size = 0.5;
		sprite->anim = s->items.jetpack;
		sprite->type = item;
	}
}

void		get_sprite_info_by_name2(t_main *s, t_sprite *sprite)
{
	if (sprite->name == table)
	{
		sprite->size = 1;
		sprite->anim = s->items.table;
		sprite->type = obstacle;
	}
	else if (sprite->name == lamp)
	{
		sprite->size = 3;
		sprite->anim = s->items.lamp;
		sprite->type = obstacle;
	}
	else if (sprite->name == bomb)
	{
		sprite->size = 2.8;
		sprite->anim = s->items.bomb;
		sprite->type = obstacle;
	}
	else if (sprite->name == o_gun)
	{
		sprite->size = 0.5;
		sprite->anim = s->items.gun;
		sprite->type = item;
	}
}

void		get_sprite_info_by_name(t_main *s, t_name name, t_sprite *sprite)
{
	if (name != none)
		sprite->name = name;
	else
		sprite->name = s->editor->sprite_selected;
	if (sprite->name == storm)
	{
		sprite->size = 2;
		sprite->anim = s->stormtrooper.face;
		sprite->type = enemy;
	}
	else if (sprite->name == table || sprite->name == lamp
		|| sprite->name == bomb || sprite->name == o_gun)
		get_sprite_info_by_name2(s, sprite);
	else
		get_sprite_info_by_name3(s, sprite);
}

t_sprite	*ft_fill_sprite(t_main *s, int part, t_sprite *sprite, t_dpos r_pos)
{
	if (part == 1)
	{
		if (!(sprite = malloc(sizeof(t_sprite))))
			handle_error(s, MALLOC_ERROR);
		ft_bzero((void*)sprite, sizeof(t_sprite));
		sprite->r_pos = r_pos;
		sprite->r_dist = 100;
		sprite->pos = get_px_r_pos(s, r_pos);
		sprite->r_ori = sprite->r_pos;
		sprite->life = 100;
		return (sprite);
	}
	s->sprite = sprite;
	s->sprite->id = 1;
	add_sprite_to_sector(s, sprite);
	return (sprite);
}

t_sprite	*create_new_sprite(t_main *s, t_name name,
	t_dpos r_pos, t_sprite *temp)
{
	t_sprite	*sprite;
	int			sct_id;
	t_dpos		pos;

	pos.x = r_pos.x * METRE;
	pos.y = r_pos.y * METRE;
	if ((sct_id = ft_is_in_sector(s, pos)) == 0)
		return (NULL);
	sprite = ft_fill_sprite(s, 1, NULL, r_pos);
	sprite->sct_id = ft_is_in_sector(s, pos);
	sprite->m_pos = pos;
	get_sprite_info_by_name(s, name, sprite);
	if (!check_limit_sprite(s, sct_id, sprite))
	{
		ft_memdel((void **)&sprite);
		return (NULL);
	}
	if (!s->sprite)
		return (ft_fill_sprite(s, 2, sprite, r_pos));
	while (temp->next)
		temp = temp->next;
	temp->next = sprite;
	sprite->id = temp->id + 1;
	add_sprite_to_sector(s, sprite);
	return (sprite);
}
