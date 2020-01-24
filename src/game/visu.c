#include "doom.h"

int 		test_new_pos(t_main *s, t_visu *vs, t_dpos player)
{
	double	l_angle;
	double	r_angle;
	t_visu	save;

	save = *vs;
	l_angle = vs->angle + s->player.demi_fov;
	l_angle = l_angle > 360 ? l_angle - 360 : l_angle;
	r_angle = vs->angle - s->player.demi_fov;
	r_angle = r_angle < 0 ? r_angle + 360: r_angle;
	vs->left_point.x = player.x + cos(to_rad(l_angle)) * 10000;
	vs->left_point.y = player.y - sin(to_rad(l_angle)) * 10000;
	vs->begin_wall_id = ft_find_wall2(s, player, vs->left_point, APPLE_GREEN, vs->sct_id);
	vs->right_point.x = player.x + cos(to_rad(r_angle)) * 10000;
	vs->right_point.y = player.y - sin(to_rad(r_angle)) * 10000;
	vs->end_wall_id = ft_find_wall2(s, player, vs->right_point, PINK, vs->sct_id);
	if(vs->end_wall_id == 0 && vs->begin_wall_id != 0)
		vs->end_wall_id = get_t_int_by_vertex_id(get_sector_by_id(s, vs->sct_id)->vertex,
		vs->begin_wall_id)->next->ptr->id;
	if (s->portal_nb == 0 && (vs->end_wall_id == 0 || vs->begin_wall_id ==0))
	{
		*vs = save;
		return (0);
	}
	else
		return (1);
}

t_visu		move_player_near_portal(t_main *s, t_visu vs)
{
	int		nb;
	t_dpos	curr;

	nb = 1;
	// On cherche autour de la position du joueur
	//jusqu'à ce qu'on trouve un endroit où le placer
	// printf("blop.\n");
		// printf ("secyeur 0\n");
	while (nb < 100)
	{
		curr = s->player.m_pos;
		curr.x = s->player.m_pos.x + nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.x = s->player.m_pos.x - nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.x = s->player.m_pos.x;
		curr.y = s->player.m_pos.y + nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.y = s->player.m_pos.y - nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.x = s->player.m_pos.x - nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.x = s->player.m_pos.x + nb;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.y += nb * 2;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		curr.x -= nb * 2;
		if (test_new_pos(s, &vs, curr))
			return (vs);
		nb++;
		// printf("%d\n", nb);
	}
	return (vs);
}

int			ft_find_wall2(t_main *s, t_dpos player, t_dpos point, Uint32 color, int sct_id)
{
	t_sector	*sct;
	t_int		*s_vtx;
	t_4dpos		pos;
	int			id_wall = 0;
	int			i;
	int			dist;
	int			new_dist;
	(void)color; //a enlever

	dist = 100000;
	new_dist = 0;
	sct = s->sector;
	if (sct_id == 0)
		handle_error(s, SECTOR_ERROR);
	while (sct_id != sct->id)
		sct = sct->next;
	s_vtx = sct->vertex;
	i = 0;
	s->count_wall = 0;
	while (i++ < sct->vertex->prev->id)
	{
		pos.pos1 = s_vtx->ptr->m_pos;
		pos.pos2 = s_vtx->next->ptr->m_pos;
		pos.pos3 = point;
		pos.pos4 = player;
		if ((new_dist = ft_find_intersection(s, pos, 1)) > 0)
		{
			s->line.x1 = ft_dpos_to_pos(to_edi_coord(s, player)).x;
			s->line.y1 = ft_dpos_to_pos(to_edi_coord(s, player)).y;
			s->line.x2 = ft_dpos_to_pos(to_edi_coord(s, point)).x;
			s->line.y2 = ft_dpos_to_pos(to_edi_coord(s, point)).y;
			get_line(s, color, 1);
			s->count_wall++;
			if (new_dist < dist && new_dist != 0 && new_dist != -1)
			{
				id_wall = s_vtx->ptr->id;
				dist = new_dist;
			}
		}
		s_vtx = s_vtx->next;
	}
	return (id_wall);
}

