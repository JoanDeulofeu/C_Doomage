#include "doom.h"

int		ft_vertex_worst_sector(t_main *s, int id)
{
	t_sector	*sct;
	t_int		*vtx;
	int			i;

	sct = s->sector;
	while (sct)
	{
		i = 0;
		vtx = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			if (vtx->value == id && sct->floor == s->editor->dply_floor)
				return (1);
			vtx = vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

void	ft_choose_draw_vertex(t_main *s, t_vertex *temp, t_pos pos)
{
	if (s->editor->mode_floor == 0)
	{
		if (temp->selected == 2)
			draw_anchor(s, pos, PINK);
		else if (temp->selected == 1)
			draw_anchor(s, pos, BLUE);
		else
			draw_anchor(s, pos, GREEN);
	}
	else
	{
		if (ft_vertex_worst_sector(s, temp->id))
			draw_anchor(s, pos, PINK);
	}
}



void	display_map(t_main *s)
{
	t_vertex	*temp;
	t_editor	*edi;
	t_pos		pos;
	int			correc = 0;

	temp = NULL;
	edi = s->editor;
	if (s->vertex)
		temp = s->vertex;
	while (temp)
	{
		if (edi->decal_x <= 0)
			correc = edi->decal_x % edi->space != 0 ? 1 : 0;
			// correc = 0;
		else
			correc = 0;
		if (edi->decal_x < 0)
			pos.x = (temp->x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
		else
			pos.x = (temp->x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
			// pos.x = (temp->x * edi->space - (edi->ref.x * edi->space + (edi->decal_x % edi->space)));
		// printf("correc = %d | pos.x = %d\n", correc, pos.x);

		if (edi->decal_y <= 0)
			correc = edi->decal_y % edi->space != 0 ? 1 : 0;
		else
			correc = 0;
		pos.y = (temp->y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
		temp->pos = pos;
		if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
			ft_choose_draw_vertex(s, temp, pos);
		temp = temp->next;
	}
	// printf("decalx = %d\n", s->editor->decal_x );

	//player anchor
		//draw_anchor(s, s->player.pos, BLUE);
	set_player(s);
	if (s->editor->selected ==1)
		trace_select(s);
	refresh_sprite_pos(s);
	//draw_weapon(s, 0, WIDTH / 2, HEIGHT / 2);


}
