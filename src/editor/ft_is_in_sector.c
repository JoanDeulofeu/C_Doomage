#include "doom.h"

int			ft_is_in_segment(t_dpos coord, t_dpos begin, t_dpos end)
{
	double	tmp;

	if (begin.x > end.x)
	{
		tmp = begin.x;
		begin.x = end.x;
		end.x = tmp;
	}
	if (begin.y > end.y)
	{
		tmp = begin.y;
		begin.y = end.y;
		end.y = tmp;
	}
	if (round(coord.x) < round(begin.x) || round(coord.x) > round(end.x))
		return (0);
	if (round(coord.y) < round(begin.y) || round(coord.y) > round(end.y))
		return (0);
	return (1);
}

int			ft_go_through_point(t_dpos begin, t_dpos end, t_dpos coord)
{
	if (round(coord.x) == begin.x && round(coord.y) == begin.y)
		return (1);
	(void)end;
	// if (round(coord.x) == end.x && round(coord.y) == end.y)
	// 	return (1);
	return (0);
}

double		ft_find_leading_coef(t_dpos begin, t_dpos end)
{
	double	a;

	if ((begin.x - end.x) == 0)
		// return (-999935168.0);
		a = (begin.y - end.y) / 0.1;
	else
		a = (begin.y - end.y) / (begin.x - end.x);
	return (a);
}

double		ft_find_ordered_in_origin(t_dpos point, double a)
{
	double	b;

	b = point.y - (a * point.x);
	return (b);
}

t_dpos		ft_find_coord(t_abpos l1, t_abpos l2, t_dpos p_l1, t_dpos p_l2, t_dpos begin_l2)
{
	t_dpos	coord;

	(void)begin_l2;
	(void)p_l1;
	(void)p_l2;
	// float	mid;
	// if (l1.a == -999935168.0)
	// {
	// 	coord.x = p_l1.x;
	// 	mid = fabs(begin_l2.y - p_l2.y) / 2;
	// 	coord.y = begin_l2.y < p_l2.y ? begin_l2.y + mid : p_l2.y + mid;
	// }
	// else if (l2.a == -999935168.0)
	// {
	// 	coord.x = p_l2.x;
	// 	coord.y = p_l1.y;
	// }
	// else
	// {
		coord.x = (l2.b - l1.b) / (l1.a - l2.a);
		coord.y = l1.a * coord.x + l1.b;
	// }
	return (coord);
}

int			ft_find_intersection(t_main *s, t_4dpos pos, char visu)
{
	t_abpos	l1;
	t_abpos	l2;
	t_dpos	crd;

	l1.a = ft_find_leading_coef(pos.pos1, pos.pos2);
	l2.a = ft_find_leading_coef(pos.pos3, pos.pos4);
	l1.b = ft_find_ordered_in_origin(pos.pos1, l1.a);
	l2.b = ft_find_ordered_in_origin(pos.pos3, l2.a);
	crd = ft_find_coord(l1, l2, pos.pos2, pos.pos4, pos.pos3);
	s->tmp_intersect.x = crd.x;
	s->tmp_intersect.y = crd.y;
	if (crd.x > INT_MAX || crd.y > INT_MAX
		|| crd.x < INT_MIN || crd.y < INT_MIN)
		return (0);
	if (visu == 0 && ft_go_through_point(pos.pos1, pos.pos2, crd))
		return (-1);
	if (!(ft_is_in_segment(crd, pos.pos1, pos.pos2)))
		return (0);
	if (!(ft_is_in_segment(crd, pos.pos3, pos.pos4)))
		return (0);
	return (sqrt(powf(pos.pos4.x - crd.x, 2) + powf(pos.pos4.y - crd.y, 2)));
}

