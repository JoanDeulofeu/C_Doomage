#include "doom.h"

void	ft_sector_mode(t_main *s, int x, int y)
{
	t_vertex	*vtx;

	vtx = s->vertex;
	while (vtx)
	{
		if ((x >= vtx->x - s->editor->anchor_size && x <= vtx->x
			+ s->editor->anchor_size) && (y >= vtx->y - s->editor->anchor_size
				&& y <= vtx->y + s->editor->anchor_size))
		{
			
		}
	}
}

void	ft_save_sector_vextex(t_main *s, int id_vtx)
{
	if (s->str_vtx == NULL)
		s->str_vtx = ft_itoa(id_vtx);
	printf("STR_VTX =%s|\n", s->str_vtx);
}

void	ft_draw_all_wall(t_main *s)
{
	t_vertex	*vtx;
	t_int		*first_vtx;
	t_sector	*sct;
	Uint32		color = 0xff7062FF; //#ff7062


	sct = s->sector;
	while (sct)
	{
		first_vtx = sct->vertex;
		while (sct->vertex)
		{
			if (sct->vertex->next != NULL)
			{
				vtx = s->vertex;
				while (sct->vertex->value != vtx->id && vtx->next)
					vtx = vtx->next;
				s->line.x1 = vtx->pos.x;
				s->line.y1 = vtx->pos.y;
				vtx = s->vertex;
				while (sct->vertex->next->value != vtx->id)
					vtx = vtx->next;
				s->line.x2 = vtx->pos.x;
				s->line.y2 = vtx->pos.y;
				get_line(s, color);
			}
			else
			{
				vtx = s->vertex;
				while (sct->vertex->value != vtx->id && vtx->next)
					vtx = vtx->next;
				s->line.x1 = vtx->pos.x;
				s->line.y1 = vtx->pos.y;
				vtx = s->vertex;
				while (first_vtx->value != vtx->id)
					vtx = vtx->next;
				s->line.x2 = vtx->pos.x;
				s->line.y2 = vtx->pos.y;
				get_line(s, color);
			}
			sct->vertex = sct->vertex->next;
		}
		sct->vertex = first_vtx;
		sct = sct->next;
	}
}
