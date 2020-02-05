/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:22:08 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/05 16:22:09 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int			ft_go_through_point(t_dpos begin, t_dpos coord)
{
	if (round(coord.x) == begin.x && round(coord.y) == begin.y)
		return (1);
	return (0);
}

double		ft_find_leading_coef(t_dpos begin, t_dpos end)
{
	double	a;

	if ((begin.x - end.x) == 0)
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

int			ft_find_intersection(t_main *s, t_4dpos pos, char visu)
{
	t_abpos	l1;
	t_abpos	l2;
	t_dpos	crd;

	l1.a = ft_find_leading_coef(pos.pos1, pos.pos2);
	l2.a = ft_find_leading_coef(pos.pos3, pos.pos4);
	l1.b = ft_find_ordered_in_origin(pos.pos1, l1.a);
	l2.b = ft_find_ordered_in_origin(pos.pos3, l2.a);
	crd = ft_find_coord(l1, l2);
	s->tmp_intersect.x = crd.x;
	s->tmp_intersect.y = crd.y;
	if (crd.x > INT_MAX || crd.y > INT_MAX
		|| crd.x < INT_MIN || crd.y < INT_MIN)
		return (0);
	if (visu == 0 && ft_go_through_point(pos.pos1, crd))
		return (-1);
	if (!(ft_is_in_segment(crd, pos.pos1, pos.pos2)))
		return (0);
	if (!(ft_is_in_segment(crd, pos.pos3, pos.pos4)))
		return (0);
	return (sqrt(powf(pos.pos4.x - crd.x, 2) + powf(pos.pos4.y - crd.y, 2)));
}
