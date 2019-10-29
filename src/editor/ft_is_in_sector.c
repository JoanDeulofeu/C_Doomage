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

int			ft_find_intersection(t_main *s, t_dpos begin_l1, t_dpos end_l1, t_dpos begin_l2, t_dpos end_l2, char visu)
{
	t_abpos	l1;
	t_abpos	l2;
	t_dpos	coord;

	l1.a = ft_find_leading_coef(begin_l1, end_l1);
	l2.a = ft_find_leading_coef(begin_l2, end_l2);
	l1.b = ft_find_ordered_in_origin(begin_l1, l1.a);
	l2.b = ft_find_ordered_in_origin(begin_l2, l2.a);
	coord = ft_find_coord(l1, l2, end_l1, end_l2, begin_l2);
	s->tmp_intersect.x = coord.x;
	s->tmp_intersect.y = coord.y;
	// printf("coord(%f,%f)\n",coord.x, coord.y);
	if (coord.x > INT_MAX || coord.y > INT_MAX || coord.x < INT_MIN || coord.y < INT_MIN)
	{
		// printf("out 1\n");
		return (0);
	}
	if (visu == 0 && ft_go_through_point(begin_l1, end_l1, coord))
	{
		// printf("out 2\n");
		return (-1);
	}
	if (!(ft_is_in_segment(coord, begin_l1, end_l1)))
	{
		// printf("out 3\n");
		return (0);
	}
	if (!(ft_is_in_segment(coord, begin_l2, end_l2)))
	{
		// printf("out 4\n");
		return (0);
	}
	// printf("IN\n");
	return (sqrt(powf(end_l2.x - coord.x, 2) + powf(end_l2.y - coord.y, 2)));
}

int			ft_is_in_sector(t_main *s, t_pos position)
{
	t_sector	*sct;
	t_int		*wall;
	t_dpos		seg1;
	t_dpos		seg2;
	int			count;
	long		save_dist;
	int			next_test;
	t_dpos		point_1;
	t_dpos		point_2;
	int			n_sector;
	int			dist_sector;
	int			i;

	sct = s->sector;
	n_sector = 0;
	dist_sector = 0;
	save_dist = LONG_MAX;
	next_test = 0;
	point_2 = ft_pos_to_dpos(position);
	point_1.x = point_2.x - 10000;
	point_1.y = point_2.y;
	while (sct)
	{
		i = 0;
		count = 0;
		wall = sct->vertex;
		point_1.y += next_test;
		next_test = 0;
		while (i++ < sct->vertex->prev->id)
		{
			seg1.x = wall->ptr->x * s->editor->space + s->editor->decal_x;
			seg1.y = wall->ptr->y * s->editor->space + s->editor->decal_y;
			seg2.x = wall->next->ptr->x * s->editor->space + s->editor->decal_x;
			seg2.y = wall->next->ptr->y * s->editor->space + s->editor->decal_y;
			if ((point_2.x == seg1.x && point_2.y == seg1.y)
				|| (point_2.x == seg2.x && point_2.y == seg2.y))
				return (0);
			dist_sector = ft_find_intersection(s, seg1, seg2, point_1, point_2, 0);
			if (dist_sector == -1)
			{
				next_test = 10;
				break;
			}
			if (dist_sector > 0)
				count++;
			wall = wall->next;
		}
		if (dist_sector == -1)
			continue;
		if (count % 2 == 1 && save_dist > dist_sector)
		{
			n_sector = sct->id;
			save_dist = dist_sector;
		}
		sct = sct->next;
	}
	return (n_sector);
}