int			check_pos_sector(t_main *s, t_4dpos pos, t_sector *sct)
{
		t_int		*wall;
		int			count;
		long		save_dist;
		long		tmp_dist;
		int			next_test;
		int			n_sector;
		int			dist_sector;
		int			i;

		n_sector = 0;
		dist_sector = 0;
		tmp_dist = LONG_MAX;
		save_dist = LONG_MAX;
		next_test = 0;
		while (sct)
		{
			i = 0;
			count = 0;
			wall = sct->vertex;
			pos.pos3.x += next_test;
			pos.pos3.y += next_test;
			next_test = 0;
			// printf("boucle 1\n");
			while (i++ < sct->vertex->prev->id)
			{
				pos.pos1 = wall->ptr->m_pos;
				pos.pos2 = wall->next->ptr->m_pos;
				if ((pos.pos4.x == pos.pos1.x && pos.pos4.y == pos.pos1.y)
					|| (pos.pos4.x == pos.pos2.x && pos.pos4.y == pos.pos2.y))
					return (0);
				dist_sector = ft_find_intersection(s, pos, 0);
				if (dist_sector == -1)
				{
					next_test = 50;
					break;
				}
				if (dist_sector > 0)
				{
					if (tmp_dist > dist_sector)
						tmp_dist = dist_sector;
					count++;
				}
				// printf("sct->prev->id = %d, i = %d\n", sct->vertex->prev->id, i);
				wall = wall->next;
			}
			if (dist_sector == -1)
				continue;
			if (count % 2 == 1 && save_dist > tmp_dist)
			{
				n_sector = sct->id;
				save_dist = tmp_dist;
			}
			sct = sct->next;
		}
		return (n_sector);
}

int			ft_is_in_sector(t_main *s, t_dpos position)
{
	t_sector	*sct;
	// t_int		*wall;
	t_4dpos		pos;
	t_4dpos		pos2;
	// int			count;
	// long		save_dist;
	// long		tmp_dist;
	// int			next_test;
	int			n_sector;
	// int			dist_sector;
	// int			i;

	sct = s->sector;
	pos.pos4 = position;
	pos.pos3.x = pos.pos4.x - 10000;
	pos.pos3.y = pos.pos4.y + 10;
	pos.pos1 = position;
	pos.pos2 = position;
	pos2.pos4 = position;
	pos2.pos3.x = pos.pos4.x + 10000;
	pos2.pos3.y = pos.pos4.y + 10;
	pos2.pos1 = position;
	pos2.pos2 = position;
	if (((n_sector = check_pos_sector(s, pos, sct)) == check_pos_sector(s, pos2, sct)))
	{
		// printf("sector = %d\n", n_sector);
		return (n_sector);
	}
	else
		return(0);
	// while (sct)
	// {
	// 	i = 0;
	// 	count = 0;
	// 	wall = sct->vertex;
	// 	pos.pos3.y += next_test;
	// 	next_test = 0;
	// 	while (i++ < sct->vertex->prev->id)
	// 	{
	// 		pos.pos1 = wall->ptr->m_pos;
	// 		pos.pos2 = wall->next->ptr->m_pos;
	// 		if ((pos.pos4.x == pos.pos1.x && pos.pos4.y == pos.pos1.y)
	// 			|| (pos.pos4.x == pos.pos2.x && pos.pos4.y == pos.pos2.y))
	// 			return (0);
	// 		dist_sector = ft_find_intersection(s, pos, 0);
	// 		if (dist_sector == -1)
	// 		{
	// 			next_test = 10;
	// 			break;
	// 		}
	// 		if (dist_sector > 0)
	// 		{
	// 			if (tmp_dist > dist_sector)
	// 				tmp_dist = dist_sector;
	// 			count++;
	// 		}
	// 		wall = wall->next;
	// 	}
	// 	if (dist_sector == -1)
	// 		continue;
	// 	if (count % 2 == 1 && save_dist > tmp_dist)
	// 	{
	// 		n_sector = sct->id;
	// 		save_dist = tmp_dist;
	// 	}
	// 	sct = sct->next;
	// }
	// return (n_sector);
}
