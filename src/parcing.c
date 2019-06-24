#include "doom.h"

int		ft_add_vertex(t_main *s, int x, int y)
{
	t_vertex	*tmp;

	tmp = s->vertex;
	if (s->vertex == NULL)
	{
		if (!(s->vertex = (t_vertex*)malloc(sizeof(t_vertex))))
			handle_error(s, MALLOC_ERROR);
		s->vertex->prev = NULL;
		tmp = s->vertex;
		tmp->id = 1;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_vertex*)malloc(sizeof(t_vertex))))
			handle_error(s, MALLOC_ERROR);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->id = tmp->prev->id + 1;
	}
	tmp->next = NULL;
	tmp->x = x;
	tmp->y = y;
	return (0);
}

int		ft_parcing(t_main *s)
{
	(void)s;
	int		fd;
	int		x;
	int		y;
	int		size_line;
	char	*line;
	int		i;

	fd = open("map.map", O_RDWR);
	while ((SDL_PollEvent(&(s->sdl->event))) && get_next_line(fd, &line))
	{
		size_line = ft_strlen(line);
		if (line[0] == 'v')
		{
			y = ft_atoi(&line[7]);
			i = 9;
			while (i < size_line)
			{
				x = ft_atoi(&line[i]);
				ft_add_vertex(s, x, y);
				// printf("y %d | x %d | i %d\n", y, x, i);
				i += ft_nbrlen(x) + 1;
			}
		}
	}
	return (0);
}
