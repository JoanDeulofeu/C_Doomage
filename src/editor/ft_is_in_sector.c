/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_sector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:22:19 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 17:44:13 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_dpos		ft_find_coord(t_abpos l1, t_abpos l2)
{
	t_dpos	coord;

	coord.x = (l2.b - l1.b) / (l1.a - l2.a);
	coord.y = l1.a * coord.x + l1.b;
	return (coord);
}

int			check_pos_sector2(t_main *s, t_4dpos *pos, t_check_pos_sector *c)
{
	pos->pos1 = c->wall->ptr->m_pos;
	pos->pos2 = c->wall->next->ptr->m_pos;
	if ((pos->pos4.x == pos->pos1.x && pos->pos4.y == pos->pos1.y)
		|| (pos->pos4.x == pos->pos2.x && pos->pos4.y == pos->pos2.y))
		return (0);
	if ((c->dist_sector = ft_find_intersection(s, *pos, 0)) == -1)
		return (50);
	if (c->dist_sector > 0)
	{
		if (c->tmp_dist > c->dist_sector)
			c->tmp_dist = c->dist_sector;
		c->count++;
	}
	return (0);
}

void		check_pos_sector3(t_sector *sct, t_4dpos *pos,
	t_check_pos_sector *c, int part)
{
	if (part)
	{
		c->dist_sector = 0;
		c->tmp_dist = LONG_MAX;
		c->save_dist = LONG_MAX;
		c->n_test = 0;
	}
	else
	{
		c->i = 0;
		c->count = 0;
		c->wall = sct->vertex->prev;
		pos->pos3.x += c->n_test;
		pos->pos3.y += c->n_test;
		c->n_test = 0;
	}
}

int			check_pos_sector(t_main *s, t_4dpos pos, t_sector *sct, int res)
{
	t_check_pos_sector c;

	check_pos_sector3(sct, &pos, &c, 1);
	while (sct)
	{
		check_pos_sector3(sct, &pos, &c, 0);
		while (c.i++ < sct->vertex->prev->id && (c.wall = c.wall->next) != NULL)
		{
			if ((c.n_test = check_pos_sector2(s, &pos, &c)) == 50)
				break ;
		}
		if (c.dist_sector == -1)
			continue;
		if (c.count % 2 == 1 && c.save_dist > c.tmp_dist)
		{
			res = sct->id;
			c.save_dist = c.tmp_dist;
		}
		sct = sct->next;
	}
	return (res);
}

int			ft_is_in_sector(t_main *s, t_dpos position)
{
	t_sector	*sct;
	t_4dpos		pos;
	t_4dpos		pos2;
	int			n_sector;

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
	if (((n_sector = check_pos_sector(s, pos, sct, 0))
	== check_pos_sector(s, pos2, sct, 0)))
		return (n_sector);
	else
		return (0);
}
