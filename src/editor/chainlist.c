#include "doom.h"

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
	handle_error(s, 0);
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
			if (value == wall->value)
				return (1);
			wall = wall->next;
		}
		sct = sct->next;
	}
	return (0);
}

t_int			*ft_add_intarray2(t_main *s, t_sector *sector, t_int *tmp2,
int part)
{
	t_int	*tmp;

	tmp = NULL;
	if (part)
	{
		if (!(sector->vertex = (t_int*)malloc(sizeof(t_int))))
			handle_error(s, MALLOC_ERROR);
		ft_bzero((void *)sector->vertex, sizeof(t_int));
		sector->vertex->id = 1;
		sector->vertex->prev = sector->vertex;
		sector->vertex->next = sector->vertex;
		tmp = sector->vertex;
	}
	else
	{
		tmp2->wall_value = -1;
		tmp2->sct = sector->id;
		tmp2->vtx_dest = NULL;
		tmp2->tex_nb = 1;
		tmp2->image = s->editor->all_texture.image[tmp2->tex_nb];
		return (tmp2);
	}
	return (tmp);
}

int			ft_add_intarray(t_main *s, t_sector *sector, int value, t_int *tmp)
{
	t_int	*tmp2;

	if (ft_check_vtx_used(s, value))
		return (-1);
	if (!tmp)
		tmp = ft_add_intarray2(s, sector, NULL, 1);
	else
	{
		if (!(tmp = (t_int*)malloc(sizeof(t_int))))
			handle_error(s, MALLOC_ERROR);
		ft_bzero((void *)tmp, sizeof(t_int));
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
	tmp->value = value;
	tmp->ptr = ft_find_vertex_ptr(s, value);
	tmp = ft_add_intarray2(s, sector, tmp, 0);
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
					printf("--  vertex m_pos = x(%.2f) y(%.2f)\n",i_tmp->ptr->m_pos.x, i_tmp->ptr->m_pos.y);
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
