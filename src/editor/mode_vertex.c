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
			if (wall->value > id)
				wall->value--;
			wall = wall->next;
		}
		if (wall->value > id)
			wall->value--;
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
			if (remove_sector(s, id, 0, 0) == 0)
			{
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

void	move_anchor(t_main *s, int id)
{
	t_vertex	*temp;
	t_pos		ori;
	t_pos		abs;

	temp = NULL;
	if (s->vertex)
		temp = s->vertex;
	ori.x = arround(s->editor->space, s->ft_mouse.x
		- (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, s->ft_mouse.y
		- (s->editor->decal_y % s->editor->space));
	abs = get_abs_pos(s, ori);
	while (temp)
	{
		if (temp->id == id && ft_check_vertex(s, abs.x, abs.y))
		{
			temp->pos = ori;
			temp->x = abs.x;
			temp->y = abs.y;
			temp->m_pos.x = temp->x * METRE;
			temp->m_pos.y = temp->y * METRE;
			printf("ptr id = %d\n", temp->id);
			check_map_portals(s);
			return ;
		}
		if (temp)
			temp = temp->next;
	}
}

void	create_anchor(t_main *s, t_pos ori)
{
	t_vertex *vtx;

	vtx = s->vertex;
	ori = get_abs_pos(s, ori);
	while (vtx->next != NULL)
		vtx = vtx->next;
	if (vtx->id < 500)
		ft_add_vertex(s, ori.x, ori.y);
	else
		printf("Error: Trop de vertex.\n");
}

void	draw_anchor(t_main *s, t_pos ori, Uint32 color)
{
	t_dpos		init;
	t_dpos		dest;
	short		size;

	size = s->editor->anchor_size;
	init.x = ori.x - size;
	init.y = ori.y - size;
	dest.x = ori.x + size;
	dest.y = ori.y + size;
	draw_rect(s->sdl->editor, init, dest, color);
}

int		ft_check_wall_lenght(t_sector *sct)
{
	t_int		*wall;
	int			i;
	int			stop;
	t_pos		vtx1;
	t_pos		vtx2;
	int			dist;

	i = 0;
	wall = sct->vertex;
	stop = wall->prev->id;
	while (i++ < stop)
	{
		vtx1.x = wall->ptr->x * METRE;
		vtx1.y = wall->ptr->y * METRE;
		vtx2.x = wall->next->ptr->x * METRE;
		vtx2.y = wall->next->ptr->y * METRE;
		if ((dist = ft_dist_t_pos(vtx1, vtx2)) > 2000)
			return (1);
		wall = wall->next;
	}
	return (0);
}

void	ft_check_move_vertex_validity(t_main *s, int id)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;
	int			stop;
	t_pos		abs;

	sct = s->sector;
	while (sct)
	{
		wall = sct->vertex;
		i = 1;
		stop = wall->prev->id + 1;
		while (i++ < stop)
		{
			if (wall->ptr->id == id)
			{
				if (ft_check_wall_that_intersect(s, sct) || ft_check_wall_lenght(sct))
				{
					wall->ptr->pos = s->save_coord_vtx;
					abs = get_abs_pos(s, s->save_coord_vtx);
					wall->ptr->x = abs.x;
					wall->ptr->y = abs.y;
					wall->ptr->m_pos.x = wall->ptr->x * METRE;
					wall->ptr->m_pos.y = wall->ptr->y * METRE;
				}
				s->save_coord_vtx.x = 0;
				s->save_coord_vtx.y = 0;
				return ;
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}
