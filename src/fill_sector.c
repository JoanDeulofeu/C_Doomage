#include "doom.h"

void	r_check_y(t_main *s, t_pile *pile, t_pos pos)
{
	Uint32	color_got;
	t_pos	cur;

	cur = pos;
	cur.y -= 1;
	if (cur.y >= 0)
	{
		color_got = get_pixel_color(s->sdl->editor, cur.x, cur.y);
		if (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
			empiler(s, pile, cur);
	}
	cur.y += 2;
	if (cur.y <= HEIGHT)
	{
		color_got = get_pixel_color(s->sdl->editor, cur.x, cur.y);
		if (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
			empiler(s, pile, cur);
	}
}

Uint32	get_color(int sct_id)
{
	int res;

	res = sct_id % 10;
	if (res == 0)
		return (S_YELLOW);
	else if (res == 1)
		return (S_RED);
	else if (res == 2)
		return (S_DBLUE);
	else if (res == 3)
		return (S_BROWN);
	else if (res == 4)
		return (S_GREEN);
	else if (res == 5)
		return (S_PURPLE);
	else if (res == 6)
		return (S_ORANGE);
	else if (res == 7)
		return (S_BLUE);
	else if (res == 8)
		return (S_DGREEN);
	else if (res == 9)
		return (S_PINK);
	else
		return (0);
}

void	remplissage(t_main *s, t_pile *pile, Uint32 r_color)
{
	t_pos	w;
	t_pos	e;
	Uint32	color_got;

	w = depiler(pile);
	e = w;
	color_got = get_pixel_color(s->sdl->editor, w.x, w.y);
	while (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
	{
		set_pixel(s->sdl->editor, r_color, w);
		r_check_y(s, pile, w);
		w.x--;
		color_got = get_pixel_color(s->sdl->editor, w.x, w.y);
	}
	w.x++;
	e.x++;
	color_got = get_pixel_color(s->sdl->editor, e.x, e.y);
	while (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
	{
		set_pixel(s->sdl->editor, r_color, e);
		r_check_y(s, pile, e);
		e.x++;
		color_got = get_pixel_color(s->sdl->editor, e.x, e.y);
	}
}

void	draw_sector(t_main *s, int x, int y, Uint32 r_color)
{
	Uint32	color_got;
	t_pile	*pile;
	t_pos	coord;

	coord.x = x;
	coord.y = y;
	if (!(pile = (t_pile*)malloc(sizeof(t_pile))))
		handle_error(s, MALLOC_ERROR);
	pile->first = NULL;
	color_got = get_pixel_color(s->sdl->editor, coord.x, coord.y);
	if (color_got != BLACK_SCREEN && color_got != 0xaca7a7FF)
		return ;
	empiler(s, pile, coord);
	while (pile->first)
		remplissage(s, pile, r_color);
}

int		check_around_vtx(t_main *s, t_int *vtx, int sct_id, t_pos *pos)
{
	t_vertex	*temp_v;
	Uint32		color_got;
	int			test;

	// printf("secteur id = %d\n", sct_id);
	temp_v = s->vertex;
	while (temp_v && temp_v->id != vtx->value)
	{
		temp_v = temp_v->next;
	}
	pos->x = temp_v->pos.x;
	pos->y = temp_v->pos.y;
	pos->y -= 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("haut : is in sector renvoie = %d\n", test);
		return (1);
	}
	pos->x += 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("haut-droite : is in sector renvoie = %d\n", test);
		return (1);
	}
	pos->y += 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("droite : is in sector renvoie = %d\n", test);
		return (1);
	}
	pos->y += 8;
	pos->x += 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("bas-doite : is in sector renvoie = %d\n", test);
		return (1);
	}
	pos->x -= 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("bas : is in sector renvoie = %d\n", test);
		return (1);
	}
	pos->x -= 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("bas-gauche : is in sector renvoie = %d\n", test);
		return (1);
	}
	pos->y -= 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("gauche : is in sector renvoie = %d\n", test);
		return (1);
	}
	pos->y -= 8;
	color_got = get_pixel_color(s->sdl->editor, pos->x, pos->y);
	if ((test = ft_is_in_sector(s, *pos)) == sct_id && color_got != COLOR_WALL)
	{
		// printf("haut-gauche : is in sector renvoie = %d\n", test);
		return (1);
	}
	return (0);
}

void	fill_sectors(t_main *s)
{
	t_sector	*tmp_sct;
	t_int		*tmp_vtx;
	t_pos		*pos;

	if (!(pos = (t_pos*)malloc(sizeof(t_pos))))
		handle_error(s, MALLOC_ERROR);
	pos->x = 0;
	pos->y = 0;
	tmp_sct = s->sector;
	while (tmp_sct)
	{
		// printf ("check sector[%d]\n", tmp_sct->id);
		tmp_vtx = tmp_sct->vertex;
		while (tmp_vtx)
		{
			// printf ("check vertex[%d]\n", tmp_vtx->value);
			if (check_around_vtx(s, tmp_vtx, tmp_sct->id, pos))
			{
				// printf ("check vertex[%d]\n", tmp_vtx->value);
				// printf("pos x[%d] et pos y[%d]\n", pos->x, pos->y);
				draw_sector(s, pos->x, pos->y, get_color(tmp_sct->id));
				break;
			}
			tmp_vtx = tmp_vtx->next;
		}
		tmp_sct = tmp_sct->next;
	}
	free (pos);
}
