#include "doom.h"

int			check_portal_validity_player(t_main *s, t_int *vtx, t_visu *vs)
{
	t_4dpos pos;
	t_dpos	l_plan;
	t_dpos	r_plan;
	int		dist;

	pos.pos1 = vs->left_point;
	pos.pos2 = vs->player;
	pos.pos3 = vtx->ptr->m_pos;
	pos.pos4 = vtx->next->ptr->m_pos;
	dist = ft_find_intersection(s, pos, 1);
	if (dist > 0)
		pos.pos1 = s->tmp_intersect;
	else
		pos.pos1 = pos.pos3;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	l_plan = s->tmp_intersect;

	pos.pos1 = vs->right_point;
	pos.pos3 = vtx->ptr->m_pos;
	pos.pos4 = vtx->next->ptr->m_pos;
	dist = ft_find_intersection(s, pos, 1);
	if (dist > 0)
		pos.pos1 = s->tmp_intersect;
	else
		pos.pos1 = pos.pos4;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	r_plan = s->tmp_intersect;

	// printf("dist left = %f, dist right = %f\n", ft_dist_t_dpos(l_plan, vs->left_plan), ft_dist_t_dpos(r_plan, vs->left_plan));

	// if (vtx->ptr->id == 79)
	// {
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, l_plan)), 0xff0000ff);
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, r_plan)), 0xffffffff);
	// }
	// if (vtx->ptr->id == 77)
	// {
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, l_plan)), 0xff00ffff);
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, r_plan)), 0xffffffff);
	// }

	if (ft_dist_t_dpos(l_plan, vs->left_plan)
	<= ft_dist_t_dpos(r_plan, vs->left_plan)
	&& abs(ceil(ft_dist_t_dpos(r_plan, vs->player))
	- ceil(ft_dist_t_dpos(vs->left_plan, vs->player)) < 1))
	{
		// printf("true id = %d\n\n", vtx->ptr->id);
		return (1);

	}
	else
	{
		// printf("l_plan(%.1f, %.1f), r_plan(%.1f, %.1f), leftplan(%.1f, %.1f)\n", l_plan.x, l_plan.y, r_plan.x, r_plan.y, vs->left_plan.x, vs->left_plan.y);
		// printf("false id = %d\n\n", vtx->ptr->id);
		return (0);

	}
}

int			check_portal_validity(t_main *s, t_int *vtx, t_visu *vs)
{
	t_4dpos pos;
	t_dpos	l_plan;
	t_dpos	r_plan;
	int		dist;

	// printf("mur gauche = %d, mur droite = %d\n", vtx->next->ptr->id, vtx->ptr->id);
	pos.pos1 = vs->left_point;
	pos.pos2 = vs->player;
	pos.pos3 = vtx->next->ptr->m_pos;
	pos.pos4 = vtx->ptr->m_pos;
	dist = ft_find_intersection(s, pos, 1);
	if (dist > 0)
		pos.pos1 = s->tmp_intersect;
	else
		pos.pos1 = pos.pos3;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	l_plan = s->tmp_intersect;
	// draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, l_plan)), BLUE);

	pos.pos1 = vs->right_point;
	pos.pos3 = vtx->next->ptr->m_pos;
	pos.pos4 = vtx->ptr->m_pos;
	dist = ft_find_intersection(s, pos, 1);
	if (dist > 0)
		pos.pos1 = s->tmp_intersect;
	else
		pos.pos1 = pos.pos4;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	r_plan = s->tmp_intersect;
	// draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, r_plan)), S_RED);

	// printf("dist left = %f, dist right = %f\n", ft_dist_t_dpos(l_plan, vs->left_plan), ft_dist_t_dpos(r_plan, vs->left_plan));

	// if (vtx->ptr->id == 79)
	// {
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, l_plan)), 0xff0000ff);
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, r_plan)), 0xffffffff);
	// }
	// if (vtx->ptr->id == 77)
	// {
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, l_plan)), 0xff00ffff);
	// 	draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, r_plan)), 0xffffffff);
	// }

	if (ft_dist_t_dpos(l_plan, vs->left_plan)
	<= ft_dist_t_dpos(r_plan, vs->left_plan)
	&& abs(ceil(ft_dist_t_dpos(r_plan, vs->player))
	- ceil(ft_dist_t_dpos(vs->left_plan, vs->player)) < 1))
	{
		// printf("true id = %d\n\n", vtx->ptr->id);
		return (1);

	}
	else
	{
		// printf("l_plan(%.1f, %.1f), r_plan(%.1f, %.1f), leftplan(%.1f, %.1f)\n", l_plan.x, l_plan.y, r_plan.x, r_plan.y, vs->left_plan.x, vs->left_plan.y);
		// printf("false id = %d\n\n", vtx->ptr->id);
		return (0);

	}
}

