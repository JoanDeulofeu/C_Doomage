/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_portals2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:38:29 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 17:39:49 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		reset_temp_portals(t_main *s)
{
	s->editor->over_portal = 0;
	s->editor->over_sector = 0;
	s->editor->over_sector2 = 0;
	s->editor->portal_temp = 0;
	if (s->editor->wall)
		s->editor->wall->selected = 0;
	s->editor->wall = NULL;
	if (s->editor->wall2)
		s->editor->wall2->selected = 0;
	s->editor->wall2 = NULL;
}

void		create_struct_portals(t_main *s)
{
	t_int		*wall1;
	t_int		*wall2;
	t_sector	*sct1;
	t_sector	*sct2;

	sct1 = get_sector_by_id(s, s->editor->over_sector);
	sct2 = get_sector_by_id(s, s->editor->over_sector2);
	wall1 = get_t_int_by_id(sct1->vertex, s->editor->wall->id);
	wall2 = get_t_int_by_id(sct2->vertex, s->editor->wall2->id);
	wall1->wall_value = s->editor->wall2->ptr->id;
	wall2->wall_value = s->editor->wall->ptr->id;
	wall1->sct_dest = sct2->id;
	wall2->sct_dest = sct1->id;
	wall1->vtx_dest = wall2;
	wall2->vtx_dest = wall1;
	reset_temp_portals(s);
}

int			check_pos(t_main *s, int x, int y)
{
	int		id;
	t_pos	pos;
	t_dpos	test;

	pos.x = x;
	pos.y = y;
	if (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT)
		return (0);
	test = get_abs_r_pos(s, pos);
	test.x *= METRE;
	test.y *= METRE;
	id = ft_is_in_sector(s, test);
	return (id);
}

int			get_nearest_sector(t_main *s, t_pos pos)
{
	int		i;
	int		id;

	i = 0;
	id = 0;
	while (i < 10)
	{
		if ((id = check_pos(s, pos.x + i, pos.y)) != 0)
			return (id);
		if ((id = check_pos(s, pos.x - i, pos.y)) != 0)
			return (id);
		if ((id = check_pos(s, pos.x, pos.y + i)) != 0)
			return (id);
		if ((id = check_pos(s, pos.x, pos.y - i)) != 0)
			return (id);
		i++;
	}
	return (id);
}

int			check_between_wall(t_main *s, t_int *wall, t_pos mouse)
{
	t_pos		begin;
	t_pos		end;
	char		bool_x;
	char		bool_y;

	begin.x = wall->ptr->pos.x + s->editor->decal_x;
	begin.y = wall->ptr->pos.y + s->editor->decal_y;
	end.x = wall->next->ptr->pos.x + s->editor->decal_x;
	end.y = wall->next->ptr->pos.y + s->editor->decal_y;
	bool_x = 0;
	bool_y = 0;
	if (begin.x >= end.x && mouse.x <= begin.x && mouse.x >= end.x)
		bool_x = 1;
	else if (begin.x <= end.x && mouse.x >= begin.x && mouse.x <= end.x)
		bool_x = 1;
	if (begin.y >= end.y && mouse.y <= begin.y && mouse.y >= end.y)
		bool_y = 1;
	else if (begin.y <= end.y && mouse.y >= begin.y && mouse.y <= end.y)
		bool_y = 1;
	if (bool_x && bool_y)
		return (1);
	else
		return (0);
}
