#include "doom.h"

double			ft_fixed_to_float(fixed_float input)
{
	return ((double)input / (double)(1 << (SHIFT_AMOUNT)));
}

fixed_float		ft_float_to_fixed(double input)
{
	return (fixed_float)(round(input * (1 << SHIFT_AMOUNT)));
}

t_fix_pos		ft_dpos_to_fixfloat(t_dpos dpos)
{
	t_fix_pos	fix;

	fix.x = (double)dpos.x / (double)(1 << SHIFT_AMOUNT);
	fix.y = (double)dpos.y / (double)(1 << SHIFT_AMOUNT);
	return (fix);
}

t_dpos			ft_fixfloat_to_dpos(t_fix_pos fix)
{
	t_dpos		dpos;

	dpos.x = (fixed_float)(round(fix.x * (1 << SHIFT_AMOUNT)));
	dpos.y = (fixed_float)(round(fix.y * (1 << SHIFT_AMOUNT)));
	return (dpos);
}

fixed_float		ft_fixed_pow(fixed_float nb, int power)
{
	int			i;
	fixed_float	tmp;

	i = 0;
	tmp = nb;
	while (i++ < power)
		nb *= tmp;
	return (nb);
}

fixed_float		ft_fixed_sqrt(fixed_float nb)
{
	fixed_float	i;

	i = 1;
	if (nb % 2 == 0)
		i++;
	while (i * i < nb)
		i += 2;
	if (i * i == nb)
		return (i);
	return (0);
}

fixed_float		ft_fixed_mul(fixed_float a, fixed_float b)
{
	int64_t	res;

	res = (int64_t)a * (int64_t)b;
	return ((fixed_float)(res >> SHIFT_AMOUNT));
}

void			ft_test_float(void)
{
	fixed_float		fix;
	double			dooble;

	dooble = -9513.6561;
	// dooble = 4215781.0;
	printf("Double au debut = %f\n", dooble);
	fix = ft_float_to_fixed(dooble);
	printf("Transformer en fixed = %d\n", fix);
	fix += 100 << SHIFT_AMOUNT;
	printf("Fix + 100 = %d\n", fix);
	fix *= 2;
	printf("Fix * 2 = %d\n", fix);
	dooble = ft_fixed_to_float(fix);
	printf("Retour en double = %f\n\n", dooble);
	// dooble = 9513.6561;
	dooble = -4215781.0;
	printf("Double au debut = %f\n", dooble);
	fix = ft_float_to_fixed(dooble);
	printf("Transformer en fixed = %d\n", fix);
	fix += 100 << SHIFT_AMOUNT;
	printf("Fix + 100 = %d\n", fix);
	fix *= 2;
	printf("Fix * 2 = %d\n", fix);
	dooble = ft_fixed_to_float(fix);
	printf("Retour en double = %f\n\n\n", dooble);
}
