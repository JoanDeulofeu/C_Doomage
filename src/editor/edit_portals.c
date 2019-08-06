#include "doom.h"

int		is_point_on_seg(t_pos point, t_pos beg, t_pos end)
{
	int cross;
	int dotproduct;
	int powlen;

	cross = (point.y - beg.y) * (end.x - beg.x) - (point.x - beg.x) * (end.y - beg.y);
	if (abs(cross) != 0)
	{
		printf("1, point.y(%d) - beg.y(%d) = %d\ncross = %d\n", point.y, beg.y, point.y - beg.y, abs(cross));
		return (0);
	}

	dotproduct = (point.x - beg.x) * (end.x - beg.x) + (point.y - beg.y) * (end.y - beg.y);
	if (dotproduct < 0)
	{
		printf("2\n");
		return (0);
	}

	powlen = pow(end.x - beg.x, 2) - pow(end.x - beg.x, 2);
	if (dotproduct > powlen)
	{
		printf("3\n");
		return (0);
	}
	return (1);

}

void	change_over_wall(t_main *s)
{
	t_sector	*sector;
	int			id;
	t_int		*wall;
	t_pos		beg;
	t_pos		end;

	id = ft_is_in_sector(s, s->ft_mouse);
	if (id != 0)
	{
		if (get_pixel_color(s->sdl->editor, s->ft_mouse.x, s->ft_mouse.y) == COLOR_WALL)
		{
			sector = get_sector_by_id(s, id);
			wall = sector->vertex;
			beg = wall->ptr->pos;
			end = wall->ptr->next->pos;
			while (!is_point_on_seg(s->ft_mouse, beg, end))
			{
				wall = ft_next_vtx(wall, sector);
				// printf("wall %d\n", wall->id);
				if (wall->id == sector->vertex->id)
					return ;
				if (wall->ptr->next == NULL)
				{
					end = sector->vertex->ptr->pos;
				}
				else
				{
					end = wall->ptr->next->pos;
				}

			}
			printf("find one \n");
		}
	}

}

void	edit_portal(t_main *s)
{
	//je regarde si le
}
