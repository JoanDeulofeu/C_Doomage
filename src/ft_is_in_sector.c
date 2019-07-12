#include "doom.h"

int		ft_is_in_segment(t_dpos coord, t_dpos begin, t_dpos end)
{
	double	tmp;

	// printf("COORD (%.0f , %.0f)     BEGIN_SEG (%.0f , %.0f)  END_SEG (%.0f , %.0f)\n", round(coord.x), round(coord.y), round(begin.x) , round(begin.y) , round(end.x), round(end.y));
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
	// printf("COORD (%.0f , %.0f)     BEGIN_SEG (%.0f , %.0f)  END_SEG (%.0f , %.0f)\n", round(coord.x), round(coord.y), round(begin.x) , round(begin.y) , round(end.x), round(end.y));
	if (round(coord.x) < round(begin.x) || round(coord.x) > round(end.x))
		return (0);
	if (round(coord.y) < round(begin.y) || round(coord.y) > round(end.y))
		return (0);
	return (1);
}

int		ft_go_through_point(t_dpos begin, t_dpos end, t_dpos coord)
{
	if (round(coord.x) == begin.x && round(coord.y) == begin.y){
		// printf("1) COORD (%.0f , %.0f)     BEGIN_SEG (%.0f , %.0f)  END_SEG (%.0f , %.0f)\n", (coord.x), (coord.y), (begin.x) , (begin.y) , (end.x), (end.y));
		return (1);
	}
	if (round(coord.x) == end.x && round(coord.y) == end.y){
		// printf("1) COORD (%.0f , %.0f)     BEGIN_SEG (%.0f , %.0f)  END_SEG (%.0f , %.0f)\n", (coord.x), (coord.y), (begin.x) , (begin.y) , (end.x), (end.y));
		return (1);
	}
	return (0);
}

int		ft_go_through_point2(t_dpos begin, t_dpos end, t_dpos coord)
{
	if (round(coord.x) == begin.x && round(coord.y) == begin.y){
		// printf("2) COORD (%.0f , %.0f)     BEGIN_SEG (%.0f , %.0f)  END_SEG (%.0f , %.0f)\n", (coord.x), (coord.y), (begin.x) , (begin.y) , (end.x), (end.y));
		return (1);
	}
	if (round(coord.x) == end.x && round(coord.y) == end.y){
		// printf("2) COORD (%.0f , %.0f)     BEGIN_SEG (%.0f , %.0f)  END_SEG (%.0f , %.0f)\n", (coord.x), (coord.y), (begin.x) , (begin.y) , (end.x), (end.y));
		return (1);
	}
	return (0);
}

double		ft_find_leading_coef(t_dpos begin, t_dpos end)
{
	double	a;

	if ((begin.x - end.x) == 0)
	{
		// printf("\033[32m beginx = %f    endx = %f\033[0m\n", begin.x, end.x);
		return (-999935168.0);
	}
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
		// printf("lol\n");
		coord.x = p_l1.x;
		mid = fabs(begin_l2.y - p_l2.y) / 2;
		coord.y = begin_l2.y < p_l2.y ? begin_l2.y + mid : p_l2.y + mid;
		// coord.y = p_l2.y;
		// printf("mid = %f    cx = %f / cy = %f\n",mid, coord.x, coord.y);
	}
	else if (l2.a == -999935168.0)
	{
		// printf("lol2\n");
		coord.x = p_l2.x;
		coord.y = p_l1.y;
	}
	else
	{
		coord.x = (l2.b - l1.b) / (l1.a - l2.a);
		// printf("coord.x = (%f - %f) * (%f - %f)\n",l2.b,l1.b,l1.a,l2.a);
		coord.y = l1.a * coord.x + l1.b;
		// printf("coord.y = %f * %f + %f\n",l1.a,coord.x,l1.b);
	}
	return (coord);
}

int		ft_find_intersection(t_dpos	begin_l1, t_dpos end_l1, t_dpos begin_l2, t_dpos end_l2) // l1 est un mur, l2 le rayon
{
	t_abpos	l1;
	t_abpos	l2;
	t_dpos	coord;

	//x = a / y = b
	l1.a = ft_find_leading_coef(begin_l1, end_l1);
	l2.a = ft_find_leading_coef(begin_l2, end_l2);
	l1.b = ft_find_ordered_in_origin(begin_l1, l1.a);
	l2.b = ft_find_ordered_in_origin(begin_l2, l2.a);
	coord = ft_find_coord(l1, l2, end_l1, end_l2, begin_l2);

	// printf("\nbegin_l1(%.0f, %.0f), end_l1(%.0f, %.0f), begin_l2(%.0f, %.0f), end_l2(%.0f, %.0f)\n",begin_l1.x, begin_l1.y, end_l1.x, end_l1.y, begin_l2.x, begin_l2.y, end_l2.x, end_l2.y);
	// printf("coord (%.0f, %.0f)\n\n", coord.x, coord.y);

	if (coord.x > INT_MAX || coord.y > INT_MAX || coord.x < INT_MIN || coord.y < INT_MIN)
		return (0);
	if (ft_go_through_point(begin_l1, end_l1, coord))
	{
		// printf("ptdr1\n");
		return (-1);
	}
	// if (ft_go_through_point2(begin_l2, end_l2, coord))
	// {
	// 	printf("ptdr2\n");
	// 	return (-1);
	// }
	if (!(ft_is_in_segment(coord, begin_l1, end_l1)))
	{
		// printf("out seg 1\n\n\n\n");
		return (0);
	}
	if (!(ft_is_in_segment(coord, begin_l2, end_l2)))
	{
		// printf("out seg 2\n\n\n\n");
		return (0);
	}
	// printf(" ----------- IN ----------- \n\n\n\n");
	return (1);
}

int		ft_is_in_sector(t_main *s, t_pos position)
{
	printf("entree\n");
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
	while (sct) // chaque secteur
	{
		count = 0;
		point_1.y += next_test;
		next_test = 0;
		s_vtx = sct->vertex;
		while (s_vtx->next) // chaque vecteur du secteur
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
			// printf("\033[32m seg1x=%f   mousex=%f\033[0m\n",seg1.x, point_2.x);
			intersect = ft_find_intersection(seg1, seg2, point_1, point_2);
			if (intersect == -1)
			{
				next_test += 10;
				// printf("\033[33m---------NEXT TEST-------p2(%f)-\033[0m\n", point_1.y);
				// sleep(1);
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
		count += ft_find_intersection(seg1, seg2, point_1, point_2);
		// printf("count = %d\n=-=-=-=-=-=-=-=-=-=\n", count);
		if (count % 2 == 1)
			return (sct->id);
		if (intersect != -1)
			sct = sct->next;
		else
		{
			next_test += 10;
			// printf("\033[33m---------NEXT TEST-------p2(%f)-\033[0m\n", point_1.y);
			// sleep(1);
		}
	}
	printf("sortie\n");
	return (0);
}