int			check_walls_lenght(t_int *wall1, t_int *wall2)
{
	t_dpos	beg1;
	t_dpos	beg2;
	t_dpos	end1;
	t_dpos	end2;

	end1 = wall1->next->ptr->m_pos;
	end2 = wall2->next->ptr->m_pos;
	beg1 = wall1->ptr->m_pos;
	beg2 = wall2->ptr->m_pos;
	// printf("adresse wall1->next->ptr -> %hd\n", wall1->next->ptr->pos.x);
	// printf("(%.1f)(%.1f)|(%.1f)(%.1f)|(%.1f)(%.1f)|(%.1f)(%.1f)\n", beg1.x, beg1.y, end1.x, end1.y, beg2.x, beg2.y, end2.x, end2.y);
	// printf("dist 1 (%f) et dist 2 (%f)\n", ft_dist_t_dpos(beg1, end1), ft_dist_t_dpos(beg2, end2));
	if (ft_dist_t_dpos(beg1, end1) == ft_dist_t_dpos(beg2, end2))
		return (1);
	else
		return (0);
}
//fonction qui revoie l'angle du point needed, 1 pour left, 2 pour right, 3 pour third
double		ft_find_angle_portal(t_dpos *left, t_dpos *right, t_dpos *third, int needed)
{
	//third est le troisieme point pour trouver l'angle si besoin;
	double	angle = 0;
	double	left_right_dist;
	double	right_third_dist;
	double	left_third_dist;
	t_dpos	tmp_third;

	if (third == NULL)
	{
		third = &tmp_third;
		third->x = left->x + 100;
		third->y = left->y;
	}
	left_third_dist = ft_dist_t_dpos(*third, *left);
	right_third_dist = ft_dist_t_dpos(*third, *right);
	left_right_dist = ft_dist_t_dpos(*left, *right);
	if (needed == 1)
		angle = ft_find_angle_plan(left_third_dist, left_right_dist, right_third_dist);
	else if (needed == 2)
		angle = ft_find_angle_plan(left_right_dist, right_third_dist, left_third_dist);
	else if (needed == 3)
		angle = ft_find_angle_plan(left_third_dist, right_third_dist, left_right_dist);
	return (angle);
}

// t_visu		ft_get_fake_vs(t_main *s, t_dpos fake_player, double fake_angle)
// {
// 	t_visu	fake_vs;
//
// 	fake_vs = ft_place_view_plan(s, fake_player, fake_angle, 0x4bd9ffff);
// }

