#include "doom.h"

double	ft_find_signed_area(t_sector *sct)
{
	double	somme;
	t_int	*wall;
	int		i;

	wall = sct->vertex;
	i = 0;
	somme = 0.0;
	while (i++ < sct->vertex->prev->id)
	{
		somme += (wall->ptr->pos.x * wall->next->ptr->pos.y)
		- (wall->next->ptr->pos.x * wall->ptr->pos.y);
		wall = wall->next;
	}
	return (0.5 * somme);
}

/*
**** Renvoie les coordonees du centre du secteur donner.
*/
t_pos	ft_find_polygon_center(t_sector *sct)
{
	double	a; //a car represente la variable "A" de l'equation
	t_int	*wall;
	int		i;
	t_pos	center;
	t_dpos	somme;

	a = ft_find_signed_area(sct);
	wall = sct->vertex;
	i = 0;
	somme.x = 0.0;
	somme.y = 0.0;
	while (i++ < sct->vertex->prev->id)
	{
		somme.x += (wall->ptr->pos.x + wall->next->ptr->pos.x)
		* ((wall->ptr->pos.x * wall->next->ptr->pos.y)
		- (wall->next->ptr->pos.x * wall->ptr->pos.y));
		somme.y += (wall->ptr->pos.y + wall->next->ptr->pos.y)
		* ((wall->ptr->pos.x * wall->next->ptr->pos.y)
		- (wall->next->ptr->pos.x * wall->ptr->pos.y));
		wall = wall->next;
	}
	center.x = (1 / (6 * a)) * somme.x;
	center.y = (1 / (6 * a)) * somme.y;
	// printf("Le centre du sct %d =  x(%d), y(%d)\n", sct->id, center.x, center.y);
	return (center);
}
