#include "doom.h"

t_sector	*update_sector_walls(t_main *s, t_int *temp_vertex,
			t_sector *temp_sector, int sector_id)
{
	int i;
	while (temp_sector)
	{
		i = 0;
		temp_vertex = temp_sector->vertex;
		while (i++ < temp_sector->vertex->prev->id)
		{
			if (temp_vertex->sct_dest == sector_id)
			{
				temp_vertex->sct_dest = 0;
				temp_vertex->wall_value = -1;
			}
			temp_vertex = temp_vertex->next;
		}
		temp_sector = temp_sector->next;
	}
	temp_sector = s->sector;
	return(temp_sector);
}

t_int		*free_sector_struct(t_sector *temp_sector)
{
	t_int		*temp_vertex;
	t_int		*temp_vertex2;
	int			i;
	int			dest;

	i = 0;
	dest = temp_sector->vertex->prev->id;
	temp_vertex = temp_sector->vertex;
	temp_vertex2 = NULL;
	while (i++ < dest)
	{
		temp_vertex2 = temp_vertex;
		temp_vertex = temp_vertex->next;
		free(temp_vertex2);
	}
	return(temp_vertex);
}

t_sector		*update_sector_list(t_main *s, t_sector *temp_sector)
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
	free(temp_sector2);
	return(temp_sector);

}
void	remove_sector(t_main *s, int id, int del, int sct_id)
{
	t_sector	*tmp_sct;
	t_int			*tmp_vtx;
	int				i;

	tmp_sct = s->sector;
	while (tmp_sct)
	{
		i = 0;
		sct_id = tmp_sct->id;
		tmp_vtx = tmp_sct->vertex;
		del = 0;
		while (i++ < tmp_sct->vertex->prev->id)
		{
			if (tmp_vtx->ptr->id == id)
			{
				tmp_vtx = free_sector_struct(tmp_sct);
				tmp_sct = update_sector_list(s, tmp_sct);
				tmp_sct = update_sector_walls(s, tmp_vtx, tmp_sct, sct_id);
				del = 1;
				break;
			}
			else
				tmp_vtx = tmp_vtx->next;
		}
		if (tmp_sct && !del)
			tmp_sct = tmp_sct->next;
	}
}
