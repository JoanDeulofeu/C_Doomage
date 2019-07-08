#include "doom.h"

void	change_mode(t_main *s, int key)
{
	if (key == MOVE)
	{
		s->editor->mode = move;
		ft_reset_color_vertex(s);
	}
	else if (key == WALL)
	{
		s->editor->mode = sector;
		s->editor->color_sector = 2;
		ft_reset_color_vertex(s);
		ft_memdel((void **)&s->str_vtx);
	}
	else if (key == VERTEX)
	{
		s->editor->mode = vertex;
		ft_reset_color_vertex(s);
	}
	else if (key == PLAYER)
	{
		s->editor->mode = player;
		ft_reset_color_vertex(s);
	}
	else if (key == FLOOR)
	{
		s->editor->mode = m_floor;
		ft_reset_color_vertex(s);
	}
	else if (key == SUPP)
	{
		s->editor->mode = supp;
		ft_reset_color_vertex(s);
	}
	// printf("mode = %d\n", s->editor->mode);
	// printf("mode = %d\n", s->editor->mode);
}



void	remplissage(t_main *s, t_pos coord)
{
	Uint32	color_got;
	t_pile	*pile;
	t_pos	cur;

	// pile = NULL;
	cur.x = 0;
	cur.y = 0;
	if (!(pile = (t_pile*)malloc(sizeof(t_pile))))
		handle_error(s, MALLOC_ERROR);
	pile->first = NULL;

	color_got = get_pixel_color(s->sdl->editor, coord.x, coord.y);
	if (color_got != BLACK_SCREEN && color_got != 0xaca7a7FF)
		return ;
	empiler(s, pile, coord);
	// printf("%d\n", pile.first->pixel.x);
	while (pile->first)
	{
		cur = depiler(pile);
		// color_got = get_pixel_color(s->sdl->editor, cur.x, cur.y);
		set_pixel(s->sdl->editor, YELLOW, cur);

		color_got = get_pixel_color(s->sdl->editor, cur.x, cur.y - 1);
		if (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
		{
			cur.y -= 1;
			empiler(s, pile, cur);
			cur.y += 1;
		}
		color_got = get_pixel_color(s->sdl->editor, cur.x, cur.y + 1);
		if (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
		{
			cur.y += 1;
			empiler(s, pile, cur);
			cur.y -= 1;
		}
		color_got = get_pixel_color(s->sdl->editor, cur.x - 1, cur.y);
		if (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
		{
			cur.x -= 1;
			empiler(s, pile, cur);
			cur.x += 1;
		}
		color_got = get_pixel_color(s->sdl->editor, cur.x + 1, cur.y);
		if (color_got == BLACK_SCREEN || color_got == 0xaca7a7FF)
		{
			cur.x += 1;
			empiler(s, pile, cur);
			cur.x -= 1;
		}
	}

}

void	draw_sector(t_main *s, int x, int y)
{
	Uint32 color;
	Uint32 color_got;
	t_pos coord;
	t_pos ori;

	coord.x = x;
	coord.y = y;
	remplissage(s, coord);
	// coord = ori;

	// printf("x = %d, y = %d\n", coord.x, coord.y);
	// color = YELLOW;
	// if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
	// 	return ;
	// printf("x = %d\n", x);
	// if (get_pixel_color(s->sdl->editor, x, y) == BLACK_SCREEN || get_pixel_color(s->sdl->editor, x, y) == 0xaca7a7FF)
	// {
	// 	set_pixel(s->sdl->editor, color, coord);
	// 	draw_sector(s, x + 1, y);
	// 	draw_sector(s, x - 1, y);
	// 	draw_sector(s, x, y - 1);
	// 	draw_sector(s, x, y + 1);
	// }

}

int		ft_find_ref(t_editor *edi, int decal)
{
	// printf("Ref : x %d | y : %d | decalx = %d\n", edi->ref.x, edi->ref.y, edi->decal_x);
	if (decal >= 0 && decal < edi->space)
	{
		// printf("ETAT [1] ");
		return (0);
	}
	else if (decal > 0)
	{
		// printf("ETAT [2] ");
		return ((decal / edi->space) * -1);
	}
	else if (decal < 0)
	{
		// printf("ETAT [3] ");
		// printf("\n(%d / (%d) -1) * -1", decal, edi->space);
		if (decal % edi->space == 0)
			return ((decal / (edi->space)) * -1);
		else
			return ((decal / (edi->space) -1) * -1);
	}
	return (0);
}

void	ft_draw_editor(t_editor *edi, t_texture *tex)
{
	t_pos	coord;
	Uint32	color = 0xaca7a7FF;

	// decal_x = decalage total en pixels entre le point 0,0 et le premier point dans l'ecran.
	// coord.x  decalage en pixels entre le pixel 0 de l'ecran et le premier point de la grille affichée a l'ecran.
	coord.x = edi->decal_x % edi->space;
	coord.y = edi->decal_y % edi->space;

	edi->ref.x = ft_find_ref(edi, edi->decal_x);
	edi->ref.y = ft_find_ref(edi, edi->decal_y);
	// printf("\ncoord.x = %d\ndecal_x = %d\nref.x = %d\n",coord.x , edi->decal_x, edi->ref.x);
	// printf("\ncoord.x = %d\ndecal_x = %d\nref.x = %d\n",coord.x , edi->decal_x, edi->ref.x);
	// printf("coord.y = %d\ndecal_y = %d\nref.y = %d\n\n\n",coord.y , edi->decal_y, edi->ref.y);

	//printf("REF   X %d | Y %d\n",edi->ref.x, edi->ref.y);

	// printf("REF   X %d | Y %d\n\n",edi->ref.x, edi->ref.y);
	// printf("coord.x = %d\n", coord.x);
	if (coord.y < 0)
		coord.y += edi->space;
	while (coord.y < HEIGHT)
	{
		if (coord.x < 0)
			coord.x += edi->space;
		while (coord.x < WIDTH)
		{
			set_pixel(tex, color, coord);
			coord.x += edi->space;
		}
		coord.x = edi->decal_x % edi->space;
		coord.y += edi->space;
	}
}

void	draw_wall(t_main *s, t_pos ori)
{
	s->line.x1 = ori.x;
	s->line.y1 = ori.y;
	get_line(s, WHITE);
}
