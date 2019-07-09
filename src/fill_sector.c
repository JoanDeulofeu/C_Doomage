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

// t_pos	check_around_vtx(t_main *s, t_int vtx)
// {
// 	t_pos		pos;
// 	t_vertex	temp_v;
//
// 	temp_v =
// 	pos.x =
// 	if ()
// }
//
// void	fill_sectors(t_main *s)
// {
// 	t_sector	*tmp_sct;
// 	t_int		*tmp_vtx;
//
// 	tmp_sct = s->sector;
// 	while (s->tmp_sct)
// 	{
// 		tmp_vtx = tmp_sct->vertex;
// 		while (tmp_vtx)
// 		{
// 			tmp_vtx = tmp_vtx->next;
// 		}
// 		tmp_sct = tmp_sct->next;
// 	}
// }
