#include "doom.h"

int		ft_draw_ceiling(t_main *s, t_walls *wall, t_pos coord)
{
	int begin;
	double pct;

	begin = coord.y;
	pct = ((coord.x - wall->minx_ceiling) * 100) / wall->diffx_ceiling;
	coord.y = ((pct * wall->diffy_ceiling) * 0.001) + wall->miny_ceiling;
	while (coord.y < begin)
	{
		set_pixel(s->sdl->game, 0x485050ff, coord);
		coord.y++;
	}
	return (coord.y - 1);
}

void	ft_draw_floor(t_main *s, t_walls *wall, t_pos coord)
{
	int end;
	double pct;

	pct = ((coord.x - wall->minx_floor) * 100) / (wall->diffx_floor); // attention div par zero possible
	end = ((pct * wall->diffy_floor) * 0.001) + wall->miny_floor;
	while (coord.y < end)
	{
		set_pixel(s->sdl->game, 0xa8b08eff, coord);
		coord.y++;
	}
}

void	ft_draw_column(t_main *s, t_walls *wall, t_pos coord, int end, Uint32 color)
{
	coord.y = ft_draw_ceiling(s, wall, coord);

	while (coord.y++ < end)
		set_pixel(s->sdl->game, color, coord);

	ft_draw_floor(s, wall, coord);

}

int		ft_draw_wall(t_main *s, t_walls *wall, int l_height_wall, int r_height_wall, double width_wall)
{
	int		diff_wall;
	double	i;
	int		height_wall;
	t_pos	coord;
	int		bottom;
	double	pct_avcm; //pourcentage avancement

	i = 0;
	diff_wall = abs(l_height_wall - r_height_wall); //calcule de la diff de hauteur entre les deux murs
	// printf("diff = %d\n",diff_wall);
	height_wall = l_height_wall;
	coord.x = wall->x;
	// printf("Largeur du mur = %f\n", width_wall);
	while (i++ < width_wall)
	{
		coord.y = (HEIGHT / 2) - height_wall / 2 + s->player.y_eye +  s->player.eyesight; //haut du mur
		bottom = (HEIGHT / 2) + height_wall / 2 + s->player.y_eye + s->player.eyesight; //bas du mur
		if (i == 1 || i == width_wall)
			ft_draw_column(s, wall, coord, bottom, 0x000000FF);
		else
			ft_draw_column(s, wall, coord, bottom, 0xb0842fff);
		coord.x++;
		pct_avcm = (100 * i) / width_wall;

		if (l_height_wall < r_height_wall)
			height_wall = l_height_wall + (diff_wall * pct_avcm) / 100;
		else if (l_height_wall > r_height_wall)
			height_wall = l_height_wall - (diff_wall * pct_avcm) / 100;
		else
			height_wall = l_height_wall;
	}
	return (coord.x);
}