double		ft_get_fake_angle(t_main *s, t_dpos player, t_int *vtx)
{
	double		angle_fake_player;
	double		angle_portal_in;
	double		angle_portal_out;
	t_dpos		l_portal;
	t_dpos		r_portal;
	t_dpos		lwall;
	t_dpos		rwall;

	(void)s;
	lwall = vtx->ptr->m_pos;
	rwall = vtx->next->ptr->m_pos;
	//trouver le sector dans lequel amene le portail et les coordonees des vtx du portal
	l_portal = vtx->vtx_dest->ptr->m_pos;
	r_portal = vtx->vtx_dest->next->ptr->m_pos;
	//placer et orienter le fake joueur (modif player)
	angle_fake_player = ft_find_angle_portal(&lwall, &rwall, &player, 1);
	//trouver langle du portail d'entree
	angle_portal_in = ft_find_angle_portal(&lwall, &rwall, NULL, 1);
	if (rwall.y > lwall.y)
		angle_portal_in = 180 + (180 - angle_portal_in);
	//trouver langle du portail de sortie
	angle_portal_out = ft_find_angle_portal(&l_portal, &r_portal, NULL, 1);
	if (r_portal.y > l_portal.y)
		angle_portal_out = 180 + (180 - angle_portal_out);
	// printf("angle PLAYER  (%f)\n",angle_fake_player);
	// printf("angle IN      (%f)\n",angle_portal_in);
	// printf("angle OUT     (%f)\n\n",angle_portal_out);
	//application de la difference d'angle des deux portail sur angle player
	angle_fake_player = angle_portal_in - angle_fake_player - fabs(angle_portal_in - angle_portal_out);
	return (angle_fake_player);
	// modifier angle et fake player
}

void		add_portal_to_list(t_main *s, t_dpos player, t_sector *sct, t_visu vs)
{
	int			x;
	t_int		*vtx;
	int			new_x;
	double		angle_left;
	double		angle_right;

	x = 0;
	new_x = 0;
	// printf("add_portal n(%d)\n", s->portal_nb);
	// printf("sct->vertex")
	// printf("vs.begin_wall_id = %d\n", vs.begin_wall_id);
	s->portal_nb++;
	vtx = sct->vertex;

	angle_right = ft_find_angle_portal(&player, &vs.end, NULL, 1);
	if (player.y < vs.end.y)
		angle_right = 180 + (180 - angle_right);
	angle_left = ft_find_angle_portal(&player, &vs.begin, NULL, 1);
	if (player.y < vs.begin.y)
		angle_left = 180 + (180 - angle_left);
	// vs.angle = (angle_right + angle_left) / 2;
	// printf("vs.begin_wall_id = %d\n", vs.begin_wall_id);
	vs.begin_wall_id = ft_find_wall2(s, vs.begin, vs.left_point, WHITE, vs.sct_id); //#37f3ff
	// draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, (vs.begin))), WHITE);
	// printf("vs.begin_wall_id = %d\n", vs.begin_wall_id);
	if (vs.begin_wall_id == 0 || s->count_wall % 2 == 0)
	{
		// vs.begin_wall_id = vs.begin_wall->ptr->id;
		vs.begin_wall_id = vs.vtx_gauche->ptr->id;
		vs.begin = vs.vtx_gauche->ptr->m_pos;
		// printf("true\n");
	}
	// else
	// 	vs.begin = s->tmp_intersect;
	vs.begin_wall = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	vs.end_wall_id = ft_find_wall2(s, vs.end, vs.right_point, S_PINK, vs.sct_id);
	if (vs.end_wall_id == 0 || s->count_wall % 2 == 0)
	{
		// printf("true\n");
		vs.end_wall_id = vs.vtx_droite->prev->ptr->id;

	}
	else
	{
		vs.end = s->tmp_intersect;
	}
	// printf("vs.end_wall_id = %d\n", vs.end_wall_id);
	// exit(-1);
	// if (vs.begin_wall_id == 81)
	// 	printf("vs.begin_wall = %d\n", vs.begin_wall_id);
	// printf("vs.end_wall_id = %d\n", vs.end_wall_id);
	//On recuper l'angle entre le joueur et le point de gauche, ca donne le mur de gauche.
	//On recupere l'angle entre le joueur et le point de droite, ca donne le mur de droite.
	vtx = vs.begin_wall;
	// printf("vtx ptr = %d\n", vtx->ptr->id);
	// draw_first_wall(s, vtx, &vs);
	// if (vs.begin_wall_id == vs.end_wall_id)
	// {
	// 	set_visible_sprites(s, &vs);
	// 	return ;
	// }
	// plan_left = s->tmp_intersect;
	//
	// vtx = vtx->next;
	// vtx = draw_mid_walls(s, vtx, &vs);
	//
	// draw_last_wall(s, vtx, &vs);
	create_all_walls(s, vtx, &vs, 1);
	s->portal_nb--;
	set_visible_sprites(s, &vs);
}

