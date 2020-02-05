/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:42:51 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/05 15:56:19 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double		to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

double		to_degres(double rad)
{
	return (rad * 180.0 / M_PI);
}

int			arround(int space, int nb)
{
	int		res;
	int		res2;

	res = nb / space;
	res2 = res + 1;
	return (nb - (space * res) > space * res2
			- nb ? space * res2 : space * res);
}

double		percent(double value, double total)
{
	return (value / total);
}
