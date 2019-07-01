#include "doom.h"

int		arround(int space, int nb)
{
	int res;
	int res2;

	res = nb / space;
	res2 = res + 1;
	return (nb - (space * res) > space * res2
	- nb ? space * res2 : space * res);
}