t_walls	*ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs)
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


	// printf("vs->left_point.x = %f, vs->left_point.y = %f\n", vs->left_point.x, vs->left_point.y);
	dist = ft_find_intersection(s, vs->left_point, vs->player, left, right, 1);
	if (dist > 0)
		wall->left = s->tmp_intersect;
	else
		wall->left = left;
	ft_find_intersection(s, wall->left, vs->player, vs->left_plan, vs->right_plan, 1);
	wall->l_plan = s->tmp_intersect;
	// printf("pour print: left(%.1f, %.1f), player(%.1f, %.1f)", wall->left.x, wall->left.y, vs->player.x, vs->player.y);
	// printf(" et leftplan(%.1f, %.1f), rightplan(%.1f, %.1f)\n", vs->left_plan.x, vs->left_plan.y, vs->right_plan.x, vs->right_plan.y);
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
	wall->left_ceiling_limit = vs->left_ceiling_limit;
	wall->left_floor_limit = vs->left_floor_limit;
	wall->right_ceiling_limit = vs->right_ceiling_limit;
	wall->right_floor_limit = vs->right_floor_limit;
	return (wall);
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

		ft_limit_ceiling_floor(s, fake_player, wall1, wall2, &fake_vs, 1);

		if (s->portal_nb < PORTAL_LIMIT)
			add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
	}
	else
	{
		vs->begin.x = vtx->ptr->x * METRE;
		vs->begin.y = vtx->ptr->y * METRE;
		vs->tmp_wall.x = vtx->next->ptr->x * METRE;
		vs->tmp_wall.y = vtx->next->ptr->y * METRE;
		ft_create_new_wall(s, vtx, vs);
		// ft_limit_ceiling_floor(s, vs->player, vs->begin, vs->tmp_wall, vs, 1);
	}
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

			ft_limit_ceiling_floor(s, fake_player, wall1, wall2, &fake_vs, 2);

			if (s->portal_nb < PORTAL_LIMIT)
				add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
			// vtx = vtx_ori->next;
		}
		else
		{
			vs->begin.x = vtx->ptr->x * METRE;
			vs->begin.y = vtx->ptr->y * METRE;
			vs->tmp_wall.x = vtx->next->ptr->x * METRE;
			vs->tmp_wall.y = vtx->next->ptr->y * METRE;
			ft_create_new_wall(s, vtx, vs);
			// ft_limit_ceiling_floor(s, vs->player, vs->begin, vs->tmp_wall, vs, 2);
		}
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
	t_walls	*wall;

	if (vtx->wall_value != -1)
	{
		fake_angle = 0;
		fake_player = ft_get_fake_player(s, vs->player, vtx, &fake_angle);
		fake_vs = ft_place_view_plan(s, fake_player, fake_angle, 0x4bd9ffff); // #4bd9ff
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
		demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player, fake_vs.right_plan), METRE, WIDTHPLAN / 2);
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

		ft_limit_ceiling_floor(s, fake_player, wall1, wall2, &fake_vs, 3);

		if (s->portal_nb < PORTAL_LIMIT)
			add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
	}
	else
	{
		vs->begin.x = vtx->ptr->x * METRE;
		vs->begin.y = vtx->ptr->y * METRE;
		vs->tmp_wall.x = vtx->next->ptr->x * METRE;
		vs->tmp_wall.y = vtx->next->ptr->y * METRE;
		ft_find_intersection(s, vs->begin, vs->player, vs->left_plan, vs->right_plan, 1);
		wall = ft_create_new_wall(s, vtx, vs);
		// ft_limit_ceiling_floor(s, vs->player, vs->begin, vs->tmp_wall, vs, 3);
	}
}
void	ft_init_diff_and_min(t_walls *wall)
{
	wall->diffx_ceiling = ft_abs(wall->left_ceiling_limit.x - wall->right_ceiling_limit.x);
	wall->diffy_ceiling = ft_abs(wall->left_ceiling_limit.y - wall->right_ceiling_limit.y);
	wall->minx_ceiling = wall->left_ceiling_limit.x < wall->right_ceiling_limit.x ? wall->left_ceiling_limit.x : wall->right_ceiling_limit.x;
	wall->miny_ceiling = wall->left_ceiling_limit.y < wall->right_ceiling_limit.y ? wall->left_ceiling_limit.y : wall->right_ceiling_limit.y;

	wall->diffx_floor = ft_abs(wall->left_floor_limit.x - wall->right_floor_limit.x);
	wall->diffy_floor = ft_abs(wall->left_floor_limit.y - wall->right_floor_limit.y);
	wall->minx_floor = wall->left_floor_limit.x < wall->right_floor_limit.x ? wall->left_floor_limit.x : wall->right_floor_limit.x;
	wall->miny_floor = wall->left_floor_limit.y < wall->right_floor_limit.y ? wall->left_floor_limit.y : wall->right_floor_limit.y;
}

int		ft_print_wall(t_main *s, t_walls *wall)
{
	double	l_big_dist; //distance joueur -> vertex
	double	r_big_dist;
	double	l_small_dist; //distance joueur -> plan
	double	r_small_dist;
	double	l_pct; //ratio de difference entre big_dist et small_dist
	double	r_pct;
	int		l_height_wall; //hauteur du mur
	int		r_height_wall;
	double	pct_plan; //pourcentage de longueur de mur sur le plan
	double	width_wall; //largeur du mur en pixel a l'ecran

	l_big_dist = ft_dist_t_dpos(wall->player, wall->left);
	r_big_dist = ft_dist_t_dpos(wall->player, wall->right);
	l_small_dist = ft_dist_t_dpos(wall->player, wall->l_plan);
	r_small_dist = ft_dist_t_dpos(wall->player, wall->r_plan);

	l_pct = (l_big_dist * 100.0) / l_small_dist;
	r_pct = (r_big_dist * 100.0) / r_small_dist;

	l_height_wall = HEIGHT / ((l_pct * 0.001) * 4);
	r_height_wall = HEIGHT / ((r_pct * 0.001) * 4);

	pct_plan = (ft_dist_t_dpos(wall->l_plan, wall->r_plan) * 100.0) / WIDTHPLAN;
	width_wall = (WIDTH * pct_plan) / 100;

	ft_init_diff_and_min(wall);

	return (ft_draw_wall(s, wall, l_height_wall, r_height_wall, width_wall));
}

