/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainlist2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:28:32 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 13:50:31 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			ft_check_vertex(t_main *s, int x, int y)
{
	t_vertex	*tmp;

	tmp = s->vertex;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void		ft_add_vertex2(t_main *s, int x, int y, t_vertex *tmp)
{
	tmp->next = NULL;
	tmp->pos.x = x * s->editor->space;
	tmp->pos.y = y * s->editor->space;
	tmp->x = x;
	tmp->y = y;
	tmp->m_pos.x = x * METRE;
	tmp->m_pos.y = y * METRE;
	tmp->selec = 0;
	tmp->selected = 0;
}

int			ft_add_vertex(t_main *s, int x, int y, t_vertex *tmp)
{
	tmp = s->vertex;
	if (s->vertex == NULL)
	{
		if (!(s->vertex = (t_vertex*)malloc(sizeof(t_vertex))))
			handle_error(s, MALLOC_ERROR);
		ft_bzero((void *)s->vertex, sizeof(t_vertex));
		tmp = s->vertex;
		tmp->prev = NULL;
	}
	else
	{
		if (!(ft_check_vertex(s, x, y)))
			return (-1);
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_vertex*)malloc(sizeof(t_vertex))))
			handle_error(s, MALLOC_ERROR);
		ft_bzero((void *)tmp->next, sizeof(tmp->next));
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	tmp->id = tmp->prev ? tmp->prev->id + 1 : 1;
	ft_add_vertex2(s, x, y, tmp);
	return (0);
}

t_sector	*ft_add_sector(t_main *s, int floor, int ceiling, t_sector *tmp)
{
	tmp = s->sector;
	if (s->sector == NULL)
	{
		if (!(s->sector = (t_sector*)malloc(sizeof(t_sector))))
			handle_error(s, MALLOC_ERROR);
		ft_bzero(s->sector, sizeof(t_sector));
		tmp = s->sector;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_sector*)malloc(sizeof(t_sector))))
			handle_error(s, MALLOC_ERROR);
		ft_bzero((void *)tmp->next, sizeof(t_sector));
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp->prev)
		tmp->id = 1;
	else
		tmp->id = tmp->prev->id + 1;
	tmp->floor = floor;
	tmp->ceiling = ceiling;
	return (tmp);
}
