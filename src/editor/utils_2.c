/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:44:09 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/05 15:57:17 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double		ft_dist_t_dpos(t_dpos pos1, t_dpos pos2)
{
	return (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
}

double		ft_dist_t_pos(t_pos pos1, t_pos pos2)
{
	t_dpos	dpos1;
	t_dpos	dpos2;

	dpos1 = ft_pos_to_dpos(pos1);
	dpos2 = ft_pos_to_dpos(pos2);
	return (sqrt(pow(dpos1.x - dpos2.x, 2) + pow(dpos1.y - dpos2.y, 2)));
}

t_dpos		to_edi_coord(t_main *s, t_dpos coord)
{
	t_dpos	new;

	new.x = coord.x / METRE;
	new.y = coord.y / METRE;
	new = ft_pos_to_dpos(get_px_r_pos(s, new));
	return (new);
}

double		ft_find_angle_plan(double a, double b, double c)
{
	return (to_degres(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b))));
}

Uint32		get_pixel_color(t_texture *text, int x, int y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (text->content[x + y * WIDTH]);
	else
		return (2);
}
