/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:47:15 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 19:23:17 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			ft_vertex_worst_sector(t_main *s, int id)
{
	t_sector	*sct;
	t_int		*vtx;
	int			i;

	sct = s->sector;
	while (sct)
	{
		i = 0;
		vtx = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (vtx->value == id && sct->floor == s->editor->dply_floor)
				return (1);
			vtx = vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

void		ft_choose_draw_vertex(t_main *s, t_vertex *temp, t_pos pos)
{
	if (s->editor->mode_floor == 0)
	{
		if (temp->selected == 2)
			draw_anchor(s, pos, PINK);
		else if (temp->selected == 1)
			draw_anchor(s, pos, BLUE);
		else
			draw_anchor(s, pos, GREEN);
	}
	else
	{
		if (ft_vertex_worst_sector(s, temp->id))
			draw_anchor(s, pos, PINK);
	}
}

t_pos		get_map_pos(t_main *s, t_vertex *temp, t_pos pos)
{
	int			correc;

	if (s->editor->decal_x <= 0)
		correc = s->editor->decal_x % s->editor->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.x = (temp->x - s->editor->ref.x + correc) *
		s->editor->space + (s->editor->decal_x % s->editor->space);
	if (s->editor->decal_y <= 0)
		correc = s->editor->decal_y % s->editor->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (temp->y - s->editor->ref.y + correc) *
		s->editor->space + (s->editor->decal_y % s->editor->space);
	return (pos);
}

void		display_map(t_main *s)
{
	t_vertex	*temp;
	t_pos		pos;

	temp = NULL;
	if (s->vertex)
		temp = s->vertex;
	while (temp)
	{
		pos = get_map_pos(s, temp, pos);
		temp->pos.x = temp->x * s->editor->space;
		temp->pos.y = temp->y * s->editor->space;
		if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
			ft_choose_draw_vertex(s, temp, pos);
		temp = temp->next;
	}
	set_player(s);
	if (s->editor->selected == 1)
		trace_select(s);
}