t_dpos		ft_get_fake_player(t_main *s, t_dpos player, t_int *vtx, double *angle_fake, double prev_angle)
{
	t_dpos		l_portal;
	t_dpos		r_portal;
	t_dpos		fake_player;
	double		fake_angle;
	double		player_angle;
	double		angle_portal_in;
	double		angle_portal_out;
	double		dist_player;
	t_dpos		lwall;
	t_dpos		rwall;

	// printf("player (%.1f, %.1f)\n", s->player.r_pos.x *METRE, s->player.r_pos.y *METRE);
	lwall = vtx->ptr->m_pos;
	rwall = vtx->next->ptr->m_pos;
	// printf("lwall.x = %f\nlwall.y = %f\nrwall.x = %f\nrwall.y = %f\n", lwall.x, lwall.y, rwall.x, rwall.y);
	//trouver le sector dans lequel amene le portail et les coordonees des vtx du portal
	l_portal = vtx->vtx_dest->ptr->m_pos;
	// printf("l_portal = %d\n", vtx->vtx_dest->ptr->id);
	// printf("r_portal = %d\n", vtx->vtx_dest->next->ptr->id);
	r_portal = vtx->vtx_dest->next->ptr->m_pos;
	// printf("l_portal.x = %f\nl_portal.y = %f\nr_portal.x = %f\nr_portal.y = %f\n", l_portal.x, l_portal.y, r_portal.x, r_portal.y);
	//trouver la distance entre joueur et le point gauche du portail initial
	dist_player = ft_dist_t_dpos(player, lwall);
	// fake_angle = ft_find_angle_portal(&lwall, &rwall, &player, 1);
	player_angle = ft_find_angle_portal(&lwall, &player, NULL, 1);
	if (lwall.y < player.y)
		player_angle = 180 + (180 - player_angle);
	//trouver langle du portail d'entree
	angle_portal_in = ft_find_angle_portal(&lwall, &rwall, NULL, 1);
	if (rwall.y > lwall.y)
		angle_portal_in = 180 + (180 - angle_portal_in);
	//trouver langle du portail de sortie
	angle_portal_out = ft_find_angle_portal(&r_portal, &l_portal, NULL, 1);
	if (l_portal.y > r_portal.y)
		angle_portal_out = 180 + (180 - angle_portal_out);
	// printf("angle PLAYER  (%.1f)\n", player_angle);
	// printf("angle IN      (%.1f)\n", angle_portal_in);
	// printf("angle OUT     (%.1f)\n\n", angle_portal_out);
	//application de la difference d'angle des deux portail sur angle player
	fake_angle = player_angle - (angle_portal_in - angle_portal_out);
	// printf("angle FINAL (%.1f)=  PLAYER(%.1f) - (IN(%.1f) - OUT(%.1f))\n\n", fake_angle, player_angle, angle_portal_in, angle_portal_out);
	//Tentative de placement du fake player
	fake_player.x = r_portal.x + cos(to_rad(fake_angle)) * dist_player;
	fake_player.y = r_portal.y - sin(to_rad(fake_angle)) * dist_player;
	// printf("\n\n--POSITION DU FAKE PLAYER (%.1f, %.1f)\n", fake_player.x, fake_player.y);
	//ATTENTION !!!! jai ajouter le decal_x pour que le point saffiche a lecran pour mes tests.
	// printf("coord r_portal (%.1f,%.1f)\n\n",r_portal.x, r_portal.y);
	// printf("coord player (%f,%f)\n\n",fake_player.x, fake_player.y);
	*angle_fake = prev_angle - (angle_portal_in - angle_portal_out);
	// *angle_fake = s->player.angle - (angle_portal_in - angle_portal_out);
	// fake_player2.x = fake_player.x + s->editor->decal_x;
	// fake_player2.y = fake_player.y + s->editor->decal_y;
	// printf("fake player.x = %f, fake_player.y = %f\n", fake_player.x, fake_player.y);
	return (fake_player);
}
