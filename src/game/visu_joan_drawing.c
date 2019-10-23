#include "doom.h"

int		ft_draw_wall2(t_main *s, int start_wallx, int l_height_wall, int r_height_wall, double width_wall, double longeur, double start_tex)
{
	int		diff_wall;
	double	x;
	int		height_wall;
	int		y;
	t_pos	coord;
	int		start;
	int		end;
	double	tex_x;
	double	tex_y;
	int		px;
	double	pct_avcm; //pourcentage avancement
	t_image *wp;

	// printf("longeur = %f\n",longeur);
	// printf("start_tex = %f\n",start_tex);
	wp = s->menu;
	x = 0;
	diff_wall = abs(l_height_wall - r_height_wall); //calcule de la diff de hauteur entre les deux murs div par deux (pour haut et bas)
	height_wall = l_height_wall;
	coord.x = start_wallx;
	while (coord.x++ < (width_wall + start_wallx))
	{
		start = (HEIGHT / 2) - height_wall / 2 +s->player.y_eye +  s->player.eyesight; //haut du mur
		end = (HEIGHT / 2) + height_wall / 2 + s->player.y_eye + s->player.eyesight; //bas du mur
		coord.y = start;
		y = 0;
		tex_x =  (double)(x++ - (start_tex)) / (double)(width_wall/longeur);
		while (coord.y++ < end)
		{
			tex_y = (double)(y++) / (double)height_wall;
			// set_pixel(s->sdl->game, PINK, coord);
			px = (int)(tex_y * (double)wp->h) * wp->w + (int)(tex_x * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		pct_avcm = (x) / width_wall;
		if (l_height_wall < r_height_wall)
			height_wall = l_height_wall + (diff_wall * pct_avcm);
		else if (l_height_wall > r_height_wall)
			height_wall = l_height_wall - (diff_wall * pct_avcm);
		else
			height_wall = l_height_wall;
	}
	return (coord.x);
}

int		ft_print_wall(t_main *s, t_walls *wall, t_int *vtx)
{
	double	l_dist;
	double	r_dist;
	int		l_height_wall;
	int		r_height_wall;
	double	pct_plan;
	double	width_wall;
	double	longueur_a_afficher;
	double	dist_lwall;
	double	value; // valeur pour debut de texture
	double	l_small_dist;
	double	r_small_dist;
	double	l_pct;
	double	r_pct;

	l_dist = (ft_dist_t_dpos(wall->player, wall->left)/METRE);
	r_dist = (ft_dist_t_dpos(wall->player, wall->right)/METRE);
	longueur_a_afficher = (ft_dist_t_dpos(wall->left, wall->right)/METRE); // longeur a afficher
	dist_lwall = (ft_dist_t_dpos(ft_pos_to_dpos(vtx->ptr->pos), wall->left)/METRE); // distance a retirer aux pixels d'affichage
	l_small_dist = (ft_dist_t_dpos(wall->player, wall->l_plan)/METRE);
	r_small_dist = (ft_dist_t_dpos(wall->player, wall->r_plan)/METRE);

	// l_height_wall = HEIGHT / (l_dist) * 1.5; //calcule des hauteur des murs gauche et droit
	// r_height_wall = HEIGHT / (r_dist) * 1.5; //calcule des hauteur des murs gauche et droit
	l_pct = (l_dist * 100.0) / l_small_dist; //calcule des ratios mur gauche et droit
	r_pct = (r_dist * 100.0) / r_small_dist;
	l_height_wall = HEIGHT / ((l_pct * 0.001)*4); //calcule des hauteur des murs gauche et droit
	r_height_wall = HEIGHT / ((r_pct * 0.001)*4);

	pct_plan = (ft_dist_t_dpos(wall->l_plan, wall->r_plan)) / WIDTHPLAN; //calcule de la largeur du mur dans la fenetre
	width_wall = (WIDTH * pct_plan);

	if (wall->x > 0 && (wall->x + width_wall) < 997) // cas pour un mur afficher en entier
	{
		longueur_a_afficher = (int)wall->longeur_total;
		value = 0;
	}
	else if (width_wall >= 999 && wall->x == 0) // cas pour 1 seul mur a afficher (sur tout l'ecran)
	{
		value = dist_lwall - (int)dist_lwall;
		value = value * (double)(width_wall / longueur_a_afficher);
		value *=  -1;
	}
	else
	{
		longueur_a_afficher -= ((wall->longeur_total - (int)wall->longeur_total) / (int)wall->longeur_total) * (int)longueur_a_afficher;
		if (wall->x > 0 && (wall->x + width_wall) >= 997) // mur droit
			value = 0;
		else // mur gauche
		{
			value = (longueur_a_afficher - (int)longueur_a_afficher);
			value = value * (double)(width_wall / longueur_a_afficher);
		}
	}
	// printf("value = %f\n",value);
	// printf("longeur total = %f\n",longeur_total);
	wall->x = ft_draw_wall2(s, wall->x, l_height_wall, r_height_wall, width_wall,longueur_a_afficher,value);
	// printf("Hauteur du mur Gauche (%d)\n",l_height_wall);
	// printf("Hauteur du mur Droit  (%d)\n\n\n",r_height_wall);
	return (wall->x);
}

void	ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs)
{
	t_walls		*wall;
	int			dist;
	t_dpos		left;
	t_dpos		right;

	if (!(wall = (t_walls*)malloc(sizeof(t_walls))))
		handle_error(s, MALLOC_ERROR);
	wall->next = NULL;
	wall->prev = NULL;
	wall->player = vs->player;
	left.x = vtx->ptr->x * METRE;
	left.y = vtx->ptr->y * METRE;
	right.x = vtx->next->ptr->x * METRE;
	right.y = vtx->next->ptr->y * METRE;
	wall->longeur_total = ft_dist_t_dpos(right, left) / METRE;


	// printf("vs->left_point.x = %f, vs->left_point.y = %f\n", vs->left_point.x, vs->left_point.y);
	dist = ft_find_intersection(s, vs->left_point, vs->player, left, right, 1);
	if (dist > 0)
		wall->left = s->tmp_intersect;
	else
		wall->left = left;
	ft_find_intersection(s, wall->left, vs->player, vs->left_plan, vs->right_plan, 1);
	wall->l_plan = s->tmp_intersect;
	if (dist > 0 && !s->walls)
		wall->x = 0;
	else
		wall->x = (ft_dist_t_dpos(vs->left_plan, wall->l_plan) / WIDTHPLAN) * WIDTH;
	dist = ft_find_intersection(s, vs->right_point, vs->player, left, right, 1);
	if (dist > 0)
	{
		wall->right = s->tmp_intersect;
	}
	else
		wall->right = right;
	ft_find_intersection(s, wall->right, vs->player, vs->left_plan, vs->right_plan, 1);
	wall->r_plan = s->tmp_intersect;
	wall->distance = fabs(vs->player.x - wall->left.x)
		+ fabs(vs->player.y - wall->left.y)
		+ fabs(vs->player.x - wall->right.x)
		+ fabs(vs->player.y - wall->right.y);
	if (ft_dist_t_dpos(wall->l_plan, vs->left_plan) <
	ft_dist_t_dpos(wall->r_plan, vs->left_plan))
	{
		add_wall_to_list(s, wall);
	}
	else
	{
		// printf("Mur[%d] caché\n", vtx->ptr->id);
	}
}

void		draw_first_wall(t_main *s, t_int *vtx, t_visu *vs)
{
	t_visu	fake_vs;
	t_dpos	fake_player;
	double	fake_angle;
	double	angle_right;
	double	angle_left;
	double	demi_fov;
	t_dpos	wall1;
	t_dpos	wall2;
	// printf("vtx->ptr->id = %d, vs->sct_id = %d\n",vtx->ptr->id, vs->sct_id);
	if (vtx->wall_value != -1)
	{
		fake_angle = 0;
		fake_player = ft_get_fake_player(s, vs->player, vtx, &fake_angle);
		// printf("player angle = %f, fake angle = %f\n",s->player.angle, fake_angle);
		fake_vs = ft_place_view_plan(s, fake_player, fake_angle, 0x4bd9ffff); // #4bd9ff
		// printf("player angle = %f, fake angle = %f\n",s->player.angle, fake_angle);
		if (s->portal_nb == 0)
		{
			s->fplayer_pos = fake_player;
			s->fplayer_angle = fake_angle;
			s->fplayer_sct = vtx->sct_dest;
			// printf("fplayer_pos.y = %f\n", s->fplayer_pos.y);
		}
		fake_vs.sct_id = vtx->sct_dest;
		fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
		// printf("sct dest = %d\n", vtx->sct_dest);
		fake_vs.vtx_droite = vtx->vtx_dest;
		if (fake_vs.vtx_droite == NULL)
			handle_error(s, POINTER_ERROR);
		fake_vs.vtx_gauche = vtx->vtx_dest->next;
		demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player,
			fake_vs.left_plan), METRE, WIDTHPLAN / 2);
		// printf("demi_fov = %f\n",demi_fov);
		angle_left = fake_angle + demi_fov;
		angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
		angle_right = fake_angle - demi_fov;
		angle_right = angle_right < 0 ? angle_right + 360: angle_right;
		fake_vs = get_walls_to_draw(s, fake_player, angle_left, angle_right, fake_vs);
		wall1.x = vtx->vtx_dest->next->ptr->x * METRE;
		wall1.y = vtx->vtx_dest->next->ptr->y * METRE;
		wall2.x = vtx->vtx_dest->ptr->x * METRE;
		wall2.y = vtx->vtx_dest->ptr->y * METRE;
		// printf("wall1 (%f;%f), wall2(%f, %f)\n", wall1.x, wall1.y, wall2.x, wall2.y);
		ft_find_intersection(s, wall1, wall2, fake_vs.left_point, fake_player, 1);
		// ft_find_wall2(s, fake_player, fake_vs.left_point, 0x37f3ffff, fake_vs.sct_id);
		if ((ft_find_intersection(s, wall1, wall2, fake_vs.left_point,
			fake_player, 1)) == 0)
		{
			fake_vs.begin.x = fake_vs.vtx_gauche->ptr->x * METRE;
			fake_vs.begin.y = fake_vs.vtx_gauche->ptr->y * METRE;
		}
		else
			fake_vs.begin = s->tmp_intersect;
		if ((ft_find_intersection(s, wall1, wall2, fake_vs.right_point,
			fake_player, 1)) == 0)
		{
			fake_vs.end.x = fake_vs.vtx_droite->ptr->x * METRE;
			fake_vs.end.y = fake_vs.vtx_droite->ptr->y * METRE;
		}
		else
			fake_vs.end = s->tmp_intersect;

		if (s->portal_nb < PORTAL_LIMIT)
			add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
	}
	else
		ft_create_new_wall(s, vtx, vs);
}

