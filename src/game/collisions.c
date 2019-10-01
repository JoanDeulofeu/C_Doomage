#include "doom.h"

t_dpos	handle_sector_zero(t_main *s, const unsigned char *keys)
{
	int		nb;
	t_pos	curr;

	nb = 1;
	(void) keys;
	while (1)
	{
		curr = ft_dpos_to_pos(s->player.pos);
		curr.x = s->player.pos.x + nb;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		curr.x = s->player.pos.x - nb;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		curr.x = s->player.pos.x;
		curr.y = s->player.pos.y + nb;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		curr.y = s->player.pos.y - nb;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		curr.x = s->player.pos.x - nb;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		curr.x = s->player.pos.x + nb;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		curr.y += nb * 2;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		curr.x -= nb * 2;
		if ((s->player.sector_id = ft_is_in_sector(s, curr)) != 0)
			return (ft_pos_to_dpos(curr));
		// 	return (curr);
		nb++;
	}
}

int		is_colliding(t_main *s)
{
	int			id;
	t_sector	*sct;
	t_int		*wall;

	if (ft_is_in_sector(s, ft_dpos_to_pos(to_edi_coord(s, s->col_pos))) != s->player.sector_id)
	{
		id = ft_find_wall2(s, s->player.m_pos, s->col_pos, 0x37f3ffff, s->player.sector_id);
		// printf("id = %d\n", id);
		if (id == 0 )
			return (0);
		sct = get_sector_by_id(s, s->player.sector_id);
		wall = get_t_int_by_vertex_id(sct->vertex, id);
		// printf("wall value = %d\n", wall->wall_value);
		// if (wall->wall_value == -1)
		return (wall->wall_value);
	}
	return (0);
}
