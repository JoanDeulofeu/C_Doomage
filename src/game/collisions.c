#include "doom.h"

void	tp_first_sector(t_main *s)
{
	t_sector	*sct;
	t_pos		center;

	sct = s->sector;
	if (sct)
	{
		center = ft_find_polygon_center(sct);
		s->player.r_pos.x = (center.x / METRE);
		s->player.r_pos.y = (center.y / METRE);
		// printf("s->player.r_pos x(%f) y(%f)\n", s->player.r_pos.x, s->player.r_pos.y);

		set_player(s);
		if ((s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos))) == 0)
			handle_sector_zero(s);
	}

	// printf("center.x = %d, center.y = %d\n", center.x, center.y);
}

static int	check_pos(t_main *s, t_dpos curr)
{
	if ((s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(curr))) != 0)
	{
		s->player.r_pos.x = curr.x / s->editor->space - s->editor->decal_x;
		s->player.r_pos.y = curr.y / s->editor->space - s->editor->decal_y;
		set_player(s);
		// printf("handle_sector_zero works !\n");
		return (1);
	}
	else
		return (0);
}

int		handle_sector_zero(t_main *s)
{
	int		nb;
	t_dpos	curr;

	nb = 1;
	// On cherche autour de la position du joueur
	//jusqu'à ce qu'on trouve un endroit où le placer
	// printf("blop.\n");
	if (ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos)) == 0)
	{
		// printf ("secyeur 0\n");
		while (nb < 100 * s->editor->space)
		{
			curr = s->player.pos;
			curr.x = s->player.pos.x + nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.pos.x - nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.pos.x;
			curr.y = s->player.pos.y + nb;
			if (check_pos(s, curr))
				return (1);
			curr.y = s->player.pos.y - nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.pos.x - nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.pos.x + nb;
			if (check_pos(s, curr))
				return (1);
			curr.y += nb * 2;
			if (check_pos(s, curr))
				return (1);
			curr.x -= nb * 2;
			if (check_pos(s, curr))
				return (1);
			nb++;
			// printf("%d\n", nb);
		}
		printf("Pas reussi a trouver un endroit où se tp.\n");
		tp_first_sector(s);
		// handle_error(s, 0);
	}
	return (0);
}

void 		check_collectible(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->type == item && sprite->destroy == 0 && sprite->r_dist < 0.2)
			sprite->destroy = 1;
		sprite = sprite->next;
	}
}

int			check_col(t_main *s, t_dpos haut, t_dpos bas)
{
	int id;
	t_sector	*sct;
	t_int		*wall;

	id = ft_find_wall2(s, haut, bas, 0x37f3ffff, s->player.sector_id);
	if (id != 0)
	{
		sct = get_sector_by_id(s, s->player.sector_id);
		wall = get_t_int_by_vertex_id(sct->vertex, id);
		return (wall->wall_value);
	}
	else
		return (0);
}

int			is_colliding(t_main *s, t_dpos target)
{
	int			id;
	// t_sector	*sct;
	// t_int		*wall;
	t_dpos		haut;
	t_dpos		bas;
	int			value;

	target.x *= METRE;
	target.y *= METRE;
	value = (s->editor->anchor_size / 1.2);
	value = (s->editor->anchor_size / 1.2);
	haut = target;
	bas = target;
	haut.x = target.x + value;
	bas.x = target.x - value;
	if ((id = (check_col(s, haut, bas))) != 0)
		return (id);
	haut = target;
	bas = target;
	haut.y = target.y - value;
	bas.y = target.y + value;
	if ((id = (check_col(s, haut, bas))) != 0)
		return (id);
	haut.x = target.x - value;
	bas.x = target.x + value;
	if ((id = (check_col(s, haut, bas))) != 0)
		return (id);
	haut.x = target.x + value;
	bas.x = target.x - value;
	if ((id = (check_col(s, haut, bas))) != 0)
		return (id);
	return (0);
}
