/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:53:55 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/05 17:08:40 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_pos		get_px_r_pos(t_main *s, t_dpos ref)
{
	t_pos		pos;
	t_editor	*edi;
	int			correc;

	correc = 0;
	edi = s->editor;
	if (edi->decal_x <= 0)
		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.x = (ref.x - edi->ref.x + correc) * edi->space
		+ (edi->decal_x % edi->space);
	if (edi->decal_y <= 0)
		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (ref.y - edi->ref.y + correc) * edi->space
		+ (edi->decal_y % edi->space);
	return (pos);
}

t_pos		get_abs_pos(t_main *s, t_pos ori)
{
	t_pos	res;
	int		correc_x;
	int		correc_y;

	res.x = 0;
	res.y = 0;
	correc_x = 0;
	correc_y = 0;
	if (s->editor->decal_x % s->editor->space != 0 && s->editor->decal_x < 0)
		correc_x = -1;
	if (s->editor->decal_y % s->editor->space != 0 && s->editor->decal_y < 0)
		correc_y = -1;
	res.x = s->editor->ref.x + (ori.x / s->editor->space) + correc_x;
	res.y = s->editor->ref.y + (ori.y / s->editor->space) + correc_y;
	return (res);
}

t_dpos		get_direction(t_main *s, const Uint8 *keys,
	double speed, t_dpos target)
{
	if (keys == NULL || keys[UP])
	{
		target.x += cos(to_rad(s->player.angle)) * speed;
		target.y -= sin(to_rad(s->player.angle)) * speed;
		if (keys == NULL)
			return (target);
	}
	if (keys[DOWN])
	{
		target.x -= cos(to_rad(s->player.angle * -1)) * speed;
		target.y -= sin(to_rad(s->player.angle * -1)) * speed;
	}
	if (keys[LEFT])
	{
		target.x += cos(to_rad(s->player.angle + 90)) * speed;
		target.y -= sin(to_rad(s->player.angle + 90)) * speed;
	}
	if (keys[RIGHT])
	{
		target.x += cos(to_rad(s->player.angle - 90)) * speed;
		target.y -= sin(to_rad(s->player.angle - 90)) * speed;
	}
	return (target);
}
