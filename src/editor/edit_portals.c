#include "doom.h"

int	check_pos(t_main *s, int x, int y, t_pos *new_pos)
{
	int		id;
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	if (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT)
		return (0);
	*new_pos = pos;
	id = ft_is_in_sector(s, pos);
	return (id);
}



int	get_nearest_sector(t_main *s, t_pos pos, t_pos *new_pos)
{
		int i;
		int id;

		i = 0;
		id = 0;
		while (i < 10)
		{
			if ((id = check_pos(s, pos.x + i, pos.y, new_pos)) != 0)
				return (id);
			if ((id = check_pos(s, pos.x - i, pos.y, new_pos)) != 0)
				return (id);
			if ((id = check_pos(s, pos.x, pos.y + i, new_pos)) != 0)
				return (id);
			if ((id = check_pos(s, pos.x, pos.y - i, new_pos)) != 0)
				return (id);
			i++;
		}
		return (id);
}

void reset_temp_portals(t_main *s)
{
	t_sector *tmp_sct;

	tmp_sct = s->sector;
	// while (tmp_sct != NULL)
	// {
		s->editor->over_portal= 0;
		s->editor->over_portal= 0;
		s->editor->over_sector = 0;
		s->editor->over_sector2 = 0;
		s->editor->portal_temp = 0;
		s->editor->wall = NULL;
		s->editor->wall2 = NULL;
		// tmp_sct = tmp_sct->next;
	// }
}

int		get_smallest_diff(t_pos mouse, t_pos pos1, t_pos pos2)
{
	int diffx1;
	int diffx2;
	int diffy1;
	int diffy2;

	diffx1 = mouse.x > pos1.x ? mouse.x - pos1.x : pos1.x - mouse.x;
	diffx2 = mouse.x > pos2.x ? mouse.x - pos2.x : pos2.x - mouse.x;
	diffy1 = mouse.y > pos1.y ? mouse.y - pos1.y : pos1.y - mouse.y;
	diffy2 = mouse.y > pos2.y ? mouse.y - pos2.y : pos2.y - mouse.y;
	// return (min(min(diffx1, diffx2), min(diffy1, diffy2)));
	return (diffx1 + diffx2 + diffy1 + diffy2);
}

void	change_over_wall(t_main *s)
{
	t_sector	*sector;
	int			id;
	t_int		*wall;
	t_pos		beg;
	t_pos		end;
	t_pos		new_pos;
	t_int		*wall_save;
	t_pos		save;
	int diff1;
	int diff2;
	t_pos mouse;
	Uint32 color;

	new_pos.x = 0;
	new_pos.y = 0;
	color = get_pixel_color(s->sdl->editor, s->ft_mouse.x, s->ft_mouse.y);

		if (color == COLOR_WALL)
		{
			// printf("id %d\n", id);
			mouse.x = s->ft_mouse.x;
			mouse.y = s->ft_mouse.y;
			id = get_nearest_sector(s, s->ft_mouse, &new_pos);
			// id = ft_is_in_sector(s, s->ft_mouse);
			if (id == 0)
				return ;
			sector  = get_sector_by_id(s, id);
			wall = sector->vertex;
			beg = wall->ptr->pos;
			end = wall->ptr->next->pos;

			wall_save = wall;
			diff1 = get_smallest_diff(mouse, wall->ptr->pos, wall->next->ptr->pos);
			while (wall != NULL)
			{
					if (wall->next == NULL)
					{
						end = sector->vertex->ptr->pos;
					}
					else
					{
						end = wall->next->ptr->pos;
					}
					diff2 = get_smallest_diff(mouse, wall->ptr->pos, end);
					if (diff2 < diff1)
					{
						wall_save = wall;
						diff1 = diff2;
					}
					wall = wall->next;
					// printf("prochain mur = %d\n", wall->id);
			}
			s->editor->over_portal = wall_save->id;
			if (s->editor->wall == NULL)
			{
				s->editor->wall = wall_save;
				s->editor->over_sector = sector->id;
			}
			else
			{
				s->editor->wall2 = wall_save;
				s->editor->over_sector2 = sector->id;
			}
			if (s->editor->wall2 && check_walls_lenght(s, s->editor->wall, wall_save))
			{
				wall_save->selected = 3;
			}
		}
}

void	edit_portal(t_main *s)
{
	t_sector *sct;
	t_int			*wall;


	if (s->editor->over_portal != 0)
	{
		sct = get_sector_by_id(s, s->editor->over_sector);
		wall = get_t_int_by_id(sct->vertex, s->editor->over_portal);
		wall->selected = 2;
		s->editor->portal_temp = 1;
		s->editor->wall = wall;
	}
	else
	{
		if (s->editor->wall != NULL)
			{
				s->editor->wall->selected = 0;
				s->editor->wall = NULL;
			}
	}
}
