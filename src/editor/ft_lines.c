/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:41:35 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/05 16:42:35 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	trace_direction(t_main *s)
{
	s->player.line.x1 = s->player.pos.x;
	s->player.line.y1 = s->player.pos.y;
	s->player.line.x2 = s->player.line.x1 + cos(to_rad(s->player.angle)) * 20;
	s->player.line.y2 = s->player.line.y1 - sin(to_rad(s->player.angle)) * 20;
	ft_get_line(s, s->player.line, BLUE);
}

void	ft_trace_vertical(t_main *s, t_line line, Uint32 color)
{
	int		sens_x;
	int		sens_y;
	t_pos	coord;
	int		px;

	px = -1;
	line.e = line.y2 > line.y1 ? line.y2 - line.y1 : line.y1 - line.y2;
	sens_x = line.x2 > line.x1 ? 1 : -1;
	sens_y = line.y2 > line.y1 ? 1 : -1;
	line.dy = line.e * 2;
	line.dx = line.x2 > line.x1 ? (line.x2 - line.x1) * 2
		: (line.x1 - line.x2) * 2;
	line.pixel_o = line.y1;
	while (line.y1 != line.y2 && ++px < 20)
	{
		coord.x = line.x1;
		coord.y = line.y1;
		set_pixel(s->sdl->editor, color, coord);
		line.y1 += sens_y;
		if ((line.e -= line.dx) <= 0)
		{
			line.x1 += sens_x;
			line.e += line.dy;
		}
	}
}

int		ft_trace_line(t_main *s, t_line line, Uint32 color)
{
	int		sens_x;
	int		sens_y;
	t_pos	coord;

	sens_x = line.x2 > line.x1 ? 1 : -1;
	sens_y = line.y2 > line.y1 ? 1 : -1;
	if (line.dx < line.dy)
	{
		ft_trace_vertical(s, line, color);
		return (0);
	}
	line.pixel_o = line.x1;
	while (line.x1 != line.x2)
	{
		coord.x = line.x1;
		coord.y = line.y1;
		set_pixel(s->sdl->editor, color, coord);
		line.x1 += sens_x;
		if ((line.e -= line.dy) <= 0)
		{
			line.y1 += sens_y;
			line.e += line.dx;
		}
	}
	return (0);
}

void	ft_get_line(t_main *s, t_line line, Uint32 color)
{
	line.e = line.x2 > line.x1 ? line.x2 - line.x1 : line.x1 - line.x2;
	line.dy = line.y2 > line.y1 ? (line.y2 - line.y1) * 2 :
		(line.y1 - line.y2) * 2;
	line.dx = line.e * 2;
	ft_trace_line(s, line, color);
}