void	ft_limit_ceiling_floor(t_main *s, t_dpos player, t_dpos left, t_dpos right, t_visu *vs, char swich)
{
	//swich permet de savoir quelle fonction a appeller celle ci et donc de savoir si on soccupe du premier ou dernier mur ou autre.
	double	width_wall;
	double	l_big_dist;
	double	r_big_dist;
	double	l_small_dist;
	double	r_small_dist;
	int		l_height_wall;
	int		r_height_wall;
	double	x;
	t_dpos	l_plan;
	t_dpos	r_plan;

	if (swich == 1) //si cest le premier mur
	{
		l_plan = vs->left_plan;
		ft_find_intersection(s, l_plan, vs->player, left, right, 1);
		l_big_dist = (ft_dist_t_dpos(player, s->tmp_intersect) / METRE);
	}
	else
	{
		ft_find_intersection(s, left, vs->player, vs->left_plan, vs->right_plan, 1);
		l_plan = s->tmp_intersect;
		l_big_dist = (ft_dist_t_dpos(player, left) / METRE);
	}
	if (swich == 3) //si cest le dernier mur
	{
		r_plan = vs->right_plan;
		ft_find_intersection(s, r_plan, vs->player, left, right, 1);
		r_big_dist = (ft_dist_t_dpos(player, s->tmp_intersect) / METRE);
	}
	else
	{
		ft_find_intersection(s, right, vs->player, vs->left_plan, vs->right_plan, 1);
		r_plan = s->tmp_intersect;
		r_big_dist = (ft_dist_t_dpos(player, right) / METRE);
	}

	l_small_dist = (ft_dist_t_dpos(player, l_plan) / METRE);
	r_small_dist = (ft_dist_t_dpos(player, r_plan) / METRE);

	l_height_wall = HEIGHT / ((((l_big_dist * 100.0) / l_small_dist) * 0.001) * 4);
	r_height_wall = HEIGHT / ((((r_big_dist * 100.0) / r_small_dist) * 0.001) * 4);
	width_wall = (WIDTH * ((ft_dist_t_dpos(l_plan, r_plan) * 100.0) / WIDTHPLAN)) / 100;

	if (ft_find_intersection(s, vs->left_point, vs->player, left, right, 1) > 0)
		x = 0;
	else
		x = (ft_dist_t_dpos(vs->left_plan, l_plan) / WIDTHPLAN) * WIDTH;

	vs->left_ceiling_limit.x = (int)x;
	vs->left_ceiling_limit.y = (HEIGHT / 2) - l_height_wall / 2 + s->player.y_eye + s->player.eyesight;
	vs->left_floor_limit.x = (int)x;
	vs->left_floor_limit.y = (HEIGHT / 2) + l_height_wall / 2 + s->player.y_eye + s->player.eyesight;
	vs->right_ceiling_limit.x = x + width_wall > WIDTH ? WIDTH : x + width_wall;
	vs->right_ceiling_limit.y = (HEIGHT / 2) - r_height_wall / 2 + s->player.y_eye + s->player.eyesight;
	vs->right_floor_limit.x = vs->right_ceiling_limit.x;
	vs->right_floor_limit.y = (HEIGHT / 2) + r_height_wall / 2 + s->player.y_eye + s->player.eyesight;
	{
	// printf("---- TEST VALEUR ----\n");
	// printf("width_wall = %.1f\n", width_wall);
	// printf("LEFT  -      floor(%d, %d)   ceiling(%d, %d)\n", vs->left_floor_limit.x, vs->left_floor_limit.y, vs->left_ceiling_limit.x, vs->left_ceiling_limit.y);
	// printf("RIGHT -      floor(%d, %d)   ceiling(%d, %d)\n\n", vs->right_floor_limit.x, vs->right_floor_limit.y, vs->right_ceiling_limit.x, vs->right_ceiling_limit.y);
	// if (swich == 3)
	// 	printf("\n\n\n");
	}
}

void	ft_draw_visu(t_main *s, t_dpos player, t_sector *sct, t_visu vs)
{
	t_walls		*wall;
	t_int		*vtx;
	(void)player; //MERDE ?

	vtx = sct->vertex;
	vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	if (!(vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id)))
		return ;
	draw_first_wall(s, vtx, &vs);
	if (vs.begin_wall_id == vs.end_wall_id)// cas 1 seul mur
	{
		wall = s->walls;
		if (wall != NULL)
		{
			while (wall)
			{
				// ft_print_wall(s, wall, vtx);
				ft_print_wall(s, wall);
				wall = wall->next;
			}
		}
		clear_wall_list(s);
		s->portal_nb = 0;
		return ;
	}
	vtx = vtx->next;
	vtx = draw_mid_walls(s, vtx, &vs);
	draw_last_wall(s, vtx, &vs);
	wall = s->walls;
	while (wall)
	{
		// ft_print_wall(s, wall, vtx);
		ft_print_wall(s, wall);
		wall = wall->next;
		vtx = vtx->next;
	}
	// print_wall_list(s);
	clear_wall_list(s);
	s->portal_nb = 0;
	// printf("-------------------------\n");
}
