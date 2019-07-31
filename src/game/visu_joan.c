#include "doom.h"

int		ft_find_wall2(t_main *s, t_dpos player, t_dpos point, Uint32 color)
{
	t_sector	*sct;
	t_vertex	*vtx;
	t_int		*s_vtx;
	t_dpos		wall1;
	t_dpos		wall2;
	// t_dpos		i_line; //ligne imaginaire
	int			id = 0;
	int			id_wall = 1;

	sct = s->sector;
	while (s->player.sector_id != sct->id)
		sct = sct->next;
	s_vtx = sct->vertex;
	while (s_vtx)
	{
		wall1.x = s_vtx->ptr->x * METRE;
		wall1.y = s_vtx->ptr->y * METRE;

		printf("wall1.x = %f\n", wall1.x);
		if (s_vtx->next != NULL)
		{
			wall2.x = s_vtx->next->ptr->x * METRE;
			wall2.y = s_vtx->next->ptr->y * METRE;
		}
		else
		{
			wall2.x = sct->vertex->ptr->x * METRE;
			wall2.y = sct->vertex->ptr->y * METRE;
		}

		if (ft_find_intersection(s, wall1, wall2, player, point) > 0)
		{
			s->line.x1 = player.x + s->editor->decal_x;
			s->line.y1 = player.y + s->editor->decal_y;
			s->line.x2 = point.x + s->editor->decal_x;
			s->line.y2 = point.y + s->editor->decal_y;
			get_line(s, color);
			// printf("play.y = %f | point.y = %f\n", player.y + s->editor->decal_y, point.y + s->editor->decal_y);
			return (id_wall);
		}
		id_wall++;
		s_vtx = s_vtx->next;
	}
	return (id_wall);
}

double	ft_find_angle_plan(t_dpos player, t_dpos plan_point)
{
	double a;
	double b;
	double c;

	a = ft_dist_t_dpos(player, plan_point);
	b = METRE;
	c = WIDTHPLAN / 2;
	// printf("a(%f) + b(%f) - c(%f) / 2*a*b\n",a, b, c);
	return (to_degres(acos((powf(a, 2) + powf(b, 2) - powf(c, 2)) / (2 * a * b))));
}

void	ft_place_view_plan(t_main *s, t_dpos player, Uint32 color)
{
	t_pos	ctr_p; //center plan
	t_visu	*vs = &s->visu;

	ctr_p.x = player.x + cos(to_rad(s->player.angle)) * METRE;
	ctr_p.y = player.y - sin(to_rad(s->player.angle)) * METRE;
	vs->left_plan.x = ctr_p.x + cos(to_rad(s->player.angle + 90)) * WIDTHPLAN / 2;
	vs->left_plan.y = ctr_p.y - sin(to_rad(s->player.angle + 90)) * WIDTHPLAN / 2;
	vs->right_plan.x = ctr_p.x + cos(to_rad(s->player.angle - 90)) * WIDTHPLAN / 2;
	vs->right_plan.y = ctr_p.y - sin(to_rad(s->player.angle - 90)) * WIDTHPLAN / 2;

	s->line.x1 = vs->left_plan.x + s->editor->decal_x;
	s->line.y1 = vs->left_plan.y + s->editor->decal_y;
	s->line.x2 = vs->right_plan.x + s->editor->decal_x;
	s->line.y2 = vs->right_plan.y + s->editor->decal_y;
	get_line(s, color);
}

void	ft_visu_joan(t_main *s)
{
	double	angle_left;
	double	angle_right;
	t_dpos	point;
	t_visu	*vs = &s->visu;
	t_dpos	player;

	if ((s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos))) == 0)
		return ;
	player.x = s->player.r_pos.x * METRE;
	player.y = s->player.r_pos.y * METRE;
	ft_place_view_plan(s, player, 0x4bd9ffff);

	angle_left = s->player.angle + ft_find_angle_plan(player, vs->left_plan);
	angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
	angle_right = s->player.angle - ft_find_angle_plan(player, vs->right_plan);
	angle_right = angle_right < 0 ? angle_right + 360: angle_right;

	point.x = player.x + cos(to_rad(angle_left)) * 2000;
	point.y = player.y - sin(to_rad(angle_left)) * 2000;
	vs->begin_wall_id = ft_find_wall2(s, player, point, 0xffed00ff);
	vs->begin.x = s->tmp_intersect.x;
	vs->begin.y = s->tmp_intersect.y;

	point.x = player.x + cos(to_rad(angle_right)) * 2000;
	point.y = player.y - sin(to_rad(angle_right)) * 2000;
	vs->end_wall_id = ft_find_wall2(s, player, point, 0x59ff00ff);
	vs->end.x = s->tmp_intersect.x;
	vs->end.y = s->tmp_intersect.y;
	ft_draw_visu(s, player, vs);

	// printf("mur gauche = %d\nmur droite = %d\n", vs->begin_wall_id, vs->end_wall_id);
	// printf("angle gauche = %.2f\nangle droite = %.2f\n\n", angle_left, angle_right);

}










//lol
