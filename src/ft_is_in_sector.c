#include "doom.h"

int		ft_is_in_segment(t_dpos coord, t_dpos begin, t_dpos end)
{
	double	tmp;

	if (begin.x > end.x) //yohann elle est ou la fonction ft_swap_double batard???? #I HATE YOU
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
	if (round(coord.x) < round(begin.x) + 1 || round(coord.x) > round(end.x) - 1)
		return (0);
	if (round(coord.y) < round(begin.y) + 1 || round(coord.y) > round(end.y) - 1)
		return (0);
	return (1);
}

double		ft_find_leading_coef(t_dpos begin, t_dpos end)
{
	double	a;


	if ((begin.x - end.x) == 0)
	// {
		// printf("\033[32m beginx = %f    endx = %f\033[0m\n", begin.x, end.x);
		return (FLT_MAX);
	// }
	a = (begin.y - end.y) / (begin.x - end.x);
	return (a);
}

double		ft_find_ordered_in_origin(t_dpos point, double a)
{
	double	b;

	b = point.y - (a * point.x);
	return (b);
}

t_dpos		ft_find_coord(t_abpos l1, t_abpos l2, t_dpos p_l1, t_dpos p_l2)
{
	t_dpos	coord;

	if (l1.a == FLT_MAX)
	{
		// printf("lol\n");
		coord.x = p_l1.x;
		coord.y = p_l2.y;
	}
	else if (l2.a == FLT_MAX)
	{
		// printf("lol\n");
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
	coord = ft_find_coord(l1, l2, end_l1, end_l2);

	// printf("\n\n\nbegin_l1(%.0f, %.0f), end_l1(%.0f, %.0f), begin_l2(%.0f, %.0f), end_l2(%.0f, %.0f)\n",begin_l1.x, begin_l1.y, end_l1.x, end_l1.y, begin_l2.x, begin_l2.y, end_l2.x, end_l2.y);
	// printf("coord (%.0f, %.0f)\n\n", coord.x, coord.y);

	if (coord.x > 2147483647 || coord.y > 2147483647)
		return (0);
	if (!(ft_is_in_segment(coord, begin_l1, end_l1)))
	{
		// printf("out seg 1\n");
		return (0);
	}
	if (!(ft_is_in_segment(coord, begin_l2, end_l2)))
	{
		// printf("out seg 2\n");
		return (0);
	}
	// printf(" ----------- IN ----------- \n");
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
	t_dpos		point_1;
	t_dpos		point_2;

	sct = s->sector;
	point_2 = ft_pos_to_dpos(position);
	point_1.x = point_2.x - 1000;
	point_1.y = point_2.y;
	while (sct) // chaque secteur
	{
		count = 0;
		s_vtx = sct->vertex;
		while (s_vtx->next) // chaque vecteur du secteur
		{
			vtx = s->vertex;
			id = s_vtx->value;
			while (vtx->id != id && vtx->next)
				vtx = vtx->next;
			seg1.x = vtx->x * s->editor->space;
			seg1.y = vtx->y * s->editor->space;

			vtx = s->vertex;
			id = s_vtx->next->value;
			while (vtx->id != id && vtx->next)
				vtx = vtx->next;
			seg2.x = vtx->x * s->editor->space;
			seg2.y = vtx->y * s->editor->space;
			// printf("\033[32m seg1x=%f   mousex=%f\033[0m\n",seg1.x, point_2.x);
			count += ft_find_intersection(seg1, seg2, point_1, point_2);
			s_vtx = s_vtx->next;
		}

		vtx = s->vertex;
		id = s_vtx->value;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		seg1.x = vtx->x * s->editor->space;
		seg1.y = vtx->y * s->editor->space;

		s_vtx = sct->vertex;
		vtx = s->vertex;
		id = s_vtx->value;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		seg2.x = vtx->x * s->editor->space;
		seg2.y = vtx->y * s->editor->space;
		count += ft_find_intersection(seg1, seg2, point_1, point_2);
		// printf("count = %d\n=-=-=-=-=-=-=-=-=-=\n", count);
		if (count % 2 == 1)
			return (sct->id);
		sct = sct->next;
	}
	return (0);
}
