#include "doom.h"

int		ft_check_other_sector_wall_intersect(t_main *s, t_sector *sct, t_sector *sct_in_check)
{
	t_int		*wall;
	t_int		*wall_in_check;
	int			wic_i;
	int			wic_stop;
	int			w_i;
	int			w_stop;
	t_4dpos		pos;

	wall_in_check = sct_in_check->vertex;
	wic_i = wall_in_check->id;
	wic_stop = wall_in_check->prev->id + 1;
	while (wic_i++ < wic_stop)
	{
		wall = sct->vertex;
		w_i = wall->id;
		w_stop = wall->prev->id + 1;
		while (w_i++ < w_stop)
		{
			pos.pos1 = wall_in_check->ptr->m_pos;
			pos.pos2 = wall_in_check->next->ptr->m_pos;
			pos.pos3 = wall->ptr->m_pos;
			pos.pos4 = wall->next->ptr->m_pos;
			if ((ft_find_intersection(s, pos, 1)) > 0)
				return (1);
			wall = wall->next;
		}
		wall_in_check = wall_in_check->next;
	}
	return (0);
}

int		ft_check_inside_sector_wall_intersect(t_main *s, t_sector *sct)
{
	t_int		*wall;
	t_int		*wall_in_check;
	int			wic_i;
	int			wic_stop;
	int			w_i;
	t_4dpos		pos;

	if (sct->vertex->prev->id < 4)
		return (0);
	wall_in_check = sct->vertex;
	w_i = wall_in_check->id;
	wic_i = w_i;
	wic_stop = wall_in_check->prev->id + 1;
	while (wic_i++ < wic_stop)
	{
		wall = wall_in_check->next->next;
		w_i = 1;
		while (w_i++ < wall_in_check->prev->id)
		{
			pos.pos1 = wall_in_check->ptr->m_pos;
			pos.pos2 = wall_in_check->next->ptr->m_pos;
			pos.pos3 = wall->ptr->m_pos;
			pos.pos4 = wall->next->ptr->m_pos;
			if ((ft_find_intersection(s, pos, 1)) > 0)
				return (1);
			wall = wall->next;
		}
		wall_in_check = wall_in_check->next;
	}
	return (0);
}

int		ft_check_wall_that_intersect(t_main *s, t_sector *sct_in_check)
{
	t_sector	*sct;

	sct = s->sector;
	while (sct)
	{
		if (sct->id == sct_in_check->id)
		{
			if (ft_check_inside_sector_wall_intersect(s, sct_in_check))
				return (1);
			sct = sct->next;
			continue;
		}
		if (ft_check_other_sector_wall_intersect(s, sct, sct_in_check))
			return (1);
		sct = sct->next;
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
