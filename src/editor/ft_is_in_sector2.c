/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_sector2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:44:27 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 18:22:28 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			check_pos_sector8(t_main *s, t_4dpos pos, t_sector *sct, int res, int sct_id)
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
		if (c.count % 2 == 1 && c.save_dist > c.tmp_dist && sct->id != sct_id)
		{
			res = sct->id;
			c.save_dist = c.tmp_dist;
		}
		sct = sct->next;
	}
	return (res);
}

int			fiis(t_main *s, t_dpos position, int sct_id, t_sector *sct)
{
	t_4dpos		pos;
	t_4dpos		pos2;
	int			n_sector;
	int			n_sector2;

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
	n_sector = check_pos_sector8(s, pos, sct, 0, sct_id);
	n_sector2 = check_pos_sector8(s, pos2, sct, 0, sct_id);
	if (n_sector == n_sector2 && n_sector == sct_id)
		return (sct_id);
	else
		if (n_sector == sct_id)
			return (n_sector2);
		else
			return (n_sector);
}
