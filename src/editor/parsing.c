#include "doom.h"

t_int	*get_t_int_from_vertex(t_main *s, int vtx_id)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	while (sct)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->ptr->id == vtx_id)
				return (wall);
			wall = wall->next;
		}
		sct = sct->next;
	}
	return (NULL);
}

void	add_portal_ptr(t_main *s)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	while (sct != NULL)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			wall->sct = sct->id;
			printf("sct->id = %d\n", sct->id);
			if (wall->wall_value != -1 && wall->vtx_dest == NULL)
			{
				wall->vtx_dest = get_t_int_from_vertex(s, wall->wall_value);
				if (wall->vtx_dest != NULL)
				{
					wall->vtx_dest->vtx_dest = wall;
					wall->vtx_dest->sct_dest = wall->sct;
					wall->vtx_dest->wall_value = wall->ptr->id; //securité
				}
			}
			wall = wall->next;
		}
		sct = sct->next;
	}
}

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
			{
				if (!check_walls_lenght(s, wall->vtx_dest, wall))
				{
					wall->vtx_dest->vtx_dest = NULL;
					wall->vtx_dest->sct_dest = 0;
					wall->vtx_dest->wall_value = -1;
					wall->vtx_dest = NULL;
					wall->sct_dest = 0;
					wall->wall_value = -1;
				}
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

	ft_strdel(&line);
	add_portal_ptr(s);
	check_map_portals(s);
	ft_test_chainlist(s);
	return (0);
}
