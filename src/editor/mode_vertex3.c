/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_vertex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:00:47 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 22:00:53 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_pos	ft_get_ori_move_anchor(t_main *s)
{
	t_pos		ori;

	ori.x = arround(s->editor->space, s->ft_mouse.x
		- (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, s->ft_mouse.y
		- (s->editor->decal_y % s->editor->space));
	return (ori);
}

void	ft_sector_eat_another(t_main *s, t_sector *sct, int sct_id)
{
	t_int	*wall;
	int		i;

	if (sct_id == 0)
		return ;
	while (sct)
	{
		if (sct->id == sct_id)
		{
			sct = sct->next;
			continue;
		}
		wall = sct->vertex;
		i = 0;
		while (i++ < sct->vertex->prev->id)
		{
			if (ft_is_in_sector(s, wall->ptr->m_pos) == sct_id)
			{
				remove_sector(s, wall->value, 0, s->sector);
				ft_putstr("Sector delete: sector is in another\n");
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}

void	move_anchor(t_main *s, int id, int ftiis, t_vertex *temp)
{
	t_pos		ori;
	t_pos		abs;
	t_dpos		mouse;

	ori = ft_get_ori_move_anchor(s);
	abs = get_abs_pos(s, ori);
	mouse.x = abs.x * METRE;
	mouse.y = abs.y * METRE;
	ftiis = fiis(s, mouse, vtx_is_in_sct(s, id), s->sector);
	while (temp)
	{
		if (temp->id == id && ft_check_vertex(s, abs.x, abs.y)
		&& (ftiis == 0 || ftiis == vtx_is_in_sct(s, id)))
		{
			temp->pos = ori;
			temp->x = abs.x;
			temp->y = abs.y;
			temp->m_pos.x = temp->x * METRE;
			temp->m_pos.y = temp->y * METRE;
			check_map_portals(s);
			return ;
		}
		temp = temp->next;
	}
}
