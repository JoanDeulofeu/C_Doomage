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
