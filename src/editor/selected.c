/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:07:24 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 13:07:27 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		move_sprite(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->selected == 1)
		{
			sprite->r_ori = get_abs_r_pos(s, s->ft_mouse);
			sprite->r_pos = sprite->r_ori;
			set_sprite(s);
			break ;
		}
		sprite = sprite->next;
	}
}

void		ft_trace_vertical_select(t_main *s, t_line line, Uint32 color)
{
	int		sens_x;
	int		sens_y;
	t_pos	coord;

	line.e = line.y2 > line.y1 ? line.y2 - line.y1 : line.y1 - line.y2;
	sens_x = line.x2 > line.x1 ? 1 : -1;
	sens_y = line.y2 > line.y1 ? 1 : -1;
	line.dy = line.e * 2;
	line.dx = line.x2 > line.x1 ? (line.x2 - line.x1) * 2
		: (line.x1 - line.x2) * 2;
	line.pixel_o = line.y1;
	while (line.y1 != line.y2)
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

int			ft_trace_line_select(t_main *s, t_line line, Uint32 color)
{
	int		sens_x;
	int		sens_y;
	t_pos	coord;

	sens_x = line.x2 > line.x1 ? 1 : -1;
	sens_y = line.y2 > line.y1 ? 1 : -1;
	if (line.dx < line.dy)
	{
		ft_trace_vertical_select(s, line, color);
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

void		ft_get_line_select(t_main *s, t_line line, Uint32 color)
{
	line.e = line.x2 > line.x1 ? line.x2 - line.x1 : line.x1 - line.x2;
	line.dy = line.y2 > line.y1 ? (line.y2 - line.y1) * 2
		: (line.y1 - line.y2) * 2;
	line.dx = line.e * 2;
	ft_trace_line_select(s, line, color);
}

void		trace_select(t_main *s)
{
	t_line		line;

	if (s->editor->selected == 0)
		return ;
	line.x1 = s->editor->line.x1;
	line.y1 = s->editor->line.y1;
	line.x2 = s->editor->line.x1;
	line.y2 = s->editor->line.y2;
	ft_get_line_select(s, line, BLUE);
	line.x1 = s->editor->line.x1;
	line.y1 = s->editor->line.y1;
	line.x2 = s->editor->line.x2;
	line.y2 = s->editor->line.y1;
	ft_get_line_select(s, line, BLUE);
	line.x1 = s->editor->line.x2;
	line.y1 = s->editor->line.y1;
	line.x2 = s->editor->line.x2;
	line.y2 = s->editor->line.y2;
	ft_get_line_select(s, line, BLUE);
	line.x1 = s->editor->line.x2;
	line.y1 = s->editor->line.y2;
	line.x2 = s->editor->line.x1;
	line.y2 = s->editor->line.y2;
	ft_get_line_select(s, line, BLUE);
}
