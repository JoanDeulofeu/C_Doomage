#include "doom.h"

int exist_vertex(t_main *s, t_pos *mouse_save, int *id, t_pos *ori)
{
	int selected;

	selected= 0;
	s->editor->selected =1;
	mouse_save->x = s->sdl->event.button.x;
	mouse_save->y = s->sdl->event.button.y;
	s->editor->line.x1 = mouse_save->x;
	s->editor->line.y1 = mouse_save->y;
	ori->x = arround(s->editor->space, s->sdl->event.button.x - (s->editor->decal_x % s->editor->space));
	ori->y = arround(s->editor->space, s->sdl->event.button.y - (s->editor->decal_y % s->editor->space));
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

void move_vertex(t_main *s, t_pos tmp_move, t_pos ori, int id)
{
	t_vertex *v;

	v = s->vertex;
	tmp_move.x = arround(s->editor->space, s->sdl->event.button.x - (s->editor->decal_x % s->editor->space));
	tmp_move.y = arround(s->editor->space, s->sdl->event.button.y - (s->editor->decal_y % s->editor->space));
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
		}
		if (v)
			v = v->next;
	}
}

void 	deselect_vertex(t_main *s)
{
	t_vertex *v;

	v = s->vertex;
	while (v)
	{
		v->selec = 0;
		v->selected = 0;
		if (v)
			v = v->next;
	}
}

void select_vertex(t_main *s)
{
	t_vertex *v;

	v = s->vertex;
	while (v)
	{
		if (((v->pos.x >= s->editor->line.x1 && v->pos.x <= s->editor->line.x2) && (v->pos.y >= s->editor->line.y1 && v->pos.y <= s->editor->line.y2)) ||
			((v->pos.x <= s->editor->line.x1 && v->pos.x >= s->editor->line.x2) && (v->pos.y <= s->editor->line.y1 && v->pos.y >= s->editor->line.y2)) ||
				((v->pos.x <= s->editor->line.x1 && v->pos.x >= s->editor->line.x2) && (v->pos.y >= s->editor->line.y1 && v->pos.y <= s->editor->line.y2)) ||
					((v->pos.x >= s->editor->line.x1 && v->pos.x <= s->editor->line.x2) && (v->pos.y <= s->editor->line.y1 && v->pos.y >= s->editor->line.y2)))
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



void	ft_trace_vertical_select(t_main *s, t_line line, Uint32 color)
{
	int sens_x;
	int sens_y;
	t_pos coord;

	line.e = line.y2 > line.y1 ? line.y2 - line.y1 : line.y1 - line.y2;
	sens_x = line.x2 > line.x1 ? 1 : -1;
	sens_y = line.y2 > line.y1 ? 1 : -1;
	line.dy = line.e * 2;
	line.dx = line.x2 > line.x1 ? (line.x2 - line.x1) * 2 : (line.x1 - line.x2) * 2;
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

int		ft_trace_line_select(t_main *s, t_line line, Uint32 color)
{
	int sens_x;
	int sens_y;
	t_pos coord;

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

void	ft_get_line_select(t_main *s, t_line line, Uint32 color)
{
		line.e = line.x2 > line.x1 ? line.x2 - line.x1 : line.x1 - line.x2;
		line.dy = line.y2 > line.y1 ? (line.y2 - line.y1) * 2 : (line.y1 - line.y2) * 2;
		line.dx = line.e * 2;
		ft_trace_line_select(s, line, color);
}

void 	trace_select(t_main *s)
{
	t_editor *edi;
	t_line line;

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
