#include "doom.h"

double		ft_fixed_to_float(fixed_float input)
{
	return ((double)input / (double)(1 << FIXED_POINT_FRACTIONAL_BITS));
}

fixed_float	ft_float_to_fixed(double input)
{
	return (fixed_float)(round(input * (1 << FIXED_POINT_FRACTIONAL_BITS)));
}

t_fix_pos	ft_dpos_to_fixfloat(t_dpos dpos)
{
	t_fix_pos fix;

	fix.x = (double)dpos.x / (double)(1 << FIXED_POINT_FRACTIONAL_BITS);
	fix.y = (double)dpos.y / (double)(1 << FIXED_POINT_FRACTIONAL_BITS);
	return (fix);
}

t_dpos		ft_fixfloat_to_dpos(t_fix_pos fix)
{
	t_dpos	dpos;

	dpos.x = (fixed_float)(round(fix.x * (1 << FIXED_POINT_FRACTIONAL_BITS)));
	dpos.y = (fixed_float)(round(fix.y * (1 << FIXED_POINT_FRACTIONAL_BITS)));
	return (dpos);
}
