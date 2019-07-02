#include "doom.h"

void	remove_sector(t_main *s, int id)
{
	//parcourir la liste des secteurs.
	//Pour chaque secteur verifier s'il y a un vertex qui contient l'id donnee
	// Si c'est le cas il faut free le secteur.
	//De la on recommence a reparcourir les secteurs depuis le debut
	//Si un secteur a un portail vers le secteur supprimé, le portail devient -1

	t_sector	*temp_s;
	t_int		*temp_v;
	t_int		*temp_v2;

	temp_s = s->sector;
	while (temp_s)
	{
		temp_v = temp_s->vertex;
		while (temp_v)
		{
			if (temp_v->value == id)
			{
				temp_v = temp_s->vertex;
				while (temp_v)
				{
					temp_v2 = temp_v;
					temp_v = temp_v->next;
					free(temp_v2);
				}
			}
			temp_v = temp_v->next;
		}
		temp_v = temp_s->wall;
		while (temp_v)
		{
			if (temp_v->value == id)
			{
				temp_v = temp_s->wall;
				while (temp_v)
				{
					temp_v2 = temp_v;
					temp_v = temp_v->next;
					free(temp_v2);
				}
			}
			temp_v = temp_v->next;
		}
	}
}

void	remove_anchor(t_main *s, int id)
{
	t_vertex	*temp;

	temp = s->vertex;
	while (temp)
	{
		if (temp->id == id)
		{
			// printf("id actuel = %d\n", temp->id);
			// printf("id du maillon suivant le precedent (notmalemnt le meme id) = %d\n", temp->prev->next->id);
			temp->prev->next = temp->next;
			// printf("id du maillon suivant le precedent (notmalemnt plus le meme id) = %d\n", temp->prev->next->id);
			temp->next->prev = temp->prev;
			temp->next = NULL;
			temp->prev = NULL;
			free(temp->next);
			free(temp->prev);
			free(temp);
			// ft_test_chainlist(s);
			return;
		}
		temp = temp->next;
	}
}

t_pos	get_abs_pos(t_main *s, t_pos ori)
{
	t_pos	res;
	int		correc_x;
	int		correc_y;

	res.x = 0;
	res.y = 0;
	correc_x = 0;
	correc_y = 0;
	if (s->editor->decal_x % s->editor->space != 0 && s->editor->decal_x < 0)
		correc_x = -1;
	if (s->editor->decal_y % s->editor->space != 0 && s->editor->decal_y < 0)
		correc_y = -1;
	res.x = s->editor->ref.x + (ori.x / s->editor->space) + correc_x;
	res.y = s->editor->ref.y + (ori.y / s->editor->space) + correc_y;
	return (res);
}

int		anchor_exists(t_main *s, t_pos ori)
{
	t_vertex	*temp;

	temp = s->vertex;
	ori = get_abs_pos(s, ori);
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y)
			return (temp->id);
		temp = temp->next;
	}
	return (0);
}
//
void	set_selected(t_main *s, t_pos ori, char on)
{
	t_vertex	*temp;

	temp = s->vertex;
	ori = get_abs_pos(s, ori);
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y && on)
		{
			temp->selected = 1;
			return;
		}
		if (temp->selected == 1 && !on)
		{
			temp->selected = 0;
			return;
		}
		temp = temp->next;
	}
}

void	move_anchor(t_main *s, int id)
{
	t_vertex	*temp;
	t_pos		ori;
	t_pos		abs;

	temp = s->vertex;
	while (temp)
	{
		if (temp->id == id)
		{
			ori.x = arround(s->editor->space, s->ft_mouse.x - (s->editor->decal_x % s->editor->space));
			ori.y = arround(s->editor->space, s->ft_mouse.y - (s->editor->decal_y % s->editor->space));
			temp->pos = ori;
			abs = get_abs_pos(s, ori);
			temp->x = abs.x;
			temp->y = abs.y;
			// printf ("true");
			return;
		}
		temp = temp->next;
	}
}

void	create_anchor(t_main *s, t_pos ori)
{
	ori = get_abs_pos(s, ori);
	ft_add_vertex(s, ori.x, ori.y);
}

void	draw_anchor(t_main *s, t_pos ori, Uint32 color)
{
	t_dpos		init;
	t_dpos		dest;
	short		size;

	// size = 5;
	size = s->editor->anchor_size;
	init.x = ori.x - size;
	init.y = ori.y - size;
	dest.x = ori.x + size;
	dest.y = ori.y + size;
	draw_rect(s->sdl->editor, init, dest, color);
}
