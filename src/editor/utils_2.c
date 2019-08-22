#include "doom.h"

double		ft_dist_double(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

double		ft_dist_t_dpos(t_dpos pos1, t_dpos pos2)
{
	return (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
}

double	ft_find_angle_plan(double a, double b, double c)
{	//la variable c correspond a la longueur en face de langle a calculer
	// printf("a(%f) + b(%f) - c(%f) / 2*a*b\n",a, b, c);
	return (to_degres(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b))));
}

char	isLeft(t_dpos a, t_dpos b, t_dpos c)
{
	return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}
