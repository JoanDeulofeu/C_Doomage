#include "doom.h"

int			ft_check_vertex(t_main *s, int x, int y)
{
	t_vertex	*tmp;

	tmp = s->vertex;
	while (tmp)
	{
		// printf("COMP) tmp.x(%d)  x(%d)    tmp.y(%d)  y(%d)\n",tmp->x, x, tmp->y, y);
		if (tmp->x == x && tmp->y == y)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int			ft_add_vertex(t_main *s, int x, int y)
{
	t_vertex	*tmp;

	tmp = s->vertex;
	if (s->vertex == NULL)
	{
		if (!(s->vertex = (t_vertex*)malloc(sizeof(t_vertex))))
			handle_error(s, MALLOC_ERROR);
		s->vertex->prev = NULL;
		s->vertex->next = NULL;
		tmp = s->vertex;
		tmp->id = 1;
	}
	else
	{
		if (!(ft_check_vertex(s, x, y)))
			return (-1);
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_vertex*)malloc(sizeof(t_vertex))))
			handle_error(s, MALLOC_ERROR);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->id = tmp->prev->id + 1;
	}
	tmp->next = NULL;
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->x = x;
	tmp->y = y;
	return (0);
}

t_sector	*ft_add_sector(t_main *s, int floor, int ceiling)
{
	t_sector	*tmp;

	tmp = s->sector;
	if (s->sector == NULL)
	{
		if (!(s->sector = (t_sector*)malloc(sizeof(t_sector))))
			handle_error(s, MALLOC_ERROR);
		s->sector->prev = NULL;
		tmp = s->sector;
		tmp->id = 1;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_sector*)malloc(sizeof(t_sector))))
			handle_error(s, MALLOC_ERROR);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->id = tmp->prev->id + 1;
	}
	tmp->next = NULL;
	tmp->vertex = NULL;
	tmp->floor = floor;
	tmp->ceiling = ceiling;
	return (tmp);
}

t_vertex	*ft_find_vertex_ptr(t_main *s, int id)
{
	t_vertex	*res;

	res = s->vertex;
	while (res)
	{
		if (res->id == id)
			return (res);
		res = res->next;
	}
	printf("ft_find_vertex_ptr crash\n");
	exit(0); //merde
	return (NULL);
}

void		put_wall_value(t_sector *sector, char *line, int i)
{
	t_int	*tmp;
	int		size_line;

	size_line = ft_strlen(line);
	tmp = sector->vertex;

	if (tmp == NULL)
		return ;
	while (i < size_line) //fill des wall et portal dans le secteur
	{
		tmp->wall_value = ft_atoi(&line[i]);
		i += ft_longlen(tmp->wall_value) + 1;
		tmp = tmp->next;
	}

}

int			ft_add_intarray(t_main *s, t_sector *sector, int value)
{
	t_int	*tmp;
	t_int	*tmp2;

	tmp = sector->vertex;
	if (tmp == NULL)
	{
		if (!(sector->vertex = (t_int*)malloc(sizeof(t_int))))
			handle_error(s, MALLOC_ERROR);
		sector->vertex->id = 1;
		sector->vertex->prev = sector->vertex;
		sector->vertex->next = sector->vertex;
		tmp = sector->vertex;
	}
	else
	{
		if (!(tmp = (t_int*)malloc(sizeof(t_int))))
			handle_error(s, MALLOC_ERROR);
		tmp2 = sector->vertex;
		tmp2->prev = tmp;
		while(tmp2->next->id != 1)
			tmp2 = tmp2->next;

		tmp2->next = tmp;
		tmp2->next->id = tmp2->id + 1;
		tmp2->next->prev = tmp2;
		tmp->next = sector->vertex;
		tmp = tmp2->next;
	}
	tmp->ptr = ft_find_vertex_ptr(s, value);
	tmp->value = value;
	tmp->selected = 0;
	tmp->sct_dest = 0;
	tmp->vtx_dest = NULL;
	return (0);
}

void	ft_test_chainlist(t_main *s)
{
	t_vertex	*v_tmp;
	t_sector	*s_tmp;
	t_int		*i_tmp;
	int			i;

	i = 0;
	printf("------VERTEX------\n");
	v_tmp = s->vertex;
	s_tmp = s->sector;
	if (s->vertex != NULL)
	{
		while (v_tmp->next != NULL)
		{
			printf("Vertex[%d] =   X %d   |   Y %d\n", v_tmp->id, v_tmp->x, v_tmp->y);
			v_tmp = v_tmp->next;
		}
		printf("Vertex[%d] =   X %d   |   Y %d\n\n", v_tmp->id, v_tmp->x, v_tmp->y);
	}

	printf("------SECTOR------\n");
	if (s->sector != NULL)
	{
		while (s_tmp->next != NULL)
		{
			printf("Sector[%d] =  sol %d  |  plafond %d\n", s_tmp->id, s_tmp->floor, s_tmp->ceiling);
			printf("sector->vertex = %p\n", s_tmp->vertex);
			if (s_tmp->vertex != NULL)
			{
				printf("chocloat\n");
				i_tmp = s_tmp->vertex;
				while (i < s_tmp->vertex->prev->id)
				{
					printf("--vertex[%d] =", i_tmp->id);
					printf(" %d\n", i_tmp->value);
					printf("--wall[%d] =", i_tmp->id);
					printf(" %d du secteur %d\n", i_tmp->wall_value, i_tmp->sct_dest);
					i_tmp = i_tmp->next;
					i++;
				}
				printf("--vertex[%d] =", i_tmp->id);
				printf(" %d\n", i_tmp->value);
				printf("--wall[%d] =", i_tmp->id);
				printf(" %d du secteur %d\n", i_tmp->wall_value, i_tmp->sct_dest);
			}
			s_tmp = s_tmp->next;
		}
		printf("Sector[%d] =  sol %d  |  plafond %d\n", s_tmp->id, s_tmp->floor, s_tmp->ceiling);
		if (s_tmp->vertex != NULL)
		{
			i = 0;
			i_tmp = s_tmp->vertex;
			while (i < s_tmp->vertex->prev->id)
			{
				printf("--vertex[%d] =", i_tmp->id);
				printf(" %d\n", i_tmp->value);
				printf("--wall[%d] =", i_tmp->id);
				printf(" %d du secteur %d\n", i_tmp->wall_value, i_tmp->sct_dest);
				i_tmp = i_tmp->next;
				i++;
			}
			printf("--vertex[%d] =", i_tmp->id);
			printf(" %d\n", i_tmp->value);
			printf("--wall[%d] =", i_tmp->id);
			printf(" %d\n", i_tmp->wall_value);
		}
	}
}











//da
