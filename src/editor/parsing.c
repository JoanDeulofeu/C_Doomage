#include "doom.h"

// void	add_portal_ptr(t_main *s)
// {
// 	t_sector	*sct;
// 	t_int		*wall;
// 	int			i;
//
// 	sct = s->sector;
// 	wall = sct->vertex;
// 	while (sct != NULL)
// 	{
// 		i = 0;
// 		while (i++ < sct->vertex->prev->id)
// 		{
// 			if (wall->sct_dest != 0)
// 				if (!check_walls_lenght(s, wall->vtx_dest, wall))
// 				{
// 					wall->vtx_dest = get_t_int_by_id(get_sector_by_id(s, wall->sct_dest)->vertex);
// 				}
// 			wall = wall->next;
// 		}
// 		sct = sct->next;
// 	}
// }

void	check_map_portals(t_main *s)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	wall = sct->vertex;
	while (sct != NULL)
	{
		i = 0;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->vtx_dest != NULL)
				if (!check_walls_lenght(s, wall->vtx_dest, wall))
				{
					wall->vtx_dest->vtx_dest = NULL;
					wall->vtx_dest->sct_dest = 0;
					wall->vtx_dest->wall_value = -1;
					wall->vtx_dest = NULL;
					wall->sct_dest = 0;
					wall->wall_value = -1;
				}
			wall = wall->next;
		}
		sct = sct->next;
	}
}

void	ft_norm_parse_sector(t_main *s, char *line, t_sector *tmp, int i)
{
	int		size_line;
	int		value;

	size_line = ft_strlen(line);
	value = 0;
	while (line[i] != '|') //fill des vecteurs dans le secteur
	{
		value = ft_atoi(&line[i]);
		ft_add_intarray(s, tmp, value);
		i += ft_longlen(value) + 1;
	}
	i += 2;
	put_wall_value(tmp, line, i);
}

int			ft_parse_sector(t_main *s, char *line)
{
	t_sector	*tmp;
	int			i;
	int			floor;
	int			ceiling;

	i = 7;
	floor = ft_atoi(&line[i]);
	i += ft_longlen(floor) + 1;
	ceiling = ft_atoi(&line[i]);
	tmp = ft_add_sector(s, floor, ceiling);
	while (line[i] != '|')
		i++;
	ft_norm_parse_sector(s, line, tmp, i + 2);
	return (0);
}

int		ft_parsing(t_main *s, int x, int y, int fd)
{
	int		size_line;
	char	*line;
	int		i;

	fd = open("map.map", O_RDWR);
	while (get_next_line(fd, &line) > 0)
	{
		size_line = ft_strlen(line);
		if (line[0] == 'v')
		{
			y = ft_atoi(&line[7]);
			i = 10;
			while (i < size_line)
			{
				x = ft_atoi(&line[i]);
				ft_add_vertex(s, x, y);
				i += ft_longlen(x) + 1;
			}
		}
		else if (line[0] == 's')
			ft_parse_sector(s, line);
		ft_strdel(&line);
	}
	// ft_test_chainlist(s);
	ft_strdel(&line);
	check_map_portals(s);
	return (0);
}
