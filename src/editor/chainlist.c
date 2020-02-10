/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:27:30 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/10 17:43:54 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_int		*ft_add_intarray2(t_main *s, t_sector *sector, t_int *tmp2,
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
