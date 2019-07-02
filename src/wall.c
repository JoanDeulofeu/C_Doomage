#include "doom.h"

int		ft_howmany_char(char *str, char c)
{
	int i = -1;
	int res = 0;

	while (str[++i] != '\0')
	{
		if (str[i] == c)
			res++;
	}
	return (res);
}

void	ft_save_sector_vextex(t_main *s, int id_vtx)
{
	char	*tmp;
	char	*space;

	tmp = ft_itoa(id_vtx);
	if (s->str_vtx == NULL)
		s->str_vtx = tmp;
	else
	{
		if (!(space = (char*)malloc(sizeof(char) * 2)))
			handle_error(s, MALLOC_ERROR);
		space[0] = ' ';
		space[1] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &space);
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &tmp);
	}
	// printf("str_vtx = %s|\n", s->str_vtx);
}

void	ft_close_sector(t_main *s)
{
	int		nb_wall;
	int		init;
	int		size_line;
	char	*begin;
	char	*end;

	begin = ft_strdup("sector 0 20 | ");
	end = NULL;
	init = 1;
	nb_wall = ft_howmany_char(s->str_vtx, ' ') + 1;
	s->str_vtx = ft_strjoin_free(&begin, &s->str_vtx);
	while (nb_wall > 0)
	{
		if (init)
		{
			init = 0;
			if (!(end = (char*)malloc(sizeof(char) * 6)))
				handle_error(s, MALLOC_ERROR);
			end[0] = ' ';
			end[1] = '|';
			end[2] = ' ';
			end[3] = '-';
			end[4] = '1';
			end[5] = '\0';
			s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
		}
		else
		{
			if (!(end = (char*)malloc(sizeof(char) * 2)))
				handle_error(s, MALLOC_ERROR);
			end[0] = ' ';
			end[1] = '-';
			end[2] = '1';
			end[3] = '\0';
			s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
		}
		nb_wall--;
	}
	// printf("FINAL str_vtx = %s\n", s->str_vtx);
	size_line = ft_strlen(s->str_vtx);
	ft_parse_sector(s, s->str_vtx, size_line);
}

void	ft_sector_mode(t_main *s, int x, int y)
{
	t_vertex	*vtx;
	t_pos		mouse;
	int			id;

	vtx = s->vertex;
	// printf("salut\n");
	mouse.x = arround(s->editor->space, x - (s->editor->decal_x % s->editor->space));
	mouse.y = arround(s->editor->space, y - (s->editor->decal_y % s->editor->space));
	if ((id = anchor_exists(s, mouse)))
	{
		if (s->str_vtx != NULL && ft_atoi(s->str_vtx) == id)
			ft_close_sector(s);
		else
			ft_save_sector_vextex(s, id);
	}
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
