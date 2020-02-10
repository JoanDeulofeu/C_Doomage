/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_portals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:38:17 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 14:14:53 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	remove_portal(t_main *s)
{
	t_int		*wall;
	t_sector	*sector;
	int			i;
	int			sct_id;

	i = 0;
	if ((sct_id = get_nearest_sector(s, s->ft_mouse)) == 0)
		return ;
	else
		sector = get_sector_by_id(s, sct_id);
	wall = sector->vertex;
	while (i++ < sector->vertex->prev->id)
	{
		if (check_between_wall(s, wall, s->ft_mouse) && wall->vtx_dest)
		{
			wall->vtx_dest->vtx_dest = NULL;
			wall->vtx_dest->sct_dest = 0;
			wall->vtx_dest->wall_value = -1;
			wall->vtx_dest = NULL;
			wall->sct_dest = 0;
			wall->wall_value = -1;
			break ;
		}
		wall = wall->next;
	}
}

int		get_smallest_diff(t_pos mouse, t_pos pos1, t_pos pos2)
{
	int		diffx1;
	int		diffx2;
	int		diffy1;
	int		diffy2;

	diffx1 = mouse.x > pos1.x ? mouse.x - pos1.x : pos1.x - mouse.x;
	diffx2 = mouse.x > pos2.x ? mouse.x - pos2.x : pos2.x - mouse.x;
	diffy1 = mouse.y > pos1.y ? mouse.y - pos1.y : pos1.y - mouse.y;
	diffy2 = mouse.y > pos2.y ? mouse.y - pos2.y : pos2.y - mouse.y;
	return (diffx1 + diffx2 + diffy1 + diffy2);
}

void	edit_portal(t_main *s)
{
	t_sector	*sct;
	t_int		*wall;

	if (s->editor->portal_temp == 0)
	{
		if (s->editor->over_sector == 0 || s->editor->over_portal == 0)
			return ;
		sct = get_sector_by_id(s, s->editor->over_sector);
		wall = get_t_int_by_id(sct->vertex, s->editor->over_portal);
		wall->selected = 2;
		s->editor->portal_temp = 1;
		s->editor->wall = wall;
	}
	else if (s->editor->portal_temp == 1 && s->editor->wall && s->editor->wall2)
	{
		if (s->editor->wall2->selected == 3)
			create_struct_portals(s);
		check_map_portals(s);
	}
	else
		reset_temp_portals(s);
}
