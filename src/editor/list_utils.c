/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:00:45 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 18:08:07 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector	*get_sector_by_vertex_id(t_main *s, int id)
{
	t_sector	*sct;
	t_int		*wall;
	int			i;

	sct = s->sector;
	while (sct)
	{
		i = 0;
		wall = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (wall->ptr->id == id)
				return (sct);
			wall = wall->next;
		}
		sct = sct->next;
	}
	return (NULL);
}

t_sector	*get_sector_by_id(t_main *s, int id)
{
	t_sector	*tmp_sct;

	tmp_sct = s->sector;
	if (id == 0)
		handle_error(s, SECTOR_ERROR);
	while (tmp_sct && tmp_sct->id != id)
		tmp_sct = tmp_sct->next;
	if (tmp_sct == NULL || tmp_sct->id != id)
		return (NULL);
	return (tmp_sct);
}

t_vertex	*get_vertex_by_id(t_main *s, int id)
{
	t_vertex	*vtx;

	vtx = s->vertex;
	while (vtx && vtx->id != id)
		vtx = vtx->next;
	return (vtx);
}

t_int		*get_t_int_by_id(t_int *vtx, int id)
{
	t_int	*tmp;
	int		i;

	i = 0;
	tmp = vtx;
	while (i++ < vtx->prev->id && tmp->id != id)
		tmp = tmp->next;
	if (tmp->id == id)
		return (tmp);
	else
		return (NULL);
}

t_int		*get_t_int_by_vertex_id(t_int *vtx, int ptr_id)
{
	t_int	*tmp;
	int		i;

	i = 0;
	if (!vtx)
		return (NULL);
	tmp = vtx;
	while (i++ < vtx->prev->id && tmp->ptr->id != ptr_id)
		tmp = tmp->next;
	if (tmp && tmp->ptr->id == ptr_id)
		return (tmp);
	else
		return (NULL);
}