t_int		*draw_mid_walls(t_main *s, t_int *vtx, t_visu *vs)
{
	t_visu	fake_vs;
	t_dpos	fake_player;
	double	fake_angle;
	double	angle_right;
	double	angle_left;
	double	demi_fov;
	int		i;
	t_dpos	wall1;
	t_dpos	wall2;

	i = 0;
	if (vs->end_wall_id == 0)
	{
		printf("ERROR\n");
		exit(-1);
	}
	while (vtx->ptr->id != vs->end_wall_id)
	{
		// printf("ptr->id = %d, vs->end_wall_id = %d\n", vtx->ptr->id, vs->end_wall_id);
		if (vtx->wall_value != -1)
		{
			fake_angle = 0;
			fake_player = ft_get_fake_player(s, vs->player, vtx, &fake_angle);
			fake_vs = ft_place_view_plan(s, fake_player, fake_angle, 0x4bd9ffff);
			// printf("player angle = %f, fake angle = %f\n",s->player.angle, fake_angle);
			if (s->portal_nb == 0)
			{
				s->fplayer_pos = fake_player;
				s->fplayer_angle = fake_angle;
				s->fplayer_sct = vtx->sct_dest;
			}
			fake_vs.sct_id = vtx->sct_dest;
			fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
			fake_vs.vtx_droite = vtx->vtx_dest;
			if (fake_vs.vtx_droite == NULL)
				handle_error(s, POINTER_ERROR);
			fake_vs.vtx_gauche = vtx->vtx_dest->next;
			demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player,
				fake_vs.left_plan), METRE, WIDTHPLAN / 2);
			angle_left = fake_angle + demi_fov;
			angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
			angle_right = fake_angle - demi_fov;
			angle_right = angle_right < 0 ? angle_right + 360 : angle_right;
			fake_vs = get_walls_to_draw(s, fake_player, angle_left,
				angle_right, fake_vs);
			wall1.x = fake_vs.vtx_gauche->ptr->x * METRE;
			wall1.y = fake_vs.vtx_gauche->ptr->y * METRE;
			wall2.x = fake_vs.vtx_droite->ptr->x * METRE;
			wall2.y = fake_vs.vtx_droite->ptr->y * METRE;
			if ((ft_find_intersection(s, wall1, wall2, fake_vs.left_point,
				fake_player, 1)) == 0)
			{
				fake_vs.begin.x = fake_vs.vtx_gauche->ptr->x * METRE;
				fake_vs.begin.y = fake_vs.vtx_gauche->ptr->y * METRE;
			}
			else
				fake_vs.begin = s->tmp_intersect;
			if ((ft_find_intersection(s, wall1, wall2, fake_vs.right_point,
				fake_player, 1)) == 0)
			{
				fake_vs.end.x = fake_vs.vtx_droite->ptr->x * METRE;
				fake_vs.end.y = fake_vs.vtx_droite->ptr->y * METRE;
			}
			else
				fake_vs.end = s->tmp_intersect;
			// printf("begin wall ID PORTAAAAL = %d\n",fake_vs.begin_wall->ptr->id );
			if (s->portal_nb < PORTAL_LIMIT)
				add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
			// vtx = vtx_ori->next;
		}
		else
			ft_create_new_wall(s, vtx, vs);
		vtx = vtx->next;
	}
	return (vtx);
}

