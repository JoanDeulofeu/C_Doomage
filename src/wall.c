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
	//	printf("SECTOR [%d]\n", sct->id);
		first_vtx = sct->vertex;
		while (sct->vertex)
		{
	//		printf("VERTEX [%d]\n", sct->vertex->id);
			if (sct->vertex->next != NULL)
			{
	//			printf("1---\n");
				vtx = s->vertex;
				while (sct->vertex->id != vtx->id && vtx->next)
					vtx = vtx->next;
				s->line.x1 = vtx->x;
				s->line.y1 = vtx->y;
	//			printf("line x1 %d | ", s->line.x1);
	//			printf("line y1 %d | ", s->line.y1);
				vtx = s->vertex;
				while (sct->vertex->next->id != vtx->id && vtx->next)
					vtx = vtx->next;
				s->line.x2 = vtx->x;
				s->line.y2 = vtx->y;
	//			printf("line x2 %d | ", s->line.x2);
	//			printf("line y2 %d\n", s->line.y2);
				get_line(s, color);
			}
			else
			{
	//			printf("2---\n");
				vtx = s->vertex;
				while (sct->vertex->id != vtx->id && vtx->next)
					vtx = vtx->next;
				s->line.x1 = vtx->x;
				s->line.y1 = vtx->y;
				vtx = s->vertex;
				while (first_vtx->id != vtx->id && vtx->next)
					vtx = vtx->next;
				s->line.x2 = vtx->x;
				s->line.y2 = vtx->y;
				get_line(s, color);
			}
			sct->vertex = sct->vertex->next;
		}
		sct->vertex = first_vtx;
		sct = sct->next;
	}
	// printf("END");
}
