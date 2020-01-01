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
		s->vertex->selec = 0;
		s->vertex->selected = 0;
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
	tmp->pos.x = x * s->editor->space;
	tmp->pos.y = y * s->editor->space;
	tmp->x = x;
	tmp->y = y;
	tmp->m_pos.x = x * METRE;
	tmp->m_pos.y = y * METRE;
	tmp->selec = 0;
	tmp->selected = 0;

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
	tmp->liste = NULL;
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
	handle_error(s, 0);
	exit(-1);
	return (NULL);
}

int			ft_check_vtx_used(t_main *s, int value)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;
	int			stop;

	sct = s->sector;
	while (sct)
	{
		wall = sct->vertex;
		if (wall == NULL)
		{
			sct = sct->next;
			continue;
		}
		stop = wall->prev->id + 1;
		i = 1;
		while (i++ < stop)
		{
			// printf("Verif value   a creer(%d) - (%d)existante\n", value, wall->value);
			if (value == wall->value)
				return (1);
			wall = wall->next;
		}
		sct = sct->next;
	}
	return (0);
}

int			ft_add_intarray(t_main *s, t_sector *sector, int value)
{
	t_int	*tmp;
	t_int	*tmp2;

	tmp = sector->vertex;
	if (ft_check_vtx_used(s, value))
		return (-1);
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
		while (tmp2->next->id != 1)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
		tmp2->next->id = tmp2->id + 1;
		tmp2->next->prev = tmp2;
		tmp->next = sector->vertex;
		tmp = tmp2->next;
	}
	tmp->ptr = ft_find_vertex_ptr(s, value);
	tmp->value = value;
	tmp->wall_value = -1;
	tmp->selected = 0;
	tmp->sct_dest = 0;
	tmp->sct = sector->id;
	tmp->vtx_dest = NULL;
	tmp->tex_nb = 0;
	tmp->image = s->editor->all_texture.image[tmp->tex_nb]; //temporaire
	return (0);
}

void		ft_test_chainlist(t_main *s)
{
	t_vertex	*v_tmp;
	t_sector	*s_tmp;
	t_int		*i_tmp;
	int			i;
	int 		j;
	t_lsprite	*sp_tmp;

	printf("\n\n\n\033[32m------VERTEX------\033[0m\n");
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

	printf("\033[32m------SECTOR------\033[0m\n");
	if (s->sector != NULL)
	{
		while (s_tmp != NULL)
		{
			j = 0;
			sp_tmp = s_tmp->liste;
			while (sp_tmp)
			{
				j++;
				sp_tmp = sp_tmp->next;
			}
			printf ("\033[31mCe secteur contient %d sprites\n", j);
			printf("\033[36mSector[%d] =  sol %d  |  plafond %d\033[0m\n-------------\n", s_tmp->id, s_tmp->floor, s_tmp->ceiling);
			if (s_tmp->vertex != NULL)
			{
				i = 0;
				i_tmp = s_tmp->vertex;
				while (i < s_tmp->vertex->prev->id)
				{
					printf("--   vertex[%d] = %d\n", i_tmp->id, i_tmp->value);
					printf("--  ptr vertex = %p\n",i_tmp->ptr);
					printf("--  vertex x y = x(%d) y(%d)\n",i_tmp->ptr->x, i_tmp->ptr->y);
					printf("--  vertex pos = x(%d) y(%d)\n",i_tmp->ptr->pos.x, i_tmp->ptr->pos.y);
					if (i_tmp->wall_value != -1)
						printf("\033[33m--     wall[%d] =", i_tmp->id);
					else
						printf("--     wall[%d] =", i_tmp->id);
					printf(" %d \033[0m \n", i_tmp->wall_value);
					printf("--  texture nb = %d \n", i_tmp->tex_nb);
					printf("--  sct actuel = %d\n",i_tmp->sct);
					if (i_tmp->sct_dest != 0)
						printf("--  sector_dest = %d\n",i_tmp->sct_dest);
					i_tmp = i_tmp->next;
					i++;
					printf("-------------\n");
				}
			}
			s_tmp = s_tmp->next;
			printf("\n");
		}
	}
}
