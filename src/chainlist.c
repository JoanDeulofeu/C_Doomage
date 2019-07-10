#include "doom.h"

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
	tmp->wall = NULL;
	tmp->floor = floor;
	tmp->ceiling = ceiling;
	return (tmp);
}

int			ft_add_intarray(t_main *s, t_sector *sector, int value, int what)
{
	t_int	*tmp;

	tmp = (what == 1 ? sector->vertex : sector->wall);
	if ((what == 1 ? sector->vertex : sector->wall) == NULL)
	{
		if (!(tmp = (t_int*)malloc(sizeof(t_int))))
			handle_error(s, MALLOC_ERROR);
		if (what == 1)
			sector->vertex = tmp;
		else
			sector->wall = tmp;
		tmp->id = 1;
		tmp->prev = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_int*)malloc(sizeof(t_int))))
			handle_error(s, MALLOC_ERROR);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->id = tmp->prev->id + 1;
	}
	tmp->next = NULL;
	tmp->value = value;
	return (0);
}

void	ft_test_chainlist(t_main *s)
{
	t_vertex	*v_tmp;
	t_sector	*s_tmp;
	t_int		*i_tmp;

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
			if (s_tmp->vertex != NULL)
			{
				i_tmp = s_tmp->vertex;
				while (i_tmp->next != NULL)
				{
					printf("--vertex[%d] =", i_tmp->id);
					printf(" %d\n", i_tmp->value);
					i_tmp = i_tmp->next;
				}
				printf("--vertex[%d] =", i_tmp->id);
				printf(" %d\n", i_tmp->value);
			}
			if (s_tmp->wall != NULL)
			{
				i_tmp = s_tmp->wall;
				while (i_tmp->next != NULL)
				{
					printf("--wall[%d] =", i_tmp->id);
					printf(" %d\n", i_tmp->value);
					i_tmp = i_tmp->next;
				}
				printf("--wall[%d] =", i_tmp->id);
				printf(" %d\n\n", i_tmp->value);
			}
			s_tmp = s_tmp->next;
		}
		printf("Sector[%d] =  sol %d  |  plafond %d\n", s_tmp->id, s_tmp->floor, s_tmp->ceiling);
		if (s_tmp->vertex != NULL)
		{
			i_tmp = s_tmp->vertex;
			while (i_tmp->next != NULL)
			{
				printf("--vertex[%d] =", i_tmp->id);
				printf(" %d\n", i_tmp->value);
				i_tmp = i_tmp->next;
			}
			printf("--vertex[%d] =", i_tmp->id);
			printf(" %d\n", i_tmp->value);
		}
		if (s_tmp->wall != NULL)
		{
			i_tmp = s_tmp->wall;
			while (i_tmp->next != NULL)
			{
				printf("--wall[%d] =", i_tmp->id);
				printf(" %d\n", i_tmp->value);
				i_tmp = i_tmp->next;
			}
			printf("--wall[%d] =", i_tmp->id);
			printf(" %d\n\n", i_tmp->value);
		}
	}
}











//da
