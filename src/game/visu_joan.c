#include "doom.h"

int		ft_find_wall2(t_main *s, t_dpos player, t_dpos point, Uint32 color, int sct_id)
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
		if (sct_id == 2)
		{
			s->line.x1 = player.x + s->editor->decal_x;
			s->line.y1 = player.y + s->editor->decal_y;
			s->line.x2 = point.x + s->editor->decal_x;
			s->line.y2 = point.y + s->editor->decal_y;
			get_line(s, color, 1);
		}
		if ((new_dist = ft_find_intersection(s, wall1, wall2, point, player, 1)) > 0)
		{
			s->line.x1 = player.x + s->editor->decal_x;
			s->line.y1 = player.y + s->editor->decal_y;
			s->line.x2 = point.x + s->editor->decal_x;
			s->line.y2 = point.y + s->editor->decal_y;
			get_line(s, color, 1);
			// printf("on test le mur[%d] : dist = %d, new_dist = %d\n", s_vtx->id, dist, new_dist);
			// printf("point(%.1f, %.1f), player(%.1f, %.1f), wall1(%.1f, %.1f), wall2(%.1f, %.1f)\n", point.x, point.y, player.x, player.y, wall1.x / METRE, wall1.y / METRE, wall2.x / METRE, wall2.y / METRE);
			// printf("play.y = %f | point.y = %f\n", player.y + s->editor->decal_y, point.y + s->editor->decal_y);
			// return (id_wall);
			if (new_dist < dist && new_dist != 0 && new_dist != -1)
			{
				// printf("on test le mur[%d] : dist = %d, new_dist = %d\n", s_vtx->id, dist, new_dist);
				id_wall = s_vtx->ptr->id;
				dist = new_dist;
			}

		}
		// id_wall++;
		s_vtx = s_vtx->next;
	}
	// printf("wall =  %d\n", get_t_int_by_vertex_id(sct->vertex, id_wall)->id);
	return (id_wall);
}

t_visu	ft_place_view_plan(t_main *s, t_dpos player, double angle, Uint32 color)
{
	t_dpos	ctr_p; //center plan
	t_visu	vs;

	ctr_p.x = player.x + cos(to_rad(angle)) * METRE;
	ctr_p.y = player.y - sin(to_rad(angle)) * METRE;
	vs.left_plan.x = ctr_p.x + cos(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.left_plan.y = ctr_p.y - sin(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.right_plan.x = ctr_p.x + cos(to_rad(angle - 90)) * WIDTHPLAN / 2;
	vs.right_plan.y = ctr_p.y - sin(to_rad(angle - 90)) * WIDTHPLAN / 2;

	s->line.x1 = vs.left_plan.x + s->editor->decal_x;
	s->line.y1 = vs.left_plan.y + s->editor->decal_y;
	s->line.x2 = vs.right_plan.x + s->editor->decal_x;
	s->line.y2 = vs.right_plan.y + s->editor->decal_y;
	get_line(s, color, 1);
	return(vs);
}

t_visu get_walls_to_draw(t_main *s, t_dpos player, double l_angle, double r_angle, t_visu vs)
{
	vs.left_point.x = player.x + cos(to_rad(l_angle)) * 2000;
	vs.left_point.y = player.y - sin(to_rad(l_angle)) * 2000;
	vs.begin_wall_id = ft_find_wall2(s, player, vs.left_point, 0xffed00ff, vs.sct_id);
	// printf("wall_id = %d\n", vs.begin_wall_id);
	vs.begin.x = s->tmp_intersect.x;
	vs.begin.y = s->tmp_intersect.y;
// printf("------MUR DROITE------\n");
	vs.right_point.x = player.x + cos(to_rad(r_angle)) * 2000;
	vs.right_point.y = player.y - sin(to_rad(r_angle)) * 2000;
	vs.end_wall_id = ft_find_wall2(s, player, vs.right_point, 0x59ff00ff, vs.sct_id);
	vs.end.x = s->tmp_intersect.x;
	vs.end.y = s->tmp_intersect.y;
	vs.player = player;
	return(vs);
}

void	ft_visu_joan(t_main *s)
{
	double	angle_left;
	double	angle_right;
	double	demi_fov;
	// t_dpos	point;
	t_visu	vs;
	// t_visu	*vsu = &s->visu;
	t_dpos	player;

	if ((s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos))) == 0)
		return ;
	player.x = s->player.r_pos.x * METRE;
	player.y = s->player.r_pos.y * METRE;
	// printf("s->visu = %f et vs->left_plan = %f\n", s->visu.left_plan.x, vs.left_plan.x);
	vs = ft_place_view_plan(s, player, s->player.angle, 0x4bd9ffff);
	vs.sct_id = s->player.sector_id;

	demi_fov = ft_find_angle_plan(ft_dist_t_dpos(player, vs.left_plan), METRE, WIDTHPLAN / 2);
	// printf("demi_fov = %f\n",demi_fov);
	angle_left = s->player.angle + demi_fov;
	angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
	angle_right = s->player.angle - demi_fov;
	angle_right = angle_right < 0 ? angle_right + 360: angle_right;
	vs = get_walls_to_draw(s, player, angle_left, angle_right, vs);

	ft_draw_visu(s, player, get_sector_by_id(s, s->player.sector_id), vs);
// printf("------  SORTIE  ------\n");

	// printf("mur gauche = %d\nmur droite = %d\n", vs.begin_wall_id, vs.end_wall_id);
	// printf("angle gauche = %.2f\nangle droite = %.2f\n\n", angle_left, angle_right);

}










//lol <== hey... è.é
