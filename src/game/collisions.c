#include "doom.h"

void tp_first_sector(t_main *s)
{
	t_sector	*sct;
	t_pos		center;

	sct = s->sector;
	if (sct)
	{
		center = ft_find_polygon_center(sct);
		s->player.r_pos.x = center.x / s->editor->space - s->editor->decal_x;
		s->player.r_pos.y = center.y / s->editor->space - s->editor->decal_y;
		set_player(s);
		if ((s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.r_pos))) == 0)
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
		return (1);
	}
	else
		return (0);
}

void		handle_sector_zero(t_main *s)
{
	int		nb;
	t_dpos	curr;

	nb = 1;
	// On cherche autour de la position du joueur
	//jusqu'à ce qu'on trouve un endroit où le placer
	// printf("blop.\n");
	if (s->player.sector_id == 0)
	{
		while (nb < 1000)
		{
			curr = s->player.pos;
			curr.x = s->player.pos.x + nb;
			if (check_pos(s, curr))
				return ;
			curr.x = s->player.pos.x - nb;
			if (check_pos(s, curr))
				return ;
			curr.x = s->player.pos.x;
			curr.y = s->player.pos.y + nb;
			if (check_pos(s, curr))
				return ;
			curr.y = s->player.pos.y - nb;
			if (check_pos(s, curr))
				return ;
			curr.x = s->player.pos.x - nb;
			if (check_pos(s, curr))
				return ;
			curr.x = s->player.pos.x + nb;
			if (check_pos(s, curr))
				return ;
			curr.y += nb * 2;
			if (check_pos(s, curr))
				return ;
			curr.x -= nb * 2;
			if (check_pos(s, curr))
				return ;
			nb++;
		}
		printf("Pas reussi a trouver un endroit où se tp.\n");
		tp_first_sector(s);
		// handle_error(s, 0);
	}
}

int			is_colliding(t_main *s)
{
	int			id;
	t_sector	*sct;
	t_int		*wall;

	if (ft_is_in_sector(s, ft_dpos_to_pos(to_edi_coord(s, s->col_pos)))!= s->player.sector_id)
	{

		id = ft_find_wall2(s, s->player.m_pos, s->col_pos, 0x37f3ffff,
			s->player.sector_id);
		// printf("id = %d\n", id);
		if (id == 0)
			return (0);
		sct = get_sector_by_id(s, s->player.sector_id);
		wall = get_t_int_by_vertex_id(sct->vertex, id);
		// printf("wall value = %d\n", wall->wall_value);
		// if (wall->wall_value == -1)
		return (wall->wall_value);
	}
	return (0);
}
