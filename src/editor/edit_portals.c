#include "doom.h"

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
		if (s->editor->wall)
			s->editor->wall->selected = 0;
		s->editor->wall = NULL;
		if (s->editor->wall2)
			s->editor->wall2->selected = 0;
		s->editor->wall2 = NULL;
		// tmp_sct = tmp_sct->next;
	// }
}

void create_struct_portals(t_main *s)
{
		t_int *wall1;
		t_int *wall2;
		t_sector *sct1;
		t_sector *sct2;

		sct1 = get_sector_by_id(s, s->editor->over_sector);
		sct2 = get_sector_by_id(s, s->editor->over_sector2);

		wall1 = get_t_int_by_id(sct1->vertex, s->editor->wall->id);
		wall2 = get_t_int_by_id(sct2->vertex, s->editor->wall2->id);

		wall1->wall_value = s->editor->wall2->ptr->id;
		wall2->wall_value = s->editor->wall->ptr->id;
		wall1->sct_dest = sct2->id;
		wall2->sct_dest = sct1->id;
		// wall1->ptr = s->editor->wall2->ptr;
		// wall2->ptr = s->editor->wall->ptr;
		reset_temp_portals(s);
		ft_test_chainlist(s);
		// printf("wall1->id = %d et wall1->value = %d\n", wall1->id, wall1->value);
		//modifier structure pour in et out
}

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

int		check_between_wall(t_int *wall, t_pos mouse)
{
	t_pos		begin;
	t_pos		end;
	char		bool_x;
	char		bool_y;

	begin = wall->ptr->pos;
	end = wall->next->ptr->pos;
	bool_x = 0;
	bool_y = 0;
	if (begin.x > end.x && mouse.x <= begin.x && mouse.x >= end.x)
		bool_x = 1;
	else if (begin.x < end.x && mouse.x >= begin.x && mouse.x <= end.x)
		bool_x = 1;
	if (begin.y > end.y && mouse.y <= begin.y && mouse.y >= end.y)
		bool_y = 1;
	else if (begin.y < end.y && mouse.y >= begin.y && mouse.y <= end.y)
		bool_y = 1;
	if (bool_x && bool_y)
		return (1);
	else
		return (0);

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
	t_pos		mouse;
	Uint32		color;
	int			i;
	int			box;

	box = -5;
	new_pos.x = 0;
	new_pos.y = 0;
	i = 0;
	mouse.x = s->ft_mouse.x +box;
	while (mouse.x <= (s->ft_mouse.x -box))
	{
		mouse.y = s->ft_mouse.y +box;

		while (mouse.y <= (s->ft_mouse.y -box))
		{
			color = get_pixel_color(s->sdl->editor, mouse.x, mouse.y);
			//set_pixel(s->sdl->editor, BLUE, mouse);

			if (color == COLOR_WALL)
			{
				id = get_nearest_sector(s, s->ft_mouse, &new_pos);
				if (id == 0)
					return ;
				sector  = get_sector_by_id(s, id);
				wall = sector->vertex;
				beg = wall->ptr->pos;
				end = wall->ptr->next->pos;

				wall_save = wall;
				while (i++ < sector->vertex->prev->id)
				{
						if (check_between_wall(wall, mouse))
						{
							wall_save = wall;
							break;
						}
						wall = wall->next;
				}
				s->editor->over_portal = wall_save->id;
				if (s->editor->wall == NULL)
				{
					// printf ("true\n");
					s->editor->wall = wall_save;
					s->editor->over_sector = sector->id;
				}
				else if (s->editor->wall != wall_save)
				{
					// printf ("s->editor->wall != wall_save\n");
					s->editor->wall2 = wall_save;
					s->editor->over_sector2 = sector->id;
				}
				if (s->editor->wall2 != NULL && s->editor->over_sector != 0
					&& s->editor->over_sector2 != 0 && check_walls_lenght(s->editor->wall, wall_save))
				{
					wall_save->selected = 3;
				}
				else if (s->editor->wall2 != NULL)
					wall_save->selected = 4;

				return  ;
			}
			mouse.y+=1;
		}
		mouse.x +=1;
	}
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
	}
	else
		reset_temp_portals(s);
}
