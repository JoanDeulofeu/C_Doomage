#include "doom.h"

int			ft_find_wall2(t_main *s, t_dpos player, t_dpos point, Uint32 color, int sct_id)
{
	t_sector	*sct;
	t_int		*s_vtx;
	t_dpos		wall1;
	t_dpos		wall2;
	int			id_wall = 0;
	int			i;
	int			dist;
	int			new_dist;

	dist = 100000;
	new_dist = 0;
	sct = s->sector;
	if (sct_id == 0)
		handle_error(s, SECTOR_ERROR);
	while (sct_id != sct->id)
		sct = sct->next;
	s_vtx = sct->vertex;
	i = 0;
	while (i++ < sct->vertex->prev->id)
	{
		wall1.x = s_vtx->ptr->x * METRE;
		wall1.y = s_vtx->ptr->y * METRE;
		wall2.x = s_vtx->next->ptr->x * METRE;
		wall2.y = s_vtx->next->ptr->y * METRE;
		// printf("wall1(%.1f, %.1f) | wall2(%.1f, %.1f) | player(%.1f, %.1f) | point(%.1f, %.1f)\n", wall1.x, wall1.y, wall2.x, wall2.y, player.x, player.y, point.x, point.y);
		(void)color;
		if (sct_id == 2)
		{
			s->line.x1 = ft_dpos_to_pos(to_edi_coord(s, player)).x;
			s->line.y1 = ft_dpos_to_pos(to_edi_coord(s, player)).y;
			s->line.x2 = ft_dpos_to_pos(to_edi_coord(s, point)).x;
			s->line.y2 = ft_dpos_to_pos(to_edi_coord(s, point)).y;
			// get_line(s, color, 1);
		}
		if ((new_dist = ft_find_intersection(s, wall1, wall2, point, player, 1)) > 0)
		{
			s->line.x1 = ft_dpos_to_pos(to_edi_coord(s, player)).x;
			s->line.y1 = ft_dpos_to_pos(to_edi_coord(s, player)).y;
			s->line.x2 = ft_dpos_to_pos(to_edi_coord(s, point)).x;
			s->line.y2 = ft_dpos_to_pos(to_edi_coord(s, point)).y;
			get_line(s, color, 1);
			// printf("on test le mur[%d] : dist = %d, new_dist = %d\n", s_vtx->id, dist, new_dist);
			// printf("point(%.1f, %.1f), player(%.1f, %.1f), wall1(%.1f, %.1f), wall2(%.1f, %.1f)\n", point.x, point.y, player.x, player.y, wall1.x / METRE, wall1.y / METRE, wall2.x / METRE, wall2.y / METRE);
			// printf("play.y = %f | point.y = %f\n", player.y + s->editor->decal_y, point.y + s->editor->decal_y);
			// return (id_wall);
			if (new_dist < dist && new_dist != 0 && new_dist != -1)
			{
				// printf("on test le mur[%d] : dist = %d, new_dist = %d\n", s_vtx->id, dist, new_dist);
				id_wall = s_vtx->ptr->id;
				// printf("vertex = %d\n", id_wall);
				dist = new_dist;
			}

		}
		// id_wall++;
		s_vtx = s_vtx->next;
	}
	// printf("wall =  %d\n", get_t_int_by_vertex_id(sct->vertex, id_wall)->id);
	return (id_wall);
}