void		draw_last_wall(t_main *s, t_int *vtx, t_visu *vs)
{
	t_visu	fake_vs;
	t_dpos	fake_player;
	double	fake_angle;
	double	angle_right;
	double	angle_left;
	double	demi_fov;
	t_dpos	wall1;
	t_dpos	wall2;

	if (vtx->wall_value != -1)
	{
		fake_angle = 0;
		fake_player = ft_get_fake_player(s, vs->player, vtx, &fake_angle);
		// printf("player angle = %f, fake angle = %f\n",s->player.angle, fake_angle);
		fake_vs = ft_place_view_plan(s, fake_player, fake_angle, 0x4bd9ffff); // #4bd9ff
		// printf("player angle = %f, fake angle = %f\n",s->player.angle, fake_angle);
		if (s->portal_nb == 0)
		{
			s->fplayer_pos = fake_player;
			s->fplayer_angle = fake_angle;
			s->fplayer_sct = vtx->sct_dest;
			// printf("fplayer_pos.y = %f\n", s->fplayer_pos.y);
		}
		fake_vs.sct_id = vtx->sct_dest;
		fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
		fake_vs.vtx_droite = vtx->vtx_dest;
		if (fake_vs.vtx_droite == NULL)
			handle_error(s, POINTER_ERROR);
		fake_vs.vtx_gauche = vtx->vtx_dest->next;
		demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player, fake_vs.right_plan), METRE, WIDTHPLAN / 2);
		// printf("demi_fov = %f\n",demi_fov);
		angle_left = fake_angle + demi_fov;
		angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
		angle_right = fake_angle - demi_fov;
		angle_right = angle_right < 0 ? angle_right + 360: angle_right;
		fake_vs = get_walls_to_draw(s, fake_player, angle_left, angle_right, fake_vs);
		fake_vs.begin_wall_id = fake_vs.vtx_gauche->ptr->id;
		wall1.x = vtx->vtx_dest->next->ptr->x * METRE;
		wall1.y = vtx->vtx_dest->next->ptr->y * METRE;
		wall2.x = vtx->vtx_dest->ptr->x * METRE;
		wall2.y = vtx->vtx_dest->ptr->y * METRE;

		if ((ft_find_intersection(s, wall1, wall2, fake_vs.left_point, fake_player, 1)) == 0)
		{
			fake_vs.begin.x = fake_vs.vtx_gauche->ptr->x * METRE;
			fake_vs.begin.y = fake_vs.vtx_gauche->ptr->y * METRE;
		}
		else
		{
			fake_vs.begin = s->tmp_intersect;
		}

		if ((ft_find_intersection(s, wall1, wall2, fake_vs.right_point, fake_player, 1)) == 0)
		{
			fake_vs.end.x = fake_vs.vtx_droite->ptr->x * METRE;
			fake_vs.end.y = fake_vs.vtx_droite->ptr->y * METRE;
		}
		else
		{
			fake_vs.end = s->tmp_intersect;
		}

		ft_limit_ceiling_floor(s, fake_player, wall1, wall2, &fake_vs);

		if (s->portal_nb < PORTAL_LIMIT)
			add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
	}
	else
	{
		vs->begin.x = vtx->ptr->x * METRE;
		vs->begin.y = vtx->ptr->y * METRE;
		vs->tmp_wall.x = vtx->next->ptr->x * METRE;
		vs->tmp_wall.y = vtx->next->ptr->y * METRE;
		ft_limit_ceiling_floor(s, vs->player, vs->begin, vs->tmp_wall, vs);
		ft_find_intersection(s, vs->begin, vs->player, vs->left_plan, vs->right_plan, 1);
		ft_create_new_wall(s, vtx, vs);
	}
}