t_visu		ft_place_view_plan(t_main *s, t_dpos player, double angle, Uint32 color)
{
	t_dpos	ctr_p; //center plan
	t_visu	vs;

	ft_bzero(&vs, sizeof(t_visu));
	ctr_p.x = player.x + cos(to_rad(angle)) * METRE;
	ctr_p.y = player.y - sin(to_rad(angle)) * METRE;
	vs.left_plan.x = ctr_p.x + cos(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.left_plan.y = ctr_p.y - sin(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.right_plan.x = ctr_p.x + cos(to_rad(angle - 90)) * WIDTHPLAN / 2;
	vs.right_plan.y = ctr_p.y - sin(to_rad(angle - 90)) * WIDTHPLAN / 2;
	// s->line.x1 = ft_dpos_to_pos(to_edi_coord(s, vs.left_plan)).x;
	// s->line.y1 = ft_dpos_to_pos(to_edi_coord(s, vs.left_plan)).y;
	// s->line.x2 = ft_dpos_to_pos(to_edi_coord(s, vs.right_plan)).x;
	// s->line.y2 = ft_dpos_to_pos(to_edi_coord(s, vs.right_plan)).y;
	// get_line(s, color, 1);
	return (vs);
}

t_visu		get_walls_to_draw(t_main *s, t_dpos player, t_visu vs)
{
	double	l_angle;
	double	r_angle;

	l_angle = vs.angle + s->player.demi_fov;
	l_angle = l_angle > 360 ? l_angle - 360 : l_angle;
	r_angle = vs.angle - s->player.demi_fov;
	r_angle = r_angle < 0 ? r_angle + 360: r_angle;
	vs.left_point.x = player.x + cos(to_rad(l_angle)) * 10000;
	vs.left_point.y = player.y - sin(to_rad(l_angle)) * 10000;
	vs.begin_wall_id = ft_find_wall2(s, player, vs.left_point, YELLOW, vs.sct_id);
	if (vs.begin_wall_id == 0 && s->player.m_pos.x == player.x && s->player.m_pos.y == player.y)
		printf("vs.begin_wall_id = 0\n");
	vs.begin = s->tmp_intersect;
	vs.right_point.x = player.x + cos(to_rad(r_angle)) * 10000;
	vs.right_point.y = player.y - sin(to_rad(r_angle)) * 10000;
	vs.end_wall_id = ft_find_wall2(s, player, vs.right_point, GREEN, vs.sct_id);
	if(vs.end_wall_id == 0 && vs.begin_wall_id != 0)
		vs.end_wall_id = get_t_int_by_vertex_id(get_sector_by_id(s, vs.sct_id)->vertex,
		vs.begin_wall_id)->next->ptr->id;
	vs.end = s->tmp_intersect;
	vs.vtx_gauche = get_t_int_by_vertex_id(vs.sct->vertex, vs.begin_wall_id);
	vs.vtx_droite = get_t_int_by_vertex_id(vs.sct->vertex, vs.end_wall_id);
	vs.player = player;
	if (s->player.m_pos.x == player.x && s->player.m_pos.y == player.y && (vs.end_wall_id == 0 || vs.begin_wall_id == 0))
	{
		printf("true\n");
		vs = move_player_near_portal(s, vs);
	}
	return(vs);
}

void		ft_visu_joan(t_main *s)
{

	t_visu	vs;
	t_dpos	player;

	player = s->player.m_pos;
	vs.vtx_droite = NULL;
	vs.vtx_gauche = NULL;
	vs = ft_place_view_plan(s, player, s->player.angle, 0x4bd9ffff);
	vs.sct_id = s->player.sector_id;
	vs.sct = get_sector_by_id(s, s->player.sector_id);
	s->player.foot_height = vs.sct->floor + s->player.jump_height;
	s->player.ceiling_height = vs.sct->ceiling;
	s->player.floor_height = vs.sct->floor;
	vs.right_ceiling_limit.x = WIDTH;
	vs.left_floor_limit.y = HEIGHT;
	vs.right_floor_limit.x = WIDTH;
	vs.right_floor_limit.y = HEIGHT;
	vs.angle = angle_mod(s->player.angle);
	vs = get_walls_to_draw(s, player, vs);
	// printf("\n\n\n");
	ft_draw_visu(s, get_sector_by_id(s, s->player.sector_id), vs);
	// printf("\n");

}
