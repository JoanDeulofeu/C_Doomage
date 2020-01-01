#include "doom.h"

void 	change_wall_texture(t_main *s, int up)
{
	t_int		*wall;
	t_dpos		pos;
	t_sector	*sct;
	int 		ptr_id;

	sct = get_sector_by_id(s, s->player.sector_id);
	if (sct == NULL)
		return ;
	pos = get_direction(s, NULL, 1000, s->player.m_pos);
	ptr_id = ft_find_wall2(s, s->player.m_pos, pos, YELLOW, sct->id);
	wall = get_t_int_by_vertex_id(sct->vertex, ptr_id);
	if (wall == NULL)
		return ;
	// printf("wall->id = %d\n", wall->id);
	if (up == 1)
	{
		wall->tex_nb += 1;
		if (s->editor->all_texture.image[wall->tex_nb] == NULL)
			wall->tex_nb = 0;
	}
	else if (up == 0)
	{
		wall->tex_nb -= 1;
		if (wall->tex_nb == -1)
			wall->tex_nb = MAX_TEXTURES;
	}
	wall->image = s->editor->all_texture.image[wall->tex_nb];
}

int		ft_howmany_char(char *str, char c)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			res++;
	}
	return (res);
}

int		ft_nb_is_in_str(char *str, int nb)
{
	int	i;
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
	//hstghs
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

int		ft_norm_close_sector(t_main *s, int part, char *end)
{
	if (part == 1)
	{
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
		if (!(end = (char*)malloc(sizeof(char) * 4)))
			handle_error(s, MALLOC_ERROR);
		end[0] = ' ';
		end[1] = '-';
		end[2] = '1';
		end[3] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
	}
	return (0);
}

int		ft_norm_close_sector2(t_main *s, int part, char *end)
{
	if (part == 1)
	{
		if (!(end = (char*)malloc(sizeof(char) * 5)))
			handle_error(s, MALLOC_ERROR);
		end[0] = ' ';
		end[1] = '|';
		end[2] = ' ';
		end[3] = '0';
		end[4] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
	}
	else
	{
		if (!(end = (char*)malloc(sizeof(char) * 3)))
			handle_error(s, MALLOC_ERROR);
		end[0] = ' ';
		end[1] = '0';
		end[2] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
	}
	return (0);
}

void	ft_close_sector(t_main *s)
{
	int		nb_wall;
	int		i;
	int		init;
	char	*begin;
	char	*end;

	begin = ft_strdup("sector 0 3 | ");
	end = NULL;
	init = 1;
	i = 0;
	nb_wall = ft_howmany_char(s->str_vtx, ' ') + 1;
	s->str_vtx = ft_strjoin_free(&begin, &s->str_vtx);
	while (nb_wall > i++)
	{
		if (init)
			init = ft_norm_close_sector(s, 1, end);
		else
			ft_norm_close_sector(s, 2, end);
	}
	i = 0;
	init = 1;
	while (nb_wall > i++)
	{
		if (init)
			init = ft_norm_close_sector2(s, 1, end);
		else
			ft_norm_close_sector2(s, 2, end);
	}
	// printf("FINAL str_vtx = -%s-\n", s->str_vtx);
	// printf("Ligne d'ajout de secteur:\n     |%s|\n\n", s->str_vtx);
	ft_parse_sector(s, s->str_vtx);
	s->str_vtx = NULL;
	ft_check_validity_last_sector(s);
	ft_reset_color_vertex(s);
}

int		ft_sector_mode(t_main *s, int x, int y)
{
	t_vertex	*vtx;
	t_pos		mouse;
	int			id;

	vtx = s->vertex;
	mouse.x = arround(s->editor->space, x
		- (s->editor->decal_x % s->editor->space));
	mouse.y = arround(s->editor->space, y
		- (s->editor->decal_y % s->editor->space));
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

Uint32	ft_color_trump(t_main *s, t_int *s_vtx)
{
	if (s_vtx->wall_value != -1)
		return (0xddd241ff);
	// printf("wall.selected = %d\n", s_vtx->selected);
	if (s_vtx->selected == 2)
	{
		return (0xddd241ff);
	}
	// if (s->editor->wall == s_vtx)
	// 	printf("%p et %p\n", s->editor->wall, s_vtx);
	if (s->editor->wall2 == NULL && s->editor->wall && s_vtx == s->editor->wall)
	{
		return (0xddd241ff);
	}
	else if (s->editor->wall2 && s->editor->wall2->selected == 3
		&& s_vtx == s->editor->wall2)
	{
		return (GREEN);
	}
	else if (s->editor->wall2 && s->editor->wall2->selected == 4
		&& s_vtx == s->editor->wall2)
	{
		return (S_RED);
	}
	else
		return (0xff7062FF);
}

void	ft_trump(t_main *s, t_int *s_vtx)
{
	Uint32		color;
	t_vertex	*vtx;

	color = ft_color_trump(s, s_vtx);
	vtx = s_vtx->ptr;
	// printf("s_vtx->ptr id1 = %d\n", vtx->id );
	s->line.x1 = vtx->pos.x + s->editor->decal_x;
	s->line.y1 = vtx->pos.y + s->editor->decal_y;
	vtx = s_vtx->next->ptr;
	s->line.x2 = vtx->pos.x + s->editor->decal_x;
	s->line.y2 = vtx->pos.y + s->editor->decal_y;
	// printf("s_vtx->ptr id2 = %d\n------------\n", vtx->id );
	get_line(s, color, 1);
}

void	ft_draw_all_wall(t_main *s)
{
	t_int		*vtx;
	t_sector	*sct;
	int				i;

	sct = s->sector;
	vtx = NULL;
	while (sct)
	{
		i = 0;
		if (s->editor->mode_floor == 1 && sct->floor != s->editor->dply_floor)
		{
			sct = sct->next;
			continue;
		}
		vtx = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			ft_trump(s, vtx);
			vtx = vtx->next;
		}
		sct = sct->next;
	}
}
