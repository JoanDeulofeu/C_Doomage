#include "doom.h"

int		ft_find_wall2(t_main *s, t_dpos point, Uint32 color)
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
	while (s->player.sector != sct->id)
		sct = sct->next;
	s_vtx = sct->vertex;
	while (s_vtx->next)
	{
		id = s_vtx->value;
		vtx = s->vertex;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		wall1.x = vtx->x * s->editor->space + s->editor->decal_x;
		wall1.y = vtx->y * s->editor->space + s->editor->decal_y;

		id = s_vtx->next->value;
		vtx = s->vertex;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		wall2.x = vtx->x * s->editor->space + s->editor->decal_x;
		wall2.y = vtx->y * s->editor->space + s->editor->decal_y;


		if (ft_find_intersection(s, wall1, wall2, s->player.pos, point) > 0)
		{
			s->line.x1 = s->player.pos.x;
			s->line.y1 = s->player.pos.y;
			s->line.x2 = point.x;
			s->line.y2 = point.y;
			get_line(s, color);
			// printf("play.y = %f | point.y = %f\n", s->player.pos.y, point.y);
			return (id_wall);
		}
		id_wall++;
		s_vtx = s_vtx->next;
	}
	s->line.x1 = s->player.pos.x;
	s->line.y1 = s->player.pos.y;
	s->line.x2 = point.x;
	s->line.y2 = point.y;
	get_line(s, color);
	return (id_wall);
}

double	ft_find_angle_plan(t_main *s, t_dpos plan_point)
{
	double a;
	double b;
	double c;

	a = ft_dist_t_dpos(s->player.pos, plan_point);
	b = METRE;
	c = WIDTHPLAN / 2;
	// printf("a(%f) + b(%f) - c(%f) / 2*a*b\n",a, b, c);
	return (to_degres(acos((powf(a, 2) + powf(b, 2) - powf(c, 2)) / (2 * a * b))));
}

void	ft_place_view_plan(t_main *s, Uint32 color)
{
	t_pos	ctr_p; //center plan
	t_visu	*vs = &s->visu;

	ctr_p.x = s->player.pos.x + cos(to_rad(s->player.angle)) * METRE;
	ctr_p.y = s->player.pos.y - sin(to_rad(s->player.angle)) * METRE;
	vs->left_plan.x = ctr_p.x + cos(to_rad(s->player.angle + 90)) * WIDTHPLAN / 2;
	vs->left_plan.y = ctr_p.y - sin(to_rad(s->player.angle + 90)) * WIDTHPLAN / 2;
	vs->right_plan.x = ctr_p.x + cos(to_rad(s->player.angle - 90)) * WIDTHPLAN / 2;
	vs->right_plan.y = ctr_p.y - sin(to_rad(s->player.angle - 90)) * WIDTHPLAN / 2;

	s->line.x1 = vs->left_plan.x;
	s->line.y1 = vs->left_plan.y;
	s->line.x2 = vs->right_plan.x;
	s->line.y2 = vs->right_plan.y;
	get_line(s, color);
}

void	ft_draw_visu(t_main *s, t_visu *vs)
{
	t_pos		end_first_wall;
	t_sector	*sct;
	t_int		*vtx;

	sct = s->sector;
	while (s->player.sector != sct->id)
		sct = sct->next;
	vtx = sct->vertex;
	while (vtx->id != vs->begin_wall + 1) // trouver le deuxieme vertex du premier mur
	{
		vtx = vtx->next;
		if (vtx == NULL)
		{
			vtx = sct->vertex;
			break ;
		}
	}
	end_first_wall.x = vtx->ptr->x;
	end_first_wall.y = vtx->ptr->y;
	printf("wall n%d et vertex du mur = %d\n", vs->begin_wall, vtx->id);
	printf("coordonees du vertex (%d, %d)\n",end_first_wall.x, end_first_wall.y);
}

void	ft_visu_joan(t_main *s)
{
	double	angle_left;
	double	angle_right;
	t_dpos	point;
	t_visu	*vs = &s->visu;

	if ((s->player.sector = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos))) == 0)
		return ;
	ft_place_view_plan(s, 0x4bd9ffff);
	angle_left = s->player.angle + ft_find_angle_plan(s, vs->left_plan);
	angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
	angle_right = s->player.angle - ft_find_angle_plan(s, vs->right_plan);
	angle_right = angle_right < 0 ? angle_right + 360: angle_right;

	point.x = s->player.pos.x + cos(to_rad(angle_left)) * 2000;
	point.y = s->player.pos.y - sin(to_rad(angle_left)) * 2000;
	vs->begin_wall = ft_find_wall2(s, point, 0xffed00ff);
	vs->begin.x = s->tmp_intersect.x;
	vs->begin.y = s->tmp_intersect.y;

	point.x = s->player.pos.x + cos(to_rad(angle_right)) * 2000;
	point.y = s->player.pos.y - sin(to_rad(angle_right)) * 2000;
	vs->end_wall = ft_find_wall2(s, point, 0x59ff00ff);
	vs->end.x = s->tmp_intersect.x;
	vs->end.y = s->tmp_intersect.y;
	ft_draw_visu(s, vs);

	// printf("mur gauche = %d\nmur droite = %d\n", mur1, mur2);
	// printf("angle gauche = %f\nangle droite = %f\n\n", angle_left, angle_right);

}










//lol
