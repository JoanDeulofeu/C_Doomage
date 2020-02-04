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
		if ((s->player.sector_id = ft_is_in_sector(s, s->player.m_pos)) == 0)
			handle_sector_zero(s);
	}

	// printf("center.x = %d, center.y = %d\n", center.x, center.y);
}

static int	check_pos(t_main *s, t_dpos curr)
{
	// printf("cur.x = %f\n", curr.x);

	if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
	{
		s->player.r_pos.x = curr.x / METRE;
		s->player.r_pos.y = curr.y / METRE;

		set_player(s);
		// printf("cur.x = %f, player.pos = %f\n", curr.x, s->player.m_pos.x);

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
	if (ft_is_in_sector(s, s->player.m_pos) == 0)
	{
		// printf ("secteur 0\n");
		while (nb < 100 * METRE)
		{
			curr = s->player.m_pos;
			curr.x = s->player.m_pos.x + nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.m_pos.x - nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.m_pos.x;
			curr.y = s->player.m_pos.y + nb;
			if (check_pos(s, curr))
				return (1);
			curr.y = s->player.m_pos.y - nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.m_pos.x - nb;
			if (check_pos(s, curr))
				return (1);
			curr.x = s->player.m_pos.x + nb;
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

void 		get_item(t_main *s, t_sprite *sprite)
{
	// printf("sprite->name = %d\n", sprite->name);
	if (sprite->name == o_shotgun)
	{
		s->player.wp_wheel[shotgun] = 1;
	}
	else if (sprite->name == o_gun)
		s->player.wp_wheel[gun] = 1;
	else if (sprite->name == jetpack)
	{
		s->player.jetpack = 1;
		s->time->jetpack_reserve = JET_TIME;
		// s->time->jetpack_ms = s->time->time_ms;
	}
	else if (sprite->name == big_s_ammo)
	{
		s->player.mun_shotgun += 5;
		if (s->player.mun_shotgun > 15)
			s->player.mun_shotgun = 15;
	}
	else if (sprite->name == big_g_ammo)
	{
		s->player.mun_gun += 10;
		if (s->player.mun_gun > 100)
			s->player.mun_gun = 100;
	}
}

void 		check_collectible(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->type == item && sprite->destroy == 0 && sprite->r_dist < 2)
		{
			get_item(s, sprite);
			sprite->destroy = 1;
		}
		sprite = sprite->next;
	}
}

void 		check_bomb(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->name == bomb && sprite->r_dist < 3.5 && sprite->set == 1)
		{
			sprite->current = 1;
			s->sct_without_ceiling = s->player.sector_id;
			s->transition_y_eye = s->player.y_eye;
			s->transition_angle = s->player.angle;
			// s->player.abs_angle = 74;
			// s->player.y_eye = 520;
			s->transition = 1;
			s->block_move = 1;
			s->time->explosion_ms = s->time->time_ms;
		}
		sprite = sprite->next;
	}
}

int			check_col(t_main *s, t_dpos haut, t_dpos bas)
{
	int id;
	t_sector	*sct;
	t_int		*wall;

	id = ft_find_wall2(s, haut, bas, S_PURPLE, s->player.sector_id);
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
