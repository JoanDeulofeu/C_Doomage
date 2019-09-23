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
			if (wall->wall_value != -1 && wall->vtx_dest == NULL)
			{
				wall->vtx_dest = get_t_int_from_vertex(s, wall->wall_value);
				if (wall->vtx_dest != NULL)
				{
					wall->vtx_dest->vtx_dest = wall;
					wall->vtx_dest->sct_dest = wall->sct;
					wall->sct_dest = wall->vtx_dest->sct;
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
				if (!check_walls_lenght(wall->vtx_dest, wall))
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

void		put_wall_value(t_sector *sector, char *line, int i)
{
	t_int	*tmp;

	tmp = sector->vertex;
	if (tmp == NULL)
		return ;
	while (line[i] != '\0')
	{
		tmp->wall_value = ft_atoi(&line[i]);
		i += ft_longlen(tmp->wall_value) + 1;
		i = ft_find_next_number(line, i);
		tmp = tmp->next;
	}
}

int		ft_check_bar(char *str, int i)
{
	while ((str[i] < '0' || str[i] > '9') && str[i] != '|' && str[i] != '\0')
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

void	ft_norm_parse_sector(t_main *s, char *line, t_sector *tmp, int i)
{
	int		value;

	value = 0;
	while (line[i] != '|' && line[i] != '\0')
	{
		value = ft_atoi(&line[i]);
		ft_add_intarray(s, tmp, value);
		i += ft_longlen(value) + 1;
		if (ft_check_bar(line, i))
			break;
		i = ft_find_next_number(line, i);
	}
	if ((i = ft_find_next_number(line, 0)) == -1)
		handle_error(s, MAP_ERROR);
	put_wall_value(tmp, line, i);
}

int			ft_parse_sector(t_main *s, char *line)
{
	t_sector	*tmp;
	int			i;
	int			floor;
	int			ceiling;

	if ((i = ft_find_next_number(line, 0)) == -1)
		handle_error(s, MAP_ERROR);
	floor = ft_atoi(&line[i]);
	i += ft_longlen(floor) + 1;
	ceiling = ft_atoi(&line[i]);
	tmp = ft_add_sector(s, floor, ceiling);
	while (line[i] != '|')
		i++;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	ft_norm_parse_sector(s, line, tmp, i);
	return (0);
}

int		ft_find_next_number(char *str, int i)
{
	while ((str[i] < '0' || str[i] > '9') && str[i] != '\0' && str[i] != '-')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int		ft_parsing(t_main *s, int x, int y, int fd)
{
	char	*line;
	int		i;

	fd = open(s->map_name, O_RDWR);
	if (fd < 1)
		handle_error(s, MAP_ERROR);
	while (get_next_line(fd, &line) > 0)
	{
		if ((i = ft_find_next_number(line, 0)) == -1)
			continue;
		if (line[0] == 'V')
		{
			y = ft_atoi(&line[i]);
			i += ft_longlen(y) + 1;
			x = ft_atoi(&line[i]);
			ft_add_vertex(s, x, y);
		}
		else if (line[0] == 'S')
			ft_parse_sector(s, line);
		else if (line[0] == 'P')
		{
			i = 7;
			s->player.pos.y = ft_atoi(&line[i]);
			i += ft_longlen(s->player.pos.y);
			s->player.pos.x = ft_atoi(&line[i]);
		}
		else if (line[0] == 'A')
		{
			i = 6;
			s->player.angle = ft_atoi(&line[i]);
		}
		ft_strdel(&line);
	}
	// ft_test_chainlist(s);
	ft_strdel(&line);
	add_portal_ptr(s);
	check_map_portals(s);
	// ft_test_chainlist(s);
	return (0);
}
