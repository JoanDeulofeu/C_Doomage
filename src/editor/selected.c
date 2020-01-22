#include "doom.h"

int			set_selected_sprite(t_main *s, t_pos *mouse_save)
{
	int		selected;

	selected = 0;
	s->editor->selected = 1;
	mouse_save->x = s->sdl->event.button.x;
	mouse_save->y = s->sdl->event.button.y;
	s->editor->line.x1 = mouse_save->x;
	s->editor->line.y1 = mouse_save->y;
//	select_sprite(s);
	return (selected);
}

void		deselect_sprite(t_main *s)
{
	t_sprite	*v;

	v = s->sprite;
	while (v != NULL)
	{
		if (v->selected == 1)
		{
			if (ft_is_in_sector(s, v->m_pos) == 0)
			{
				ft_create_message(s, 2, 200, "sprite must be in sector!");
				v->r_ori = v->old;
				v->r_pos = v->old;
				set_sprite(s);
			}
			v->selected = 0;
		}

		v = v->next;
	}
}

int			is_sprite_selected(t_main *s)
{
	t_sprite	*v;

	v = s->sprite;
	while (v)
	{
		if (v->selected == 1)
			return (1);
		v = v->next;
	}
	return (0);
}

t_sprite	*is_sprite_under_mouse(t_main *s)
{
	t_sprite *sprite;
	t_dpos	s_pos;
	t_dpos	mouse;
	float	value;

	sprite = s->sprite;
	value = 0.5;
	mouse = get_abs_r_pos(s, s->ft_mouse);
	// mouse.x *= METRE;
	// mouse.y *= METRE;
	// mouse = ft_dpos_to_pos(to_edi_coord(s, ft_pos_to_dpos(mouse)));
	while (sprite)
	{
		s_pos = sprite->r_pos;
		if (s_pos.x <= mouse.x + value
		&& s_pos.x >= mouse.x - value
		&& s_pos.y >= mouse.y - value
		&& s_pos.y <= mouse.y + value)
		{
			// printf("\033[32m%f < %f > %f\n", mouse.x - value, s_pos.x, mouse.x + value);
			// printf("%f < %f > %f\n", mouse.y - value, s_pos.y, mouse.y + value);
			return (sprite);
		}
		else
		{
			// printf(" \033[31m%f < %f > %f\n", mouse.x - value, s_pos.x, mouse.x + value);
			// printf(" %f < %f > %f\n", mouse.y - value, s_pos.y, mouse.y + value);
		}
		sprite = sprite->next;
	}
	return (NULL);
}

int		select_sprite(t_main *s)
{
	t_sprite *sprite;

	sprite = is_sprite_under_mouse(s);
	if (sprite)
	{
		sprite->selected = 1;
		sprite->old = sprite->r_ori;
		return (1);
	}
		return (0);
}

// void		select_sprite(t_main *s)
// {
// 	t_sprite	*v;
// 	t_line 		l;
//
// 	l = s->editor->line;
// 	v = s->sprite;
// 	while (v != NULL)
// 	{
// 		if (((v->pos.x >= l.x1 && v->pos.x <= l.x2)
// 			&& (v->pos.y >= l.y1 && v->pos.y <= l.y2))
// 			|| ((v->pos.x <= l.x1 && v->pos.x >= l.x2) && (v->pos.y <= l.y1
// 			&& v->pos.y >= l.y2)) || ((v->pos.x <= l.x1 && v->pos.x >= l.x2)
// 			&& (v->pos.y >= l.y1 && v->pos.y <= l.y2)) || ((v->pos.x >= l.x1
// 			&& v->pos.x <= l.x2) && (v->pos.y <= l.y1 && v->pos.y >= l.y2)))
// 		{
// 			//printf("ok\n\n");
// 		//	draw_anchor(s,v->pos, YELLOW);
// 			v->selected = 1;
// 		}
// 		v = v->next;
// 	}
// 	s->editor->selected = 0;
// }

