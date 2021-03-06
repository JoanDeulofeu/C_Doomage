/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:04:35 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/09 17:58:58 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	sct = ft_add_sector(s, floor, ceiling, NULL);
	while (line[i] != '|')
		i++;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	ft_norm_parse_sector(s, line, sct, i);
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
		handle_error(s, MAP_ERROR);
	if (sct == NULL)
		handle_error(s, MAP_ERROR);
	if (sct->vertex->prev->id < 3)
		handle_error(s, MAP_ERROR);
	if (!ft_is_in_sector(s, s->player.m_pos))
		tp_first_sector(s);
}

int		ft_parsing(t_main *s, int fd)
{
	char	*line;
	int		i;

	fd = open(s->map_name, O_RDWR);
	if (fd < 1)
		handle_error(s, MAP_ERROR);
	while (get_next_line(fd, &line) > 0)
	{
		if ((i = ft_find_next_number(line, 0)) == -1)
		{
			ft_strdel(&line);
			continue;
		}
		if (line[0] == 'V' || line[0] == 'S' || line[0] == 'P'
		|| line[0] == 'E')
			ft_parsing_norm(s, line, i, 0);
		else if (line[0] == 'A')
			s->player.angle = ft_atoi(&line[i]);
		ft_strdel(&line);
	}
	ft_check_parsing_validity(s);
	ft_strdel(&line);
	add_portal_ptr(s, NULL, 0, s->sector);
	check_map_portals(s);
	return (0);
}