void	ft_limit_ceiling_floor(t_main *s, t_dpos player, t_dpos left, t_dpos right, t_visu *vs)
{
	double width_wall;
	double l_dist;
	double r_dist;
	double l_small_dist;
	double r_small_dist;
	double l_height_wall;
	double r_height_wall;
	double x;
	t_dpos l_plan;
	t_dpos r_plan;

	l_dist = (ft_dist_t_dpos(player, left) / METRE);
	r_dist = (ft_dist_t_dpos(player, right) / METRE);
	l_small_dist = (ft_dist_t_dpos(player, vs->left_plan) / METRE);
	r_small_dist = (ft_dist_t_dpos(player, vs->right_plan) / METRE);
	l_height_wall = HEIGHT / ((((l_dist * 100.0) / l_small_dist) * 0.001) * 4);
	r_height_wall = HEIGHT / ((((r_dist * 100.0) / r_small_dist) * 0.001) * 4);

	ft_find_intersection(s, left, vs->player, vs->left_plan, vs->right_plan, 1);
	l_plan = s->tmp_intersect;
	// draw_anchor(s, ft_dpos_to_pos(s->tmp_intersect), 0x00eeffff);//bleu
	r_plan = vs->right_plan;
	ft_find_intersection(s, vs->right_plan, vs->player, left, right, 1);
	// printf("left(%.1f, %.1f)    right(%.1f, %.1f)\n", left.x, left.y, right.x, right.y);
	r_dist = (ft_dist_t_dpos(player, s->tmp_intersect) / METRE);
	r_height_wall = HEIGHT / ((((r_dist * 100.0) / r_small_dist) * 0.001) * 4);
	// draw_anchor(s, ft_dpos_to_pos(s->tmp_intersect), 0x1cff69ff);//vert
	width_wall = ((ft_dist_t_dpos(l_plan, r_plan) / WIDTHPLAN) * WIDTH);

	if (ft_find_intersection(s, vs->left_point, vs->player, left, right, 1) > 0)
		x = 0; // pas neccesaire dans cette fonction...
	else
		x = (ft_dist_t_dpos(vs->left_plan, l_plan) / WIDTHPLAN) * WIDTH;

	vs->left_ceiling_limit.x = (int)x;
	vs->left_ceiling_limit.y = (HEIGHT / 2) - l_height_wall / 2 + s->player.y_eye + s->player.eyesight;
	vs->left_floor_limit.x = (int)x;
	vs->left_floor_limit.y = (HEIGHT / 2) + l_height_wall / 2 + s->player.y_eye + s->player.eyesight;

	vs->right_ceiling_limit.x = x + width_wall;
	vs->right_ceiling_limit.y = (HEIGHT / 2) - r_height_wall / 2 + s->player.y_eye + s->player.eyesight;
	vs->right_floor_limit.x = vs->right_ceiling_limit.x;
	vs->right_floor_limit.y = (HEIGHT / 2) + r_height_wall / 2 + s->player.y_eye + s->player.eyesight;
	// printf("---- TEST VALEUR ----\n\n");
	// printf("width_wall = %.1f\n", width_wall);
	// printf("LEFT  -      floor(%d, %d)   ceiling(%d, %d)\n", vs->left_floor_limit.x, vs->left_floor_limit.y, vs->left_ceiling_limit.x, vs->left_ceiling_limit.y);
	// printf("RIGHT -      floor(%d, %d)   ceiling(%d, %d)\n\n\n\n", vs->right_floor_limit.x, vs->right_floor_limit.y, vs->right_ceiling_limit.x, vs->right_ceiling_limit.y);
}

