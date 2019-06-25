#include "doom.h"

//RAPPEL tmp est egale au bon secteur(s->sector), celui que l'on veut remplir)
int			ft_parse_sector(t_main *s, char *line, int size_line)
{
	t_sector	*tmp;
	int			i;
	int			value;
	int			floor;
	int			ceiling;

	i = 7;
	floor = ft_atoi(&line[i]);
	i += ft_longlen(floor) + 1;
	ceiling = ft_atoi(&line[i]);
	tmp = ft_add_sector(s, floor, ceiling);
	while (line[i] != '|')
		i++;
	i += 2;
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
	return (0);
}

int		ft_parsing(t_main *s)
{
	int		fd;
	int		x;
	int		y;
	int		size_line;
	char	*line;
	int		i;

	fd = open("map.map", O_RDWR);
	while (get_next_line(fd, &line) > 0)
	{
		size_line = ft_strlen(line);
		// printf("test = %c\n", line[0]);
		if (line[0] == 'v')
		{
			y = ft_atoi(&line[7]);
			i = 9;
			while (i < size_line)
			{
				x = ft_atoi(&line[i]);
				ft_add_vertex(s, x, y);
				// printf("y %d | x %d | i %d\n", y, x, i);
				i += ft_longlen(x) + 1;
			}
		}
		else if (line[0] == 's')
		{
			ft_parse_sector(s, line, size_line);
		}
	}
	ft_test_chainlist(s);
	return (0);
}
