#include "doom.h"

void clear_wall_list(t_main *s)
{
	t_walls *tmp;

	tmp = s->walls;
	while (s->walls)
	{
		tmp = s->walls;
		s->walls = s->walls->next;
		ft_memdel((void **)&tmp);
	}
	s->walls = NULL;
}

void	put_wall_before(t_main *s, t_walls *new, t_walls *current)
{
	if (current->prev == NULL)
	{
		new->next = current;
		current->prev = new;
		s->walls = new;
	}
	else
	{
		new->next = current;
		new->prev = current->prev;
		new->prev->next = new;
		current->prev = new;
	}

}

void	put_wall_after(t_walls *new, t_walls *current)
{
	if (current->next == NULL)
	{
		current->next = new;
		new->prev = current;
	}
	else
	{
		new->next = current->next;
		new->prev = current;
		current->next->prev = new;
		current->next = new;
	}

}

// void	add_wall_to_list(t_main *s, t_walls *new)
// {
// 	t_walls *tmp;
//
// 	tmp = s->walls;
// 	// printf("new->distqnce = %f\n", new->distance);
// 	if (tmp == NULL) //S'il n'y a aucun mur dans la liste
// 	{
// 		s->walls = new;
// 		// printf("pas de mur\n");
// 		return ;
// 	}
//
// 	while (tmp->next && new->distance < tmp->distance) //On avance tant que la distance du nouveau mur est plus petite que le mur actuek
// 		tmp = tmp->next;
// 		if (new->distance > tmp->distance)
// 			put_wall_before(s, new, tmp);
// 		else
// 			put_wall_after(new, tmp);
// }

void	add_wall_to_list(t_main *s, t_walls *new)
{
	t_walls *tmp;

	tmp = s->walls;
	// printf("new->distqnce = %f\n", new->distance);
	if (tmp == NULL) //S'il n'y a aucun mur dans la liste
	{
		s->walls = new;
		// printf("pas de mur\n");
		return ;
	}

	while (tmp->next && new->l_dist < tmp->l_dist) //On avance tant que la distance du nouveau mur est plus petite que le mur actuek
		tmp = tmp->next;
	if (new->l_dist == tmp->l_dist)
	{
		if (new->b_dist < tmp->b_dist)
			put_wall_before(s, new, tmp);
		else
			put_wall_after(new, tmp);
	}
	else if (new->l_dist > tmp->l_dist)
		put_wall_before(s, new, tmp);
	else
		put_wall_after(new, tmp);
}
