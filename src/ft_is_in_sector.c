#include "doom.h"

int		ft_is_in_segment(t_dpos coord, t_dpos begin, t_dpos end)
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

int		ft_go_through_point(t_dpos begin, t_dpos end, t_dpos coord)
{
	if (round(coord.x) == begin.x && round(coord.y) == begin.y)
		return (1);
	if (round(coord.x) == end.x && round(coord.y) == end.y)
		return (1);
	return (0);
}

double		ft_find_leading_coef(t_dpos begin, t_dpos end)
{
	double	a;

	if ((begin.x - end.x) == 0)
		return (-999935168.0);
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
	float	mid;

	if (l1.a == -999935168.0)
	{
		coord.x = p_l1.x;
		mid = fabs(begin_l2.y - p_l2.y) / 2;
		coord.y = begin_l2.y < p_l2.y ? begin_l2.y + mid : p_l2.y + mid;
	}
	else if (l2.a == -999935168.0)
	{
		coord.x = p_l2.x;
		coord.y = p_l1.y;
	}
	else
	{
		coord.x = (l2.b - l1.b) / (l1.a - l2.a);
		coord.y = l1.a * coord.x + l1.b;
	}
	return (coord);
}

int		ft_find_intersection(t_dpos	begin_l1, t_dpos end_l1, t_dpos begin_l2, t_dpos end_l2)
{
	t_abpos	l1;
	t_abpos	l2;
	t_dpos	coord;

	l1.a = ft_find_leading_coef(begin_l1, end_l1);
	l2.a = ft_find_leading_coef(begin_l2, end_l2);
	l1.b = ft_find_ordered_in_origin(begin_l1, l1.a);
	l2.b = ft_find_ordered_in_origin(begin_l2, l2.a);
	coord = ft_find_coord(l1, l2, end_l1, end_l2, begin_l2);

	if (coord.x > INT_MAX || coord.y > INT_MAX || coord.x < INT_MIN || coord.y < INT_MIN)
		return (0);
	if (ft_go_through_point(begin_l1, end_l1, coord))
		return (-1);
	if (!(ft_is_in_segment(coord, begin_l1, end_l1)))
		return (0);
	if (!(ft_is_in_segment(coord, begin_l2, end_l2)))
		return (0);
	return (1);
}

int		ft_is_in_sector(t_main *s, t_pos position)
{
	t_sector	*sct;
	t_vertex	*vtx;
	t_int		*s_vtx;
	t_dpos		seg1;
	t_dpos		seg2;
	int			id;
	int			count;
	int			intersect;
	int			next_test;
	t_dpos		point_1;
	t_dpos		point_2;

	sct = s->sector;
	intersect = 0;
	next_test = 0;
	point_2 = ft_pos_to_dpos(position);
	point_1.x = point_2.x - 10000;
	point_1.y = point_2.y;
	while (sct)
	{
		count = 0;
		point_1.y += next_test;
		next_test = 0;
		s_vtx = sct->vertex;
		while (s_vtx->next)
		{
			vtx = s->vertex;
			id = s_vtx->value;
			while (vtx->id != id && vtx->next)
				vtx = vtx->next;
			seg1.x = vtx->x * s->editor->space + s->editor->decal_x;
			seg1.y = vtx->y * s->editor->space + s->editor->decal_y;

			vtx = s->vertex;
			id = s_vtx->next->value;
			while (vtx->id != id && vtx->next)
				vtx = vtx->next;
			seg2.x = vtx->x * s->editor->space + s->editor->decal_x;
			seg2.y = vtx->y * s->editor->space + s->editor->decal_y;
			if ((point_2.x == seg1.x && point_2.y == seg1.y)
				|| (point_2.x == seg2.x && point_2.y == seg2.y))
				return (0);
			intersect = ft_find_intersection(seg1, seg2, point_1, point_2);
			if (intersect == -1)
			{
				next_test += 10;
				break;
			}
			count += intersect;
			s_vtx = s_vtx->next;
		}

		if (intersect == -1)
			continue;
		vtx = s->vertex;
		id = s_vtx->value;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		seg1.x = vtx->x * s->editor->space + s->editor->decal_x;
		seg1.y = vtx->y * s->editor->space + s->editor->decal_y;

		s_vtx = sct->vertex;
		vtx = s->vertex;
		id = s_vtx->value;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		seg2.x = vtx->x * s->editor->space + s->editor->decal_x;
		seg2.y = vtx->y * s->editor->space + s->editor->decal_y;
		if ((point_2.x == seg1.x && point_2.y == seg1.y)
			|| (point_2.x == seg2.x && point_2.y == seg2.y))
			return (0);
		count += ft_find_intersection(seg1, seg2, point_1, point_2);
		if (count % 2 == 1)
			return (sct->id);
		if (intersect != -1)
			sct = sct->next;
		else
			next_test += 10;
	}
	return (0);
}
