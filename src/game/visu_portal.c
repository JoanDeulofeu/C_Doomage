#include "doom.h"

int		check_walls_lenght(t_dpos beg_wall1, t_dpos end_wall1, t_dpos beg_wall2, t_dpos end_wall2)
{
	printf("%f et %f\n", ft_dist_t_dpos(beg_wall1, end_wall1), ft_dist_t_dpos(beg_wall2, end_wall2));
	if (ft_dist_t_dpos(beg_wall1, end_wall1) == ft_dist_t_dpos(beg_wall2, end_wall2))
		return (1);
	else
		return (0);
}

int		ft_get_other_sector_portal(t_main *s, int id_portal, int sector_id, int *id_portal_out)
{
	t_sector	*sct;
	t_int		*wall;

	sct = s->sector;
	while (sct)
	{
		if (sct->id == sector_id)
			sct = sct->next;
		wall = sct->wall;
		while (wall)
		{
			if (wall->value == id_portal)
			{
				*id_portal_out = wall->id;
				return (sct->id);
			}
			else
				wall = wall->next;
		}
	}
	return (-1);
}

void	ft_get_coord_portal(t_main *s, int id_sector_out, int id_portal_out, t_dpos *left_portal, t_dpos *right_portal)
{
	t_sector	*sct;
	t_int		*vtx;

	sct = get_sector_by_id(s, id_sector_out);
	vtx = get_t_int_by_id(sct->vertex, id_portal_out);

	left_portal->x = vtx->ptr->x;
	left_portal->y = vtx->ptr->y;
	if (vtx->next)
	{
		right_portal->x = vtx->next->ptr->x;
		right_portal->y = vtx->next->ptr->y;
	}
	else
	{
		right_portal->x = sct->vertex->ptr->x;
		right_portal->y = sct->vertex->ptr->y;
	}
}

int		ft_print_portal(t_main *s, int x, t_dpos player, t_dpos lwall, t_dpos rwall, t_dpos lplan, t_dpos rplan, int id_portal, int id_sector)
{
	int	id_sector_out;
	int	id_portal_out;
	int	angle;
	int	left_dist;
	int	right_dist;
	int	front_dist;
	t_dpos	left_portal;
	t_dpos	right_portal;

	//trouver le sector dans lequel amene le portail et les coordonees des vtx du portal
	id_sector_out = ft_get_other_sector_portal(s, id_portal, id_sector, &id_portal_out);
	ft_get_coord_portal(s, id_sector_out, id_portal_out, &left_portal, &right_portal);
	left_portal.x *= SPACE;
	left_portal.y *= SPACE;
	right_portal.x *= SPACE;
	right_portal.y *= SPACE;
	if (check_walls_lenght(lwall, rwall, left_portal, right_portal))
		printf("true\n");

	// printf("id du secteur de destination (%d)\n", id_sector_out);
	// printf("coord du vertex du portail destinataire left(%.3f, %.3f) et right(%.3f, %.3f)\n",left_portal.x, left_portal.y, right_portal.x, right_portal.y);

	//placer et orienter le fake joueur (modif player)
	left_dist = ft_dist_t_dpos(player, lwall);
	right_dist = ft_dist_t_dpos(player, rwall);
	front_dist = ft_dist_t_dpos(lwall, rwall);
	angle = ft_find_angle_plan(left_dist, right_dist, front_dist);

	double	pct_plan; // temporaire
	double	width_wall; // temporaire
	pct_plan = (ft_dist_t_dpos(lplan, rplan) * 100.0) / WIDTHPLAN; // temporaire
	width_wall = (WIDTH * pct_plan) / 100; // temporaire
	return ((int)width_wall + x);
}