int			exist_vertex(t_main *s, t_pos *mouse_save, int *id, t_pos *ori)
{
	int		selected;

	selected = 0;
	s->editor->selected = 1;
	mouse_save->x = s->sdl->event.button.x;
	mouse_save->y = s->sdl->event.button.y;
	s->editor->line.x1 = mouse_save->x;
	s->editor->line.y1 = mouse_save->y;
	ori->x = arround(s->editor->space, s->sdl->event.button.x
		- (s->editor->decal_x % s->editor->space));
	ori->y = arround(s->editor->space, s->sdl->event.button.y
		- (s->editor->decal_y % s->editor->space));
	if (ori->x >= 0 && ori->x <= WIDTH && ori->y >= 0 && ori->y <= HEIGHT)
	{
		if ((*id = anchor_exists(s, *ori)) != 0)
		{
			selected = 1;
			s->editor->selected = 0;
		}
	}
	return (selected);
}

void		move_vertex(t_main *s, t_pos tmp_move, t_pos ori, int id)
{
	t_vertex	*v;

		// printf("-------\nid = %d\n-------\n", id);
	v = s->vertex;
	tmp_move.x = arround(s->editor->space, s->sdl->event.button.x
		- (s->editor->decal_x % s->editor->space));
	tmp_move.y = arround(s->editor->space, s->sdl->event.button.y
		- (s->editor->decal_y % s->editor->space));
	tmp_move.x -= ori.x;
	tmp_move.y -= ori.y;
	tmp_move.x /= s->editor->space;
	tmp_move.y /= s->editor->space;
	while (v)
	{
		if (v->selec == 1 && v->id != id)
		{
			v->x = v->old.x + tmp_move.x;
			v->y = v->old.y + tmp_move.y;
			v->m_pos.x = v->x * METRE;
			v->m_pos.y = v->y * METRE;
		}
		if (v)
			v = v->next;
	}
}

void		move_sprite(t_main *s)
{
	t_sprite	*sprite;

	// printf("sprite move\n");
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

void		deselect_vertex(t_main *s)
{
	t_vertex	*v;

	v = s->vertex;
	while (v)
	{
		v->selec = 0;
		v->selected = 0;
		if (v)
			v = v->next;
	}
}

void		select_vertex(t_main *s)
{
	t_vertex	*v;
	t_line		line;
	t_pos		pos;

	deselect_vertex(s);
	v = s->vertex;
	line = s->editor->line;
	while (v)
	{
		pos.x = v->x;
		pos.y = v->y;
		v->pos = get_px_pos(s, pos);
		if (((v->pos.x >= line.x1 && v->pos.x <= line.x2)
			&& (v->pos.y >= line.y1 && v->pos.y <= line.y2))
			|| ((v->pos.x <= line.x1 && v->pos.x >= line.x2)
			&& (v->pos.y <= line.y1 && v->pos.y >= line.y2))
			|| ((v->pos.x <= line.x1 && v->pos.x >= line.x2)
			&& (v->pos.y >= line.y1 && v->pos.y <= line.y2))
			|| ((v->pos.x >= line.x1 && v->pos.x <= line.x2)
			&& (v->pos.y <= line.y1 && v->pos.y >= line.y2)))
		{
			v->selec = 1;
			v->selected = 1;
			v->old.x = v->x;
			v->old.y = v->y;
		}
		if (v)
			v = v->next;
	}
	s->editor->selected = 0;
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
	t_editor	*edi;
	t_line		line;

	if (s->editor->selected == 0)
		return ;
	edi = s->editor;
	line.x1 = edi->line.x1;
	line.y1 = edi->line.y1;
	line.x2 = edi->line.x1;
	line.y2 = edi->line.y2;
	ft_get_line_select(s, line, BLUE);
	line.x1 = edi->line.x1;
	line.y1 = edi->line.y1;
	line.x2 = edi->line.x2;
	line.y2 = edi->line.y1;
	ft_get_line_select(s, line, BLUE);
	line.x1 = edi->line.x2;
	line.y1 = edi->line.y1;
	line.x2 = edi->line.x2;
	line.y2 = edi->line.y2;
	ft_get_line_select(s, line, BLUE);
	line.x1 = edi->line.x2;
	line.y1 = edi->line.y2;
	line.x2 = edi->line.x1;
	line.y2 = edi->line.y2;
	ft_get_line_select(s, line, BLUE);
}
