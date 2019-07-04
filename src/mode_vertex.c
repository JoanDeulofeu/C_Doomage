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

void	remove_anchor(t_main *s, int id)
{
	t_vertex	*temp;

	temp = s->vertex;
	while (temp)
	{
		if (temp->id == id)
		{
			remove_sector(s, id, 0, 0);
			update_anchor_list(s, temp);
			free(temp);
			return;
		}
			temp = temp->next;
	}
}

void	set_selected(t_main *s, t_pos ori, char color)
{
	t_vertex	*temp;

	temp = s->vertex;
	ori = get_abs_pos(s, ori);
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y && color == 2)
		{
			temp->selected = color;
			return;
		}
		if (temp->x == ori.x && temp->y == ori.y && color == 1)
		{
			temp->selected = color;
			return;
		}
		if (temp->selected != 0 && color == 0)
		{
			temp->selected = color;
			return;
		}
		temp = temp->next;
	}
}

void	ft_reset_color_vertex(t_main *s)
{
	t_vertex	*tmp;

	tmp = s->vertex;
	while (tmp)
	{
		tmp->selected = 0;
		tmp = tmp->next;
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
	while (temp)
	{
		if (temp->id == id)
		{
			ori.x = arround(s->editor->space, s->ft_mouse.x
				- (s->editor->decal_x % s->editor->space));
			ori.y = arround(s->editor->space, s->ft_mouse.y
				- (s->editor->decal_y % s->editor->space));
			temp->pos = ori;
			abs = get_abs_pos(s, ori);
			temp->x = abs.x;
			temp->y = abs.y;
			return;
		}
		if (temp)
			temp = temp->next;
	}
}

void	create_anchor(t_main *s, t_pos ori)
{
	ori = get_abs_pos(s, ori);
	ft_add_vertex(s, ori.x, ori.y);
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
