#include "doom.h"

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

void	set_selected(t_main *s, t_pos ori, char color)
{
	t_vertex	*temp;

	temp = s->vertex;
	ori = get_abs_pos(s, ori);
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y && color == 2)
		{
			temp->selected = color;
			return ;
		}
		if (temp->x == ori.x && temp->y == ori.y && color == 1)
		{
			temp->selected = color;
			return ;
		}
		if (temp->selected != 0 && color == 0)
		{
			temp->selected = color;
			return ;
		}
		temp = temp->next;
	}
}

void	ft_reset_color_vertex(t_main *s)
{
	t_vertex	*tmp;

	tmp = s->vertex;
	while (tmp)
	{
		tmp->selected = 0;
		tmp = tmp->next;
	}
}
