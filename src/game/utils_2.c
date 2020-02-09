/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:00:17 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 16:31:19 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
