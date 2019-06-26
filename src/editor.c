#include "doom.h"

void	ft_draw_editor(t_editor *edi, t_texture *tex)
{
	t_pos	coord;
	Uint32	color = 0xaca7a7FF; // #aca7a7

	// decal_x = decalage total en pixels entre le point 0,0 et le premier point dans l'ecran.
	// coord.x  decalage en pixels entre le pixel 0 de l'ecran et le premier point de la grille affichée a l'ecran.
	coord.x = edi->decal_x % edi->space;
	coord.y = edi->decal_y % edi->space;

	if (edi->decal_x >= 0 && ft_abs(edi->decal_x) < edi->space){
		edi->ref.x = 0;printf("etat1\n");}
	else if (edi->decal_x > 0){
		edi->ref.x = (edi->decal_x / edi->space);printf("etat2\n");}
	else if (edi->decal_x < 0){
		edi->ref.x = (edi->decal_x / edi->space);printf("etat3\n");}


	printf("coord.x = %d\ndecal_x = %d\nref.x = %d\n\n\n",coord.x , edi->decal_x, edi->ref.x);
	while (coord.y < HEIGHT)
	{
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
