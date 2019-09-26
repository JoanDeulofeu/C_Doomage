#include "doom.h"

void	empiler(t_main *s, t_pile *pile, t_pos new_pixel)
{
	t_element *new;

	if (!(new = (t_element*)malloc(sizeof(t_element))))
		handle_error(s, MALLOC_ERROR);
	new->pixel = new_pixel;
	new->next = pile->first;
	pile->first = new;
}

t_pos	depiler(t_pile *pile)
{
	t_pos pixel_depile;
	t_element *element_depile;

	pixel_depile.x = 0;
	pixel_depile.y = 0;
	element_depile = pile->first;
	if (pile && pile->first)
	{
		pixel_depile = element_depile->pixel;
		pile->first = element_depile->next;
		ft_memdel((void **)&element_depile);
	}
	return (pixel_depile);
}
