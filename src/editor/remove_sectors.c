/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_sectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:55:32 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 12:58:04 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector	*update_sector_walls(t_main *s, t_int *tmp_vtx,
		t_sector *tmp_sct, int sector_id)
{
	int		i;

	while (tmp_sct)
	{
		i = 0;
		tmp_vtx = tmp_sct->vertex;
		while (i++ < tmp_sct->vertex->prev->id)
		{
			if (tmp_vtx->sct_dest == sector_id)
			{
				tmp_vtx->sct_dest = 0;
				tmp_vtx->wall_value = -1;
				tmp_vtx->vtx_dest = NULL;
				tmp_vtx->selected = 0;
			}
			tmp_vtx = tmp_vtx->next;
		}
		tmp_sct = tmp_sct->next;
	}
	tmp_sct = s->sector;
	return (tmp_sct);
}

t_int		*free_sector_struct(t_sector *temp_sector)
{
	t_int		*temp_vertex;
	t_int		*temp_vertex2;
	t_lsprite	*temp_list;
	t_lsprite	*temp_list2;
	int			i;

	i = 0;
	temp_vertex = temp_sector->vertex;
	temp_vertex2 = NULL;
	temp_list = temp_sector->liste;
	while (i++ < temp_sector->vertex->prev->id)
	{
		temp_vertex2 = temp_vertex;
		temp_vertex = temp_vertex->next;
		ft_memdel((void **)&temp_vertex2);
	}
	while (temp_list)
	{
		temp_list2 = temp_list;
		temp_list = temp_list->next;
		ft_memdel((void **)&temp_list2);
	}
	return (temp_vertex);
}

t_sector	*update_sector_list(t_main *s, t_sector *temp_sector)
{
	t_sector	*temp_sector2;

	temp_sector2 = NULL;
	if (temp_sector->prev && temp_sector->next)
	{
		temp_sector->prev->next = temp_sector->next;
		temp_sector->next->prev = temp_sector->prev;
	}
	else if (temp_sector->prev && !temp_sector->next)
		temp_sector->prev->next = NULL;
	else if (!temp_sector->prev && temp_sector->next)
	{
		s->sector = temp_sector->next;
		s->sector->prev = NULL;
	}
	else if (!temp_sector->prev && !temp_sector->next)
		s->sector = NULL;
	temp_sector2 = temp_sector;
	temp_sector = s->sector;
	ft_memdel((void **)&temp_sector2);
	return (temp_sector);
}

int			remove_sector_content(t_main *s,
			t_sector **tmp_sct, t_int **tmp_vtx)
{
	int sct_id;

	sct_id = (**tmp_sct).id;
	if (ft_is_in_sector(s, s->player.m_pos) == sct_id)
		return (0);
	while ((*tmp_sct)->liste)
		remove_sprite(s, (*tmp_sct)->liste->sprite->id);
	*tmp_vtx = free_sector_struct(*tmp_sct);
	*tmp_sct = update_sector_list(s, *tmp_sct);
	*tmp_sct = update_sector_walls(s, *tmp_vtx, *tmp_sct, sct_id);
	return (1);
}

int			remove_sector(t_main *s, int id, int del)
{
	t_sector	*tmp_sct;
	t_int		*tmp_vtx;
	int			i;

	tmp_sct = s->sector;
	while (tmp_sct)
	{
		i = 0;
		tmp_vtx = tmp_sct->vertex;
		del = 0;
		while (i++ < tmp_sct->vertex->prev->id)
		{
			if (tmp_vtx->ptr->id == id)
			{
				if (!(del = remove_sector_content(s, &tmp_sct, &tmp_vtx)))
					return (0);
				break ;
			}
			else
				tmp_vtx = tmp_vtx->next;
		}
		if (tmp_sct && !del)
			tmp_sct = tmp_sct->next;
	}
	return (1);
}
