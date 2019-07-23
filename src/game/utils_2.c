#include "doom.h"

int	clamp (int x, int min, int max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return (x);
}
