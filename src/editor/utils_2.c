#include "doom.h"

double		ft_dist_double(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

double		ft_dist_t_dpos(t_dpos pos1, t_dpos pos2)
{
	return (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
}
