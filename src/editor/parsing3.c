#include "doom.h"

int		is_dest_valid(t_main *s, int id)
{
	t_vertex *vertex;

	vertex = s->vertex;
	while (vertex)
	{
		if (vertex->id == id)
			return (1);
		vertex = vertex->next;
	}
	return (0);
}

void	check_map_portals2(t_int *wall)
{
	wall->vtx_dest->vtx_dest = NULL;
	wall->vtx_dest->sct_dest = 0;
	wall->vtx_dest->wall_value = -1;
	wall->vtx_dest->selected = 0;
	wall->vtx_dest = NULL;
	wall->sct_dest = 0;
	wall->wall_value = -1;
	wall->selected = 0;
}

void	check_map_portals(t_main *s)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	i = 0;
	while (sct != NULL)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->vtx_dest != NULL)
			{
				if (!check_walls_lenght(wall->vtx_dest, wall)
				|| wall->vtx_dest->vtx_dest == NULL
				|| wall->vtx_dest->vtx_dest->ptr->id != wall->ptr->id
				|| !is_dest_valid(s, wall->vtx_dest->ptr->id))
					check_map_portals2(wall);
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}

t_int	*get_t_int_from_vertex(t_main *s, int vtx_id)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	while (sct)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->ptr->id == vtx_id)
				return (wall);
			wall = wall->next;
		}
		sct = sct->next;
	}
	return (NULL);
}

void	add_portal_ptr(t_main *s, t_int *wall, int i)
{
	t_sector	*sct;

	sct = s->sector;
	while (sct != NULL)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			wall->sct = sct->id;
			if (wall->wall_value != -1 && wall->vtx_dest == NULL)
			{
				wall->vtx_dest = get_t_int_from_vertex(s, wall->wall_value);
				if (wall->vtx_dest != NULL)
				{
					wall->vtx_dest->vtx_dest = wall;
					wall->vtx_dest->sct_dest = wall->sct;
					wall->sct_dest = wall->vtx_dest->sct;
					wall->vtx_dest->wall_value = wall->ptr->id;
				}
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}
