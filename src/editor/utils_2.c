#include "doom.h"

double		ft_dist_double(double x1, double y1, double x2, double y2)
{
	return (sqrt(powf(x1 - x2, 2) + powf(y1 - y2, 2)));
}

double		ft_dist_t_dpos(t_dpos pos1, t_dpos pos2)
{
	return (sqrt(powf(pos1.x - pos2.x, 2) + powf(pos1.y - pos2.y, 2)));
}
