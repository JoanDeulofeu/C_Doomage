#include "doom.h"

void	ft_draw_all_wall(t_main *s)
{
	t_vertex	*vtx;
	t_int		*first_vtx;
	t_sector	*sct;
	Uint32		color = 0xff7062FF; //#ff7062


	sct = s->sector;
	while (sct)
	{
		printf("SECTOR [%d]\n", sct->id);
		first_vtx = sct->vertex;
		while (sct->vertex)
		{
			// printf("VERTEX [%d]\n", sct->vertex->id);
			if (sct->vertex->next != NULL)
			{
				// printf("1---\n");
				vtx = s->vertex;
				while (sct->vertex->value != vtx->id && vtx->next)
					vtx = vtx->next;
				printf("mur entre le vertex n%d et ", vtx->id);
				s->line.x1 = vtx->pos.x;
				s->line.y1 = vtx->pos.y;
				// printf("line x1 %d | ", vtx->x);
				// printf("line y1 %d | ", vtx->y);
				vtx = s->vertex;
				while (sct->vertex->next->value != vtx->id)
					vtx = vtx->next;
				printf("n%d\n", vtx->id);
				s->line.x2 = vtx->pos.x;
				s->line.y2 = vtx->pos.y;
				// printf("line x2 %d | ", vtx->x);
				// printf("line y2 %d\n", vtx->y);
				get_line(s, color);
			}
			else
			{
				// printf("2---\n");
				vtx = s->vertex;
				while (sct->vertex->value != vtx->id && vtx->next)
					vtx = vtx->next;
				printf("mur entre le vertex n%d et ", vtx->id);
				s->line.x1 = vtx->pos.x;
				s->line.y1 = vtx->pos.y;
				vtx = s->vertex;
				while (first_vtx->value != vtx->id)
					vtx = vtx->next;
				printf("n%d\n", vtx->id);
				s->line.x2 = vtx->pos.x;
				s->line.y2 = vtx->pos.y;
				get_line(s, color);
			}
			sct->vertex = sct->vertex->next;
		}
		sct->vertex = first_vtx;
		sct = sct->next;
	}
	// printf("END");
}
