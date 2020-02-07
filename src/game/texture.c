/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:38:05 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 16:38:48 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ft_draw_ceiling(t_main *s, t_walls *wall, t_pos coord)
{
	int			begin;
	double		pct;

	if ((begin = coord.y) < 0)
		return (begin);
	wall->diffx_ceiling = (wall->diffx_ceiling == 0) ? 1 : wall->diffx_ceiling;
	pct = (((double)coord.x - (double)wall->minx_ceiling) * 100)
	/ (double)wall->diffx_ceiling;
	if ((wall->minx_ceiling == wall->left_ceiling_limit.x && wall->miny_ceiling
		== wall->right_ceiling_limit.y) || (wall->minx_ceiling
		== wall->right_ceiling_limit.x && wall->miny_ceiling
		== wall->left_ceiling_limit.y))
		pct = 100 - pct;
	coord.y = ((pct * wall->diffy_ceiling) * 0.01) + wall->miny_ceiling;
	if (coord.y < 0)
		coord.y = 0;
	while (coord.y < begin && coord.y < HEIGHT)
	{
		set_pixel(s->sdl->game, 0x6e492eff, coord);
		coord.y++;
	}
	coord.y = begin;
	return (coord.y - 1);
}

void	ft_draw_floor(t_main *s, t_walls *wall, t_pos coord)
{
	int		end;
	double	pct;

	wall->diffx_floor = (wall->diffx_floor == 0) ? 1 : wall->diffx_floor;
	pct = (((double)coord.x - (double)wall->minx_floor) * 100)
	/ ((double)wall->diffx_floor);
	if ((wall->minx_floor == wall->left_floor_limit.x
		&& wall->miny_floor == wall->right_floor_limit.y)
		|| (wall->minx_floor == wall->right_floor_limit.x
		&& wall->miny_floor == wall->left_floor_limit.y))
		pct = 100 - pct;
	end = ((pct * wall->diffy_floor) * 0.01) + wall->miny_floor;
	if (coord.y < 0)
		coord.y = 0;
	while (coord.y < end && coord.y < HEIGHT)
	{
		set_pixel(s->sdl->game, 0xa8b08eff, coord);
		coord.y++;
	}
}
