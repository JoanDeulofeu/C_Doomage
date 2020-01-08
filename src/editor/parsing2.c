#include "doom.h"

int		ft_check_sector_norm(t_main *s, t_int *wall, t_int *wall_in_check)
{
	t_4dpos		pos;

	pos.pos1 = wall_in_check->ptr->m_pos;
	pos.pos2 = wall_in_check->next->ptr->m_pos;
	pos.pos3 = wall->ptr->m_pos;
	pos.pos4 = wall->next->ptr->m_pos;
	if ((ft_find_intersection(s, pos, 1)) > 0)
		return (1);
	return (0);
}

int		ft_check_other_sector(t_main *s, t_sector *sct, t_sector *sct_in_check,
int wic_stop)
{
	t_int		*wall;
	t_int		*wall_in_check;
	int			wic_i;
	int			w_i;
	int			w_stop;

	wall_in_check = sct_in_check->vertex;
	wic_i = wall_in_check->id;
	while (wic_i++ < wic_stop)
	{
		wall = sct->vertex;
		w_i = wall->id;
		w_stop = wall->prev->id + 1;
		while (w_i++ < w_stop)
		{
			if (ft_check_sector_norm(s, wall, wall_in_check))
				return (1);
			wall = wall->next;
		}
		wall_in_check = wall_in_check->next;
	}
	return (0);
}

int		ft_check_inside_sector(t_main *s, t_sector *sct, int wic_stop)
{
	t_int		*wall;
	t_int		*wall_in_check;
	int			wic_i;
	int			w_i;

	if (sct->vertex->prev->id < 4)
		return (0);
	wall_in_check = sct->vertex;
	w_i = wall_in_check->id;
	wic_i = w_i;
	while (wic_i++ < wic_stop)
	{
		wall = wall_in_check->next->next;
		w_i = 1;
		while (w_i++ < wall_in_check->prev->id)
		{
			if (ft_check_sector_norm(s, wall, wall_in_check))
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
			if (ft_check_inside_sector(s, sct_in_check,
				sct_in_check->vertex->prev->id + 1))
				return (1);
			sct = sct->next;
			continue;
		}
		if (ft_check_other_sector(s, sct, sct_in_check,
			sct_in_check->vertex->prev->id + 1))
			return (1);
		sct = sct->next;
	}
	return (0);
}
