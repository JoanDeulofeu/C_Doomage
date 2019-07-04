#include "doom.h"

void	remove_sector(t_main *s, int id)
{
	t_sector	*temp_sector;
	t_sector	*temp_sector2;
	t_int		*temp_vertex;
	t_int		*temp_vertex2;
	int			sector_id;
	int del;

	del = 0;
	sector_id = 0;
	temp_sector = s->sector;
	while (temp_sector)
	{
		sector_id = temp_sector->id;
		temp_vertex = temp_sector->vertex;
		while (temp_vertex)
		{
			if (temp_vertex->value == id)
			{
				temp_vertex = temp_sector->vertex;
				while (temp_vertex)
				{
					temp_vertex2 = temp_vertex;
					temp_vertex = temp_vertex->next;
					free(temp_vertex2);
				}
				temp_vertex = temp_sector->wall;
				while (temp_vertex)
				{
					temp_vertex2 = temp_vertex;
					temp_vertex = temp_vertex->next;
					free(temp_vertex2);
				}
				if (temp_sector->prev && temp_sector->next)
				{
					temp_sector->prev->next = temp_sector->next;
					temp_sector->next->prev = temp_sector->prev;
				}
				else if (temp_sector->prev && !temp_sector->next)
					temp_sector->prev->next = NULL;
				else if (!temp_sector->prev && temp_sector->next)
				{
					s->sector = temp_sector->next;
					s->sector->prev = NULL;
				}

				else if (!temp_sector->prev && !temp_sector->next)
					s->sector = NULL;
				temp_sector2 = temp_sector;
				temp_sector = s->sector;
				free(temp_sector2);
				while (temp_sector)
				{
					temp_vertex = temp_sector->wall;
					while (temp_vertex)
					{
						if (temp_vertex->value == sector_id)
							temp_vertex->value = -1;
						temp_vertex = temp_vertex->next;
					}
					temp_sector = temp_sector->next;
				}
				temp_sector = s->sector;
				del = 1;
				break;
			}
			else
			{
				temp_vertex = temp_vertex->next;
				del = 0;
			}
		}
		if (temp_sector && !del)
			temp_sector = temp_sector->next;
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
			remove_sector(s, id);
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
			free(temp);
			temp = NULL;
			return;
		}
		if (temp)
			temp = temp->next;
	}
}

t_pos	get_abs_pos(t_main *s, t_pos ori)
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

int		anchor_exists(t_main *s, t_pos ori)
{
	t_vertex	*temp;

	temp = s->vertex;
	ori = get_abs_pos(s, ori);
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y)
			return (temp->id);
		temp = temp->next;
	}
	return (0);
}
//
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
