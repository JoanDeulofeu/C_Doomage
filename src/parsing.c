#include "doom.h"

void	ft_norm_parse_sector(t_main *s, char *line, t_sector *tmp, int i)
{
	int		size_line;
	int		value;

	size_line = ft_strlen(line);
	value = 0;
	while (line[i] != '|') //fill des vecteurs dans le secteur
	{
		value = ft_atoi(&line[i]);
		ft_add_intarray(s, tmp, value, 1);
		i += ft_longlen(value) + 1;
	}
	i += 2;
	while (i < size_line) //fill des wall et portal dans le secteur
	{
		value = ft_atoi(&line[i]);
		ft_add_intarray(s, tmp, value, 2);
		i += ft_longlen(value) + 1;
	}
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
	return (0);
}
