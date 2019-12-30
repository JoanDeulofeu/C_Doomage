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
	while (sct != NULL)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->vtx_dest != NULL)
			{
					// printf("wall->vtx_dest = %d       et wall = %d\n", wall->vtx_dest->value, wall->value);
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

void	put_wall_value(t_sector *sct, char *line, int i)
{
	t_int	*tmp;

	tmp = sct->vertex;
	if (tmp == NULL)
		return ;
	while (line[i] != '\0')
	{
		tmp->wall_value = ft_atoi(&line[i]);
		i += ft_longlen(tmp->wall_value);
		i = ft_find_next_number(line, i);
		if (i == -1)
			return ;
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

void	ft_norm_parse_sector(t_main *s, char *line, t_sector *sct, int i)
{
	int		value;

	value = 0;
	while (line[i] != '|' && line[i] != '\0')
	{
		// printf("chocolat1\n");
		value = ft_atoi(&line[i]);
		// printf("chocolat2\n");
		ft_add_intarray(s, sct, value);
		i += ft_longlen(value) + 1;
		// printf("chocolat3\n");
		if (ft_check_bar(line, i))
			break;
		i = ft_find_next_number(line, i);
		// printf("chocolat4\n");
	}
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
		// printf("chocolat5\n");
	put_wall_value(sct, line, i);
	// printf("chocolat6\n");
}

int		ft_parse_sector(t_main *s, char *line)
{
	t_sector	*sct;
	int			i;
	int			floor;
	int			ceiling;

	if ((i = ft_find_next_number(line, 0)) == -1)
		handle_error(s, MAP_ERROR);
	floor = ft_atoi(&line[i]);
	i += ft_longlen(floor) + 1;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	ceiling = ft_atoi(&line[i]);
	sct = ft_add_sector(s, floor, ceiling);
	// printf("entree1\n");
	while (line[i] != '|')
		i++;
	// printf("sortie1\n");
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
		// printf("entree2\n");
	ft_norm_parse_sector(s, line, sct, i);
	// printf("sortie2\n");
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

int		ft_check_other_sector_wall_intersect(t_main *s, t_sector *sct, t_sector *sct_in_check)
{
	t_int		*wall;
	t_int		*wall_in_check;
	int			wic_i;
	int			wic_stop;
	int			w_i;
	int			w_stop;
	t_dpos		beg1;
	t_dpos		beg2;
	t_dpos		end1;
	t_dpos		end2;

	wall_in_check = sct_in_check->vertex;
	wic_i = wall_in_check->id;
	wic_stop = wall_in_check->prev->id + 1;
	while (wic_i++ < wic_stop)
	{
		wall = sct->vertex;
		w_i = wall->id;
		w_stop = wall->prev->id + 1;
		while (w_i++ < w_stop)
		{
			beg1.x = wall_in_check->ptr->x * METRE;
			beg1.y = wall_in_check->ptr->y * METRE;
			beg2.x = wall_in_check->next->ptr->x * METRE;
			beg2.y = wall_in_check->next->ptr->y * METRE;
			end1.x = wall->ptr->x * METRE;
			end1.y = wall->ptr->y * METRE;
			end2.x = wall->next->ptr->x * METRE;
			end2.y = wall->next->ptr->y * METRE;
			if ((ft_find_intersection(s, beg1, beg2, end1, end2, 1)) > 0)
				return (1);
			wall = wall->next;
		}
		wall_in_check = wall_in_check->next;
	}
	return (0);
}

int		ft_check_inside_sector_wall_intersect(t_main *s, t_sector *sct)
{
	t_int		*wall;
	t_int		*wall_in_check;
	int			wic_i;
	int			wic_stop;
	int			w_i;
	int			w_stop;
	t_dpos		beg1;
	t_dpos		beg2;
	t_dpos		end1;
	t_dpos		end2;

	if (sct->vertex->prev->id < 4) //si le secteur a 3 murs
		return (0);
	wall_in_check = sct->vertex;
	w_i = wall_in_check->id;
	w_stop = wall_in_check->prev->id; //pas de +1 car pas besoin de check le dernier mur
	wic_i = w_i;
	wic_stop = w_stop + 1;
	// printf("\n\nTEST\n");
	while (wic_i++ < wic_stop)
	{
		wall = wall_in_check->next->next;
		w_i = 1;
		// printf("Mur testé n%d", wall_in_check->id);
		while (w_i++ < w_stop)
		{
			beg1.x = wall_in_check->ptr->x * METRE;
			beg1.y = wall_in_check->ptr->y * METRE;
			beg2.x = wall_in_check->next->ptr->x * METRE;
			beg2.y = wall_in_check->next->ptr->y * METRE;
			end1.x = wall->ptr->x * METRE;
			end1.y = wall->ptr->y * METRE;
			end2.x = wall->next->ptr->x * METRE;
			end2.y = wall->next->ptr->y * METRE;
			if ((ft_find_intersection(s, beg1, beg2, end1, end2, 1)) > 0)
				return (1);
			// printf(" avec mur n%d", wall->id);
			wall = wall->next;
		}
		// printf("\n");
		wall_in_check = wall_in_check->next;
	}
	return (0);
}

int		ft_check_wall_that_intersect(t_main *s, t_sector *sct_in_check)
{
	t_sector	*sct;

	sct = s->sector;
	// printf("secteur testé = %d\n", sct_in_check->id);
	while (sct)
	{
		// printf("test\n");
		if (sct->id == sct_in_check->id)
		{
			if (ft_check_inside_sector_wall_intersect(s, sct_in_check))
				return (1);
			sct = sct->next;
			continue;
		}
		if (ft_check_other_sector_wall_intersect(s, sct, sct_in_check))
			return (1);
		sct = sct->next;
	}
	return (0);
}

void	ft_check_validity_last_sector(t_main *s)
{
	t_sector	*sct;
	t_int		*wall;

	sct = s->sector;
	while (sct->next)
		sct = sct->next;
	wall = sct->vertex;
	if (wall->prev->id < 3 || sct->floor == sct->ceiling)
		remove_sector(s, wall->value, 0, 0);
	if (ft_check_wall_that_intersect(s, sct))
		remove_sector(s, wall->value, 0, 0);
	if (ft_check_sector_sens(s, sct))
		remove_sector(s, wall->value, 0, 0);
}

int		ft_how_many_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (str[i] != '\0')
	{
		if (str[i++] == '|')
			pipe++;
	}
	return (pipe);
}

void	ft_check_parsing_validity(t_main *s)
{
	int			i;
	t_vertex	*vtx;
	t_sector	*sct;

	vtx = s->vertex;
	sct = s->sector;
	i = 0;
	while (vtx)
	{
		i++;
		vtx = vtx->next;
	}
	if (i < 3)
	{
		printf("Moins de 3 vtx\n");
		handle_error(s, MAP_ERROR);
	}
	if (sct == NULL)
	{
		printf("Moins de 1 sct\n");
		handle_error(s, MAP_ERROR);
	}
	i = 0;
	if (sct->vertex->prev->id < 3)
	{
		printf("Moins de 3 vtx dans sct1\n");
		handle_error(s, MAP_ERROR);
	}
}

int		ft_parse_ennemi_part2(t_main *s, char *line, int i, t_sprite *sprite)
{
	if (!sprite)
		return (0);
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	sprite->s_angle = (double)ft_atoi(&line[i]);
	i += ft_longlen((int)sprite->s_angle) + 1;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	sprite->name = ft_atoi(&line[i]);
	get_sprite_info_by_name(s, sprite->name, sprite);
	return (0);
}

int		ft_parse_ennemi(t_main *s, char *line)
{
	t_sprite	*sprite;
	t_dpos		pos;
	t_type		type;
	int			i;

	if ((i = ft_find_next_number(line, 0)) == -1)
		handle_error(s, MAP_ERROR);
	type = ft_atoi(&line[i]);
	i += ft_longlen(type) + 1;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	pos.x = ft_atoi(&line[i]);
	i += ft_longlen((int)pos.x) + 1;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	pos.y = ft_atoi(&line[i]);
	i += ft_longlen((int)pos.y) + 1;
	pos.x /= 100;
	pos.y /= 100;
	sprite = create_new_sprite(s, 0, pos);
	ft_parse_ennemi_part2(s, line, i, sprite);
	return (0);
}

int		ft_parsing(t_main *s, int x, int y, int fd)
{
	char	*line;
	int		i;
	int		test;

	fd = open(s->map_name, O_RDWR);
	if (fd < 1)
		handle_error(s, MAP_ERROR);
	while ((test = get_next_line(fd, &line)) > 0)
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
		{
			if (ft_how_many_pipe(line) != 2)
				continue;
			ft_parse_sector(s, line);
			ft_check_validity_last_sector(s);
		}
		else if (line[0] == 'E')
		{
			if (ft_how_many_pipe(line) != 3)
				continue;
			ft_parse_ennemi(s, line);
		}
		else if (line[0] == 'P')
		{
			s->player.r_ori.y = (float)ft_atoi(&line[i]) / METRE;
			i += ft_longlen(s->player.r_pos.y * METRE);
			s->player.r_ori.x = (float)ft_atoi(&line[i]) / METRE;
			s->player.r_pos = s->player.r_ori;
		}
		else if (line[0] == 'A')
		{
			s->player.angle = ft_atoi(&line[i]);
		}
		ft_strdel(&line);
	}
	ft_check_parsing_validity(s);
	ft_strdel(&line);
	add_portal_ptr(s);
	check_map_portals(s);
	return (0);
}
