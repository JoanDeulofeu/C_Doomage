#include "doom.h"

int		is_colliding(t_main *s)
{
	int			id;
	t_sector	*sct;
	t_int		*wall;

	if (ft_is_in_sector(s, ft_dpos_to_pos(s->col_pos)) != s->player.sector_id)
	{
		id = ft_find_wall2(s, s->player.pos, s->col_pos, 0x37f3ffff, s->player.sector_id);
		if (id == 0 )
			return (0);
		sct = get_sector_by_id(s, s->player.sector_id);
		wall = get_t_int_by_vertex_id(sct->vertex, id);
		// if (wall->wall_value == -1)
		return (wall->wall_value);
	}
	return (0);
}
