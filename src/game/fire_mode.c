/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:28:09 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 18:31:04 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		set_weapon_range(t_main *s)
{
	if (s->player.wp_name == kick)
	{
		s->player.range = 10;
		s->player.power = 10;
	}
	else if (s->player.wp_name == gun)
	{
		s->player.range = 20;
		s->player.power = 30;
	}
	else if (s->player.wp_name == shotgun)
	{
		s->player.range = 10;
		s->player.power = 100;
	}
}

void		change_weapon_up(t_main *s)
{
	s->player.wp_name++;
	if (s->player.wp_name > 2)
		s->player.wp_name = 0;
	while (s->player.wp_wheel[s->player.wp_name] != 1)
	{
		s->player.wp_name++;
		if (s->player.wp_name > 2)
			s->player.wp_name = 0;
	}
}

void		change_weapon(t_main *s, int up)
{
	if (up)
		change_weapon_up(s);
	if (up == 0)
	{
		if (s->player.wp_name == kick)
			s->player.wp_name = 2;
		else
			s->player.wp_name--;
		while (s->player.wp_wheel[s->player.wp_name] != 1)
		{
			if (s->player.wp_name == kick)
				s->player.wp_name = 2;
			else
				s->player.wp_name--;
		}
	}
	select_weapon_anim(s);
	set_weapon_range(s);
}

t_sprite	*check_storm_hitbox(t_main *s, t_sprite *sprite,
	t_sprite *save_sprite, double pct)
{
	double		height;
	double		width;
	double		diff_height_pxl;

	pct = (sprite->r_dist * METRE * 100) / sprite->l_dist;
	height = HEIGHT / ((pct * 0.001) * 4) * sprite->size * HEIGHT_MULT;
	pct = (100 * sprite->anim.image[sprite->current]->w)
		/ sprite->anim.image[sprite->current]->h;
	width = (pct * height) * 0.01;
	diff_height_pxl = ft_get_sprite_height_pxl(s, sprite, height);
	if (sprite->r_dist < s->player.range
			&& (WIDTH * 0.5) > sprite->x - (width * 0.5) && WIDTH * 0.5 <
			sprite->x + (width * 0.5) && (HEIGHT * 0.5) > (HEIGHT * 0.5)
			- height + s->player.y_eye + diff_height_pxl && (HEIGHT * 0.5) <
			(HEIGHT * 0.5) + s->player.y_eye + diff_height_pxl)
	{
		if (save_sprite)
		{
			if (sprite->r_dist < save_sprite->r_dist)
				save_sprite = sprite;
		}
		else
			save_sprite = sprite;
	}
	return (save_sprite);
}

void		fire(t_main *s)
{
	t_sprite	*sprite;
	t_sprite	*save_sprite;

	sprite = s->sprite;
	save_sprite = NULL;
	while (sprite)
	{
		if (sprite->name == storm && sprite->set == 1 && !sprite->destroy)
			save_sprite = check_storm_hitbox(s, sprite, save_sprite, 0);
		sprite = sprite->next;
	}
	if (save_sprite)
	{
		printf("hit\n");
		save_sprite->life -= s->player.power;
		if (save_sprite->life <= 0 && save_sprite->a_name != dying)
		{
			save_sprite->anim = s->stormtrooper.dying;
			save_sprite->a_name = dying;
			save_sprite->current = 0;
		}
	}
}
