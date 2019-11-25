#include "doom.h"

int		clamp(int x, int min, int max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return (x);
}

int		max(int value1, int value2)
{
	return (value1 > value2 ? value1 : value2);
}

int		min(int value1, int value2)
{
	return (value1 < value2 ? value1 : value2);
}

double	angle_mod(double angle)
{
	if (angle > (double)360)
		return (angle - (double)360);
	if (angle < 0)
		return ((double)360 + angle);
	else
		return (angle);
}
