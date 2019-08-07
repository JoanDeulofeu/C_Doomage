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

void	change_over_wall(t_main *s)
{
	t_sector	*sector;
	int			id;
	t_int		*wall;
	t_pos		beg;
	t_pos		end;
	t_pos		new_pos;

	new_pos.x = 0;
	new_pos.y = 0;

	// id = ft_is_in_sector(s, s->ft_mouse);
		// printf ("color wall = %d, color = %d\n", COLOR_WALL, get_pixel_color(s->sdl->editor, s->ft_mouse.x, s->ft_mouse.y));
		// if (COLOR_WALL == get_pixel_color(s->sdl->editor, s->ft_mouse.x, s->ft_mouse.y))
		// 	printf("%d\n", id);

		if (get_pixel_color(s->sdl->editor, s->ft_mouse.x, s->ft_mouse.y) == COLOR_WALL)
		{
			// printf("id %d\n", id);
			id = get_nearest_sector(s, s->ft_mouse, &new_pos);
			if (id == 0)
				return ;
			sector  = get_sector_by_id(s, id);
			printf("sector id = %d\n", sector->id);
			wall = sector->vertex;
			beg = wall->ptr->pos;
			end = wall->ptr->next->pos;
			printf("wall %d\n", wall->id);
			printf("%d\n", new_pos.x);
			while (!ft_is_in_segment(ft_pos_to_dpos(new_pos), ft_pos_to_dpos(beg), ft_pos_to_dpos(end)))
				{
					wall = ft_next_vtx(wall, sector);
					beg = wall->ptr->pos;
					printf("wall %d\n", wall->id);
					if (wall->id == sector->vertex->id)
					{
						printf("test\n");
						return ;
					}

					if (wall->ptr->next == NULL)
					{
						end = sector->vertex->ptr->pos;
					}
					else
					{
						end = wall->ptr->next->pos;
					}

			}
			printf("selected wall = %d\n", wall->id);
			wall->selected = 2;
		}
}

void	edit_portal(t_main *s)
{
	//je regarde si le
}