t_visu		ft_place_view_plan(t_main *s, t_dpos player, double angle, Uint32 color)
{
	// printf("chocolat\n");
	t_dpos	ctr_p; //center plan
	t_visu	vs;

	ctr_p.x = player.x + cos(to_rad(angle)) * METRE;
	ctr_p.y = player.y - sin(to_rad(angle)) * METRE;
	vs.left_plan.x = ctr_p.x + cos(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.left_plan.y = ctr_p.y - sin(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.right_plan.x = ctr_p.x + cos(to_rad(angle - 90)) * WIDTHPLAN / 2;
	vs.right_plan.y = ctr_p.y - sin(to_rad(angle - 90)) * WIDTHPLAN / 2;
	// s->sky.player = player;
	// s->sky.left_point = vs.left_plan;
	// s->sky.right_point = vs.right_plan;
	s->line.x1 = ft_dpos_to_pos(to_edi_coord(s, vs.left_plan)).x;
	s->line.y1 = ft_dpos_to_pos(to_edi_coord(s, vs.left_plan)).y;
	s->line.x2 = ft_dpos_to_pos(to_edi_coord(s, vs.right_plan)).x;
	s->line.y2 = ft_dpos_to_pos(to_edi_coord(s, vs.right_plan)).y;
	get_line(s, color, 1);
	return (vs);
}

t_visu		get_walls_to_draw(t_main *s, t_dpos player, double l_angle, double r_angle, t_visu vs)
{
	// printf("entree-----------\n");
	vs.left_point.x = player.x + cos(to_rad(l_angle)) * 10000;
	vs.left_point.y = player.y - sin(to_rad(l_angle)) * 10000;
	vs.begin_wall_id = ft_find_wall2(s, player, vs.left_point, 0xffed00ff, vs.sct_id);
	// printf("begin_wall id = %d\n", vs.begin_wall_id);
	// if(vs.begin_wall_id == 0)
	// 	exit(0);
	vs.begin = s->tmp_intersect;
	// printf("------MUR DROITE------\n");
	vs.right_point.x = player.x + cos(to_rad(r_angle)) * 10000;
	vs.right_point.y = player.y - sin(to_rad(r_angle)) * 10000;
	vs.end_wall_id = ft_find_wall2(s, player, vs.right_point, 0x59ff00ff, vs.sct_id);
	if(vs.end_wall_id == 0 && vs.begin_wall_id != 0)
		vs.end_wall_id = get_t_int_by_vertex_id(get_sector_by_id(s, vs.sct_id)->vertex,
		vs.begin_wall_id)->next->ptr->id;
	// 	exit(0);
	vs.end = s->tmp_intersect;
	// printf("end_wall id = %d\n", vs.end_wall_id);
	// printf("sct = %d, sct->vertex->id = %d\n", vs.sct->id, vs.sct->vertex->id);
	vs.vtx_gauche = get_t_int_by_vertex_id(vs.sct->vertex, vs.begin_wall_id);
	vs.vtx_droite = get_t_int_by_vertex_id(vs.sct->vertex, vs.end_wall_id);
	// printf("id 1 = %d, id 2 = %d\n", vs.vtx_gauche->id, vs.vtx_droite->id);
	// if (!vs.vtx_gauche && !vs.vtx_droite)
	// 	exit(-1);
	// printf("TEST vs.end (%.1f, %.1f)\n", vs.end.x, vs.end.y);
	vs.player = player;
	// printf("\nsortie-----------\n\n");
	return(vs);
}

void		ft_visu_joan(t_main *s, const unsigned char *keys)
{
	double	angle_left;
	double	angle_right;
	double	demi_fov;
	t_visu	vs;
	t_dpos	player;

	ft_bzero(&vs, sizeof(t_visu));
	(void)keys;
	player = s->player.m_pos;
	vs.vtx_droite = NULL;
	vs.vtx_gauche = NULL;

	vs = ft_place_view_plan(s, player, s->player.angle, 0x4bd9ffff);
	vs.prev_sct_id = 0; //pas de sct precedent...
	vs.sct_id = s->player.sector_id;
	vs.sct = get_sector_by_id(s, s->player.sector_id);

	vs.left_ceiling_limit.x = 0;
	vs.left_ceiling_limit.y = 0;
	vs.right_ceiling_limit.x = WIDTH;
	vs.right_ceiling_limit.y = 0;
	vs.left_floor_limit.x = 0;
	vs.left_floor_limit.y = HEIGHT;
	vs.right_floor_limit.x = WIDTH;
	vs.right_floor_limit.y = HEIGHT;

	demi_fov = ft_find_angle_plan(ft_dist_t_dpos(player, vs.left_plan), METRE, WIDTHPLAN / 2);
	angle_left = s->player.angle + demi_fov;
	angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
	angle_right = s->player.angle - demi_fov;
	angle_right = angle_right < 0 ? angle_right + 360: angle_right;
	vs.angle = angle_mod(s->player.angle);
	vs = get_walls_to_draw(s, player, angle_left, angle_right, vs);
	// printf("\n\n\n");
	ft_draw_visu(s, get_sector_by_id(s, s->player.sector_id), vs);
}
