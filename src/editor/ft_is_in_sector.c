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

int			ft_is_in_sector(t_main *s, t_dpos position)
{
	t_sector	*sct;
	t_int		*wall;
	t_dpos		seg1;
	t_dpos		seg2;
	int			count;
	long		save_dist;
	long		tmp_dist;
	int			next_test;
	t_dpos		point_1;
	t_dpos		point_2;
	int			n_sector;
	int			dist_sector;
	int			i;

	sct = s->sector;
	n_sector = 0;
	dist_sector = 0;
	tmp_dist = LONG_MAX;
	save_dist = LONG_MAX;
	next_test = 0;
	point_2 = position;
	point_1.x = point_2.x - 10000;
	point_1.y = point_2.y + 10;
	//debug
	// printf("BEGIN =-=-=-=-=-=-=-=-=\n");
	// s->line.x1 = ft_dpos_to_pos(to_edi_coord(s, point_1)).x;
	// s->line.y1 = ft_dpos_to_pos(to_edi_coord(s, point_1)).y;
	// s->line.x2 = ft_dpos_to_pos(to_edi_coord(s, point_2)).x;
	// s->line.y2 = ft_dpos_to_pos(to_edi_coord(s, point_2)).y;
	// get_line(s, S_YELLOW, 1);
	//debug
	while (sct)
	{
		// printf("--- test sector %d ---\n", sct->id);
		i = 0;
		count = 0;
		wall = sct->vertex;
		point_1.y += next_test;
		next_test = 0;
		// printf("while ---\n");
		while (i++ < sct->vertex->prev->id)
		{
			seg1.x = wall->ptr->x * METRE;
			seg1.y = wall->ptr->y * METRE;
			seg2.x = wall->next->ptr->x * METRE;
			seg2.y = wall->next->ptr->y * METRE;
			if ((point_2.x == seg1.x && point_2.y == seg1.y)
				|| (point_2.x == seg2.x && point_2.y == seg2.y))
				return (0);
			if (sct->id == 9)
				// printf("sct 9 - coord de test: seg1(%.1f, %.1f), seg2(%.1f, %.1f), point_1(%.1f, %.1f), point_2(%.1f, %.1f)\n", seg1.x, seg1.y, seg2.x, seg2.y, point_1.x, point_1.y, point_2.x, point_2.y);
			dist_sector = ft_find_intersection(s, seg1, seg2, point_1, point_2, 0);
			if (dist_sector == -1)
			{
				next_test = 10;
				// printf("BREAK\n");
				break;
			}
			if (dist_sector > 0)
			{
				if (tmp_dist > dist_sector)
					tmp_dist = dist_sector;
				count++;
			}
			wall = wall->next;
			// printf("count = %d\n", count);
		}
		// printf("end ---\n");
		if (dist_sector == -1)
			continue;
		if (count % 2 == 1)
			// printf("new dist = %ld\n", tmp_dist);
		if (count % 2 == 1 && save_dist > tmp_dist)
		{
			n_sector = sct->id;
			save_dist = tmp_dist;
			// printf("sector %d save\n", sct->id);
			// printf("dist save = %ld\n", tmp_dist);
		}
		sct = sct->next;
	}
	// printf("END =-=-=-=-=-=-=-=-=-=\n\n\n");
	return (n_sector);
}
