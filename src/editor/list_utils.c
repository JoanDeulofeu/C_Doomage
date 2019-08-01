#include "doom.h"

t_sector	*get_sector_by_id(t_main *s, int id)
{
	t_sector	*tmp_sct;

	tmp_sct = s->sector;
	while (tmp_sct->id != id)
		tmp_sct = tmp_sct->next;
	return(tmp_sct);
}

t_vertex	*get_vertex_by_id(t_main *s, int id)
{
	t_vertex	*vtx;

	vtx = s->vertex;
	while (vtx->id != id)
		vtx = vtx->next;
	return(vtx);
}

t_int	*get_t_int_by_id(t_int *obj, int id)
{
	t_int	*tmp;

	tmp = obj;
	while (tmp->id != id)
		tmp = tmp->next;
	return(tmp);
}