void	ft_draw_visu(t_main *s, t_dpos player, t_sector *sct, t_visu vs)
{
	t_walls		*tmp;
	t_int		*vtx;
	(void)player; //MERDE ?

	(void)player;
	vtx = sct->vertex;
	vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	if (!(vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id)))
		return ;
		// handle_error(s, POINTER_ERROR);
	draw_first_wall(s, vtx, &vs);
	if (vs.begin_wall_id == vs.end_wall_id)// cas 1 seul mur
	{
		tmp = s->walls;
		if (tmp != NULL)
		{
			while (tmp)
			{
				ft_print_wall(s, tmp, vtx);
				// ft_print_wall(s,tmp tmp->x, tmp->player, tmp->left, tmp->right, tmp->l_plan, tmp->r_plan,vtx,tmp->longeur);
				tmp = tmp->next;
			}
		}
		clear_wall_list(s);
		s->portal_nb = 0;
		return ;
	}
	vtx = vtx->next;
	vtx = draw_mid_walls(s, vtx, &vs);
	draw_last_wall(s, vtx, &vs);
	tmp = s->walls;
	while (tmp)
	{
		ft_print_wall(s, tmp, vtx);
		tmp = tmp->next;
		vtx = vtx->next;
	}
	// print_wall_list(s);
	clear_wall_list(s);
	s->portal_nb = 0;
	// printf("-------------------------\n");
}
