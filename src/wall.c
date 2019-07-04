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

int		ft_nb_is_in_str(char *str, int nb)
{
	int i;
	int	tmp;
	int	strlg;

	i = 0;
	tmp = 0;
	strlg = ft_strlen(str);
	while (i <= strlg)
	{
		while ((str[i] < 48 || str[i] > 57) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (0);
		tmp = ft_atoi(&str[i]);
		// printf("tmp = %d et nb = %d\n", tmp, nb);
		if (tmp == nb)
			return (1);
		i += ft_longlen(tmp) + 1;
	}
	return (0);
}

void	ft_save_sector_vextex(t_main *s, int id_vtx)
{
	char	*tmp;
	char	*space;

	tmp = ft_itoa(id_vtx);
	if (s->str_vtx == NULL)
		s->str_vtx = tmp;
	else if ((ft_nb_is_in_str(s->str_vtx, id_vtx)) == 0)
	{
		if (!(space = (char*)malloc(sizeof(char) * 2)))
			handle_error(s, MALLOC_ERROR);
		space[0] = ' ';
		space[1] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &space);
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &tmp);
	}
	// printf("str_vtx = %s|\n", s->str_vtx);
	// printf("lol\n");
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
	s->str_vtx = NULL;
	ft_reset_color_vertex(s);
}

int		ft_sector_mode(t_main *s, int x, int y)
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
		{
			if ((ft_howmany_char(s->str_vtx, ' ') + 1) > 2)
				ft_close_sector(s);
			return (2);
		}
		else
		{
			ft_save_sector_vextex(s, id);
			return (1);
		}
	}
	return (0);
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
				while (vtx && sct->vertex->value != vtx->id && vtx->next)
					vtx = vtx->next;
					s->line.x1 = vtx->pos.x;
					s->line.y1 = vtx->pos.y;

				vtx = s->vertex;
				while (vtx && sct->vertex->next && sct->vertex->next->value != vtx->id)
					vtx = vtx->next;

					s->line.x2 = vtx->pos.x;
					s->line.y2 = vtx->pos.y;
				get_line(s, color);
			}
			else
			{
				vtx = s->vertex;
				while (vtx && sct->vertex && sct->vertex->value != vtx->id && vtx->next)
					vtx = vtx->next;
				s->line.x1 = vtx->pos.x;
				s->line.y1 = vtx->pos.y;
				vtx = s->vertex;
				while (vtx && first_vtx->value != vtx->id)
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
