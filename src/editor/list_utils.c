#include "doom.h"

t_sector	*get_sector_by_id(t_main *s, int id)
{
	t_sector	*tmp_sct;

	tmp_sct = s->sector;
	if(id == 0)
		handle_error(s, SECTOR_ERROR);
	while (tmp_sct->id != id)
		tmp_sct = tmp_sct->next;
	return(tmp_sct);
}

t_vertex	*get_vertex_by_id(t_main *s, int id)
{
	t_vertex	*vtx;

	vtx = s->vertex;
	while (vtx && vtx->id != id)
		vtx = vtx->next;
	return(vtx);
}

t_int	*get_t_int_by_id(t_int *vtx, int id)
{
	t_int	*tmp;
	int		i;

	i = 0;
	tmp = vtx;
	while (i++ < vtx->prev->id && tmp->id != id)
		tmp = tmp->next;
	if (tmp->id == id)
		return(tmp);
	else
		return(NULL);
}

t_int	*get_t_int_by_vertex_id(t_int *vtx, int ptr_id)
{
	t_int	*tmp;
	int		i;

	i = 0;
	tmp = vtx;
	while (i++ < vtx->prev->id && tmp->ptr->id != ptr_id)
		tmp = tmp->next;
	if (tmp->ptr->id == ptr_id)
		return(tmp);
	else
		return(NULL);
}
