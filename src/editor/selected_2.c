/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:17:45 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 13:19:38 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sprite	*is_sprite_under_mouse(t_main *s)
{
	t_sprite	*sprite;
	t_dpos		s_pos;
	t_dpos		mouse;
	float		value;

	sprite = s->sprite;
	value = 0.5;
	mouse = get_abs_r_pos(s, s->ft_mouse);
	while (sprite)
	{
		s_pos = sprite->r_pos;
		if (s_pos.x <= mouse.x + value
				&& s_pos.x >= mouse.x - value
				&& s_pos.y >= mouse.y - value
				&& s_pos.y <= mouse.y + value)
			return (sprite);
		sprite = sprite->next;
	}
	return (NULL);
}

int			select_sprite(t_main *s)
{
	t_sprite *sprite;

	sprite = is_sprite_under_mouse(s);
	if (sprite)
	{
		sprite->selected = 1;
		sprite->old = sprite->r_ori;
		return (1);
	}
	return (0);
}

void		deselect_vertex(t_main *s)
{
	t_vertex	*v;

	v = s->vertex;
	while (v)
	{
		v->selec = 0;
		v->selected = 0;
		if (v)
			v = v->next;
	}
}

int			is_vertex_selected(t_vertex *v, t_line line)
{
	if (((v->pos.x >= line.x1 && v->pos.x <= line.x2)
				&& (v->pos.y >= line.y1 && v->pos.y <= line.y2))
			|| ((v->pos.x <= line.x1 && v->pos.x >= line.x2)
				&& (v->pos.y <= line.y1 && v->pos.y >= line.y2))
			|| ((v->pos.x <= line.x1 && v->pos.x >= line.x2)
				&& (v->pos.y >= line.y1 && v->pos.y <= line.y2))
			|| ((v->pos.x >= line.x1 && v->pos.x <= line.x2)
				&& (v->pos.y <= line.y1 && v->pos.y >= line.y2)))
		return (1);
	return (0);
}

void		select_vertex(t_main *s)
{
	t_vertex	*v;
	t_line		line;
	t_pos		pos;

	deselect_vertex(s);
	v = s->vertex;
	line = s->editor->line;
	while (v)
	{
		pos.x = v->x;
		pos.y = v->y;
		v->pos = get_px_pos(s, pos);
		if (is_vertex_selected(v, line))
		{
			v->selec = 1;
			v->selected = 1;
			v->old.x = v->x;
			v->old.y = v->y;
		}
		if (v)
			v = v->next;
	}
	s->editor->selected = 0;
}
