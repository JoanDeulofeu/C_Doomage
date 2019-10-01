#include "doom.h"

double		ft_dist_double(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

double		ft_dist_t_dpos(t_dpos pos1, t_dpos pos2)
{
	return (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
}

double		ft_dist_t_pos(t_pos pos1, t_pos pos2)
{
	t_dpos	dpos1;
	t_dpos	dpos2;

	dpos1 = ft_pos_to_dpos(pos1);
	dpos2 = ft_pos_to_dpos(pos2);
	return (sqrt(pow(dpos1.x - dpos2.x, 2) + pow(dpos1.y - dpos2.y, 2)));
}

t_dpos	to_edi_coord(t_main *s, t_dpos coord)
{
	t_dpos new;

	new.x = coord.x / METRE;
	new.y = coord.y / METRE;
	new = ft_pos_to_dpos(get_px_r_pos(s, new));
	return (new);
}

double	ft_find_angle_plan(double a, double b, double c)
{	//la variable c correspond a la longueur en face de langle a calculer
	// printf("a(%f) + b(%f) - c(%f) / 2*a*b\n",a, b, c);
	return (to_degres(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b))));
}

void	*ft_memalloc(size_t size)
{
	void *ptr;

	ptr = (void *)malloc(sizeof(void *) * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}
