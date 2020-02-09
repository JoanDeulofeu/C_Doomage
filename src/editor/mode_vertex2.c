/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_vertex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:24:53 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/09 22:06:01 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	update_anchor_list(t_main *s, t_vertex *temp)
{
	if (temp->prev && temp->next)
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	else if (temp->prev && !temp->next)
		temp->prev->next = NULL;
	else if (!temp->prev && temp->next)
	{
		s->vertex = temp->next;
		s->vertex->prev = NULL;
	}
	else if (!temp->prev && !temp->next)
		s->vertex = NULL;
}

void	ft_drag_vextex_id(t_main *s, int id)
{
	t_vertex	*vtx;
	t_sector	*sct;
	t_int		*wall;
	int			wall_end;

	vtx = s->vertex;
	sct = s->sector;
	while (vtx)
	{
		if (vtx->id > id)
			vtx->id--;
		vtx = vtx->next;
	}
	while (sct)
	{
		wall = sct->vertex;
		wall_end = wall->prev->id;
		while (wall->id != wall_end)
		{
			wall->value = (wall->value > id) ? wall->value - 1 : wall->value;
			wall = wall->next;
		}
		wall->value = (wall->value > id) ? wall->value - 1 : wall->value;
		sct = sct->next;
	}
}

void	remove_anchor(t_main *s, int id)
{
	t_vertex	*temp;

	temp = s->vertex;
	while (temp)
	{
		if (temp->id == id)
		{
			if (remove_sector(s, id, 0) == 0)
			{
				if (!s->msg->message)
					ft_create_message(s, 2, 200, "Cannot remove player's sector!");
				return ;
			}
			update_anchor_list(s, temp);
			ft_memdel((void **)&temp);
			ft_drag_vextex_id(s, id);
			return ;
		}
		temp = temp->next;
	}
}

void	remove_selected_anchor(t_main *s)
{
	t_vertex	*v;

	v = s->vertex;
	while (v)
	{
		if (v->selected == 1)
			remove_anchor(s, v->id);
		if (v)
			v = v->next;
	}
}

void	create_anchor(t_main *s, t_pos ori)
{
	t_vertex *vtx;
	t_dpos mouse;

	vtx = s->vertex;
	ori = get_abs_pos(s, ori);
	while (vtx->next != NULL)
		vtx = vtx->next;
	mouse.x = arround(s->editor->space, s->ft_mouse.x
		- (s->editor->decal_x % s->editor->space));
	mouse.y = arround(s->editor->space, s->ft_mouse.y
		- (s->editor->decal_y % s->editor->space));
	if (vtx->id < 500 && ft_is_in_sector(s, mouse) == 0)
		ft_add_vertex(s, ori.x, ori.y, NULL);
}
