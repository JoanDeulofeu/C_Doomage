/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_portals3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:38:22 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 17:38:23 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	change_over_wall3(t_main *s, t_int *wall_save, t_sector *sector)
{
	s->editor->over_portal = wall_save->id;
	if (s->editor->wall == NULL)
	{
		s->editor->wall = wall_save;
		s->editor->over_sector = sector->id;
		s->editor->wall->selected = 2;
	}
	else if (s->editor->wall && s->editor->wall != wall_save)
	{
		s->editor->wall2 = wall_save;
		s->editor->over_sector2 = sector->id;
	}
	if (s->editor->wall2 != NULL && s->editor->over_sector != 0
			&& s->editor->over_sector2 != 0 &&
			check_walls_lenght(s->editor->wall, wall_save))
		wall_save->selected = 3;
	else if (s->editor->wall2 != NULL)
		wall_save->selected = 4;
}

int		change_over_wall2(t_main *s, t_pos mouse)
{
	t_sector	*sector;
	t_int		*wall;
	t_int		*wall_save;
	int			i;

	i = 0;
	if (get_nearest_sector(s, s->ft_mouse) == 0)
		return (1);
	sector = get_sector_by_id(s, get_nearest_sector(s, s->ft_mouse));
	wall = sector->vertex;
	wall_save = NULL;
	while (i++ < sector->vertex->prev->id)
	{
		if (check_between_wall(s, wall, mouse))
		{
			wall_save = wall;
			break ;
		}
		wall = wall->next;
	}
	if (!wall_save)
		return (1);
	change_over_wall3(s, wall_save, sector);
	return (0);
}

void	change_over_wall(t_main *s)
{
	t_pos		mouse;

	mouse.x = s->ft_mouse.x - 5;
	while (mouse.x <= (s->ft_mouse.x + 5))
	{
		mouse.y = s->ft_mouse.y - 5;
		while (mouse.y <= (s->ft_mouse.y + 5))
		{
			if (get_pixel_color(s->sdl->editor, mouse.x, mouse.y) == COLOR_WALL)
			{
				change_over_wall2(s, mouse);
				return ;
			}
			mouse.y += 1;
		}
		mouse.x += 1;
	}
}
