#include "doom.h"

void	get_wall_distance(t_walls *wall, t_visu *vs)
{
	int	dist1;
	int dist2;

	dist1 = ft_dist_t_dpos(wall->left, vs->player);
	dist2 = ft_dist_t_dpos(wall->right, vs->player);
	if (dist1 <= dist2)
	{
		wall->l_dist = dist1;
		wall->b_dist = dist2;
	}
	else
	{
		wall->l_dist = dist2;
		wall->b_dist = dist1;
	}
}

void	ft_draw_column(t_main *s, t_walls *wall, t_pos coord, int end, Uint32 color)
{
	coord.y = ft_draw_ceiling(s, wall, coord);

	if (wall->wall_or_portal == 'w')
	{
		if (wall->image)
			draw_texture(s, wall, coord, end);
		else
		{
			if (coord.y < 0)
				coord.y = -1;
			while (coord.y++ < end)
				set_pixel(s->sdl->game, color, coord);
		}
	}
	coord.y = end - 1;
	ft_draw_floor(s, wall, coord);
}

int		ft_get_diff_height_pxl(int pct_eyesight, int height_wall)
{
	int		half_wall; //hauteur du mur en pxl divisé par 2;

	half_wall = height_wall / 2;
	return (((half_wall * pct_eyesight) / 50) - half_wall); //50 car moitié mur
}

int		ft_draw_wall(t_main *s, t_walls *wall, double l_height_wall, double r_height_wall, int width_wall)
{
	double	diff_wall;
	int		i;
	double	height_wall;
	t_pos	coord;
	int		bottom;
	double	pct_avcm; //pourcentage avancement
	double	diff_height_pxl;
	double	pct_eyesight; //pourcentage vision player

	i = 0;
	diff_wall = fabs(l_height_wall - r_height_wall);
	height_wall = l_height_wall;
	coord.x = wall->x;
	wall->screen_width_wall = width_wall;
	get_total_w_wall(wall);
	pct_eyesight = 100 - (s->player.size * 100 / (wall->ceiling_height - wall->floor_height));
	// printf("---\nwall size = %d       player size %d\n", wall->ceiling_height - wall->floor_height, s->player.size);
	while (i++ < width_wall)
	{
		wall->avcm_x = i;
		diff_height_pxl = ft_get_diff_height_pxl(pct_eyesight, l_height_wall);
		// printf("height = %.2f      diff = %.2f\n", height_wall, diff_height_pxl);
		coord.y = (HEIGHT / 2) - (height_wall / 2 + diff_height_pxl) + s->player.y_eye;
		bottom = (HEIGHT / 2) + (height_wall / 2 - diff_height_pxl) + s->player.y_eye;
		if (i == 1 || i == width_wall)
			ft_draw_column(s, wall, coord, bottom, 0x000000FF);
		else
			ft_draw_column(s, wall, coord, bottom, 0xb0842fff);
		coord.x++;
		pct_avcm = (100 * (double)i) / (double)width_wall;

		if (l_height_wall < r_height_wall)
			height_wall = l_height_wall + (diff_wall * pct_avcm) / 100;
		else if (l_height_wall > r_height_wall)
			height_wall = l_height_wall - (diff_wall * pct_avcm) / 100;
		else
			height_wall = l_height_wall;
	}
	// printf("-----------------------------------------------\n\n\n\n");
	return (coord.x);
}

t_walls	*ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs, char w_or_p)
{
	t_walls		*wall;
	int			dist;
	t_dpos		left;
	t_dpos		right;

	if (!(wall = (t_walls*)malloc(sizeof(t_walls))))
		handle_error(s, MALLOC_ERROR);
	wall->wall_or_portal = w_or_p;
	wall->next = NULL;
	wall->prev = NULL;
	wall->image = NULL;
	if (vtx->image)
		wall->image = vtx->image;
	wall->player = vs->player;
	left.x = vtx->ptr->x * METRE;
	left.y = vtx->ptr->y * METRE;
	right.x = vtx->next->ptr->x * METRE;
	right.y = vtx->next->ptr->y * METRE;
	wall->r_right = right;
	wall->r_left = left;

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
		wall->right = s->tmp_intersect;
	else
		wall->right = right;

	ft_find_intersection(s, wall->right, vs->player, vs->left_plan, vs->right_plan, 1);
	wall->r_plan = s->tmp_intersect;
	get_wall_distance(wall, vs);
	if (vtx->ptr->id == 19) //19 mur du fond
	{
		draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, wall->l_plan)), YELLOW);
		draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, wall->r_plan)), GREEN);
	}
		if (ft_dist_t_dpos(wall->l_plan, vs->left_plan) <=
		ft_dist_t_dpos(wall->r_plan, vs->left_plan)
		&& abs(ceil(ft_dist_t_dpos(wall->r_plan, vs->player)) - ceil(ft_dist_t_dpos(vs->left_plan, vs->player)) < 1))
		{
				add_wall_to_list(s, wall);
		}

	wall->left_ceiling_limit = vs->left_ceiling_limit;
	wall->left_floor_limit = vs->left_floor_limit;
	wall->right_ceiling_limit = vs->right_ceiling_limit;
	wall->right_floor_limit = vs->right_floor_limit;
	wall->floor_height = vs->sct->floor;
	wall->ceiling_height = vs->sct->ceiling;
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
		fake_vs.prev_sct_id = vtx->sct;
		fake_vs.sct_id = vtx->sct_dest;
		fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
		demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player,
			fake_vs.left_plan), METRE, WIDTHPLAN / 2);
		angle_left = fake_angle + demi_fov;
		angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
		angle_right = fake_angle - demi_fov;
		angle_right = angle_right < 0 ? angle_right + 360: angle_right;
		fake_vs = get_walls_to_draw(s, fake_player, angle_left, angle_right, fake_vs);
		fake_vs.vtx_droite = vtx->vtx_dest;
		if (fake_vs.vtx_droite == NULL)
			handle_error(s, POINTER_ERROR);
		fake_vs.vtx_gauche = vtx->vtx_dest->next;
		wall1.x = vtx->vtx_dest->next->ptr->x * METRE;
		wall1.y = vtx->vtx_dest->next->ptr->y * METRE;
		wall2.x = vtx->vtx_dest->ptr->x * METRE;
		wall2.y = vtx->vtx_dest->ptr->y * METRE;
		ft_find_intersection(s, wall1, wall2, fake_vs.left_point, fake_player, 1);
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

		fake_vs.player = fake_player;
		ft_create_new_wall(s, vtx, vs, 'p');

		if (s->portal_nb < PORTAL_LIMIT)
		{
			add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
		}
	}
	else
	{
		// vs.vtx_droite = vtx->vtx_dest;
		vs->begin.x = vtx->ptr->x * METRE;
		vs->begin.y = vtx->ptr->y * METRE;
		vs->tmp_wall.x = vtx->next->ptr->x * METRE;
		vs->tmp_wall.y = vtx->next->ptr->y * METRE;
		ft_create_new_wall(s, vtx, vs, 'w');
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
	t_dpos	wall1;
	t_dpos	wall2;

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
			fake_vs.prev_sct_id = vtx->sct;
			fake_vs.sct_id = vtx->sct_dest;
			fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
			demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player,
				fake_vs.left_plan), METRE, WIDTHPLAN / 2);
			angle_left = fake_angle + demi_fov;
			angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
			angle_right = fake_angle - demi_fov;
			angle_right = angle_right < 0 ? angle_right + 360 : angle_right;
			fake_vs = get_walls_to_draw(s, fake_player, angle_left,
				angle_right, fake_vs);
			fake_vs.vtx_droite = vtx->vtx_dest;
			if (fake_vs.vtx_droite == NULL)
				handle_error(s, POINTER_ERROR);
			fake_vs.vtx_gauche = vtx->vtx_dest->next;
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

			ft_limit_ceiling_floor(s, fake_player, wall1, wall2, &fake_vs, 2);

			fake_vs.player = fake_player;
			ft_create_new_wall(s, vtx, vs, 'p');

			if (s->portal_nb < PORTAL_LIMIT)
				add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
		}
		else
		{
			vs->begin.x = vtx->ptr->x * METRE;
			vs->begin.y = vtx->ptr->y * METRE;
			vs->tmp_wall.x = vtx->next->ptr->x * METRE;
			vs->tmp_wall.y = vtx->next->ptr->y * METRE;
			ft_create_new_wall(s, vtx, vs, 'w');
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
		fake_vs.prev_sct_id = vtx->sct;
		fake_vs.sct_id = vtx->sct_dest;
		fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
		demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player, fake_vs.right_plan), METRE, WIDTHPLAN / 2);
		angle_left = fake_angle + demi_fov;
		angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
		angle_right = fake_angle - demi_fov;
		angle_right = angle_right < 0 ? angle_right + 360: angle_right;
		fake_vs = get_walls_to_draw(s, fake_player, angle_left, angle_right, fake_vs);
		fake_vs.vtx_droite = vtx->vtx_dest;
		if (fake_vs.vtx_droite == NULL)
			handle_error(s, POINTER_ERROR);
		fake_vs.vtx_gauche = vtx->vtx_dest->next;
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

		fake_vs.player = fake_player;
		ft_create_new_wall(s, vtx, vs, 'p');

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
		ft_create_new_wall(s, vtx, vs, 'w');
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
	// printf("min_ceiling(x %d, y %d) min_floor(x %d, y %d) diff_ceiling(x %d, y %d) diff_floor(x %d, y %d)\n", wall->minx_ceiling, wall->miny_ceiling, wall->minx_floor, wall->miny_floor, wall->diffx_ceiling, wall->diffy_ceiling, wall->diffx_floor, wall->diffy_floor);
}

int		ft_print_wall(t_main *s, t_walls *wall)
{
	double	l_big_dist; //distance joueur -> vertex
	double	r_big_dist;
	double	l_small_dist; //distance joueur -> plan
	double	r_small_dist;
	double	l_pct; //ratio de difference entre big_dist et small_dist
	double	r_pct;
	double	l_height_wall; //hauteur du mur
	double	r_height_wall;
	double	pct_plan; //pourcentage de longueur de mur sur le plan
	int		width_wall; //largeur du mur en pixel a l'ecran

	l_big_dist = ft_dist_t_dpos(wall->player, wall->left);
	r_big_dist = ft_dist_t_dpos(wall->player, wall->right);
	l_small_dist = ft_dist_t_dpos(wall->player, wall->l_plan);
	r_small_dist = ft_dist_t_dpos(wall->player, wall->r_plan);

	l_pct = (l_big_dist * 100.0) / l_small_dist;
	r_pct = (r_big_dist * 100.0) / r_small_dist;

	l_height_wall = HEIGHT / ((l_pct * 0.001) * 4) * (double)abs(wall->floor_height - wall->ceiling_height) * HEIGHT_MULT;
	r_height_wall = HEIGHT / ((r_pct * 0.001) * 4) * (double)abs(wall->floor_height - wall->ceiling_height) * HEIGHT_MULT;

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
	double	l_height_wall;
	double	r_height_wall;
	double	l_height_wall_diff;
	double	r_height_wall_diff;
	double	x;
	t_dpos	l_plan;
	t_dpos	r_plan;
	double	pct_eyesight;

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

	l_height_wall = HEIGHT / ((((l_big_dist * 100.0) / l_small_dist) * 0.001) * 4)
	* ft_abs(vs->sct->floor - vs->sct->ceiling) * HEIGHT_MULT;
	r_height_wall = HEIGHT / ((((r_big_dist * 100.0) / r_small_dist) * 0.001) * 4)
	* ft_abs(vs->sct->floor - vs->sct->ceiling) * HEIGHT_MULT;
	width_wall = (WIDTH * ((ft_dist_t_dpos(l_plan, r_plan) * 100.0) / WIDTHPLAN)) / 100;

	if (ft_find_intersection(s, vs->left_point, vs->player, left, right, 1) > 0)
		x = 0;
	else
		x = (ft_dist_t_dpos(vs->left_plan, l_plan) / WIDTHPLAN) * WIDTH;

	pct_eyesight = 100 - (s->player.size * 100 / (vs->sct->ceiling - vs->sct->floor));
	l_height_wall_diff = ft_get_diff_height_pxl(pct_eyesight, l_height_wall);
	r_height_wall_diff = ft_get_diff_height_pxl(pct_eyesight, r_height_wall);
	// printf("height_wall (%.2f, %.2f)\nles deux diff (%.2f, %.2f)\n", l_height_wall, r_height_wall, l_height_wall_diff, r_height_wall_diff);
	vs->left_ceiling_limit.x = (int)x;
	vs->left_ceiling_limit.y = (HEIGHT / 2) - (l_height_wall / 2 + l_height_wall_diff) + s->player.y_eye + s->player.eyesight;
	vs->left_floor_limit.x = (int)x;
	vs->left_floor_limit.y = (HEIGHT / 2) + (l_height_wall / 2 - l_height_wall_diff) + s->player.y_eye + s->player.eyesight;

	vs->right_ceiling_limit.x = x + width_wall > WIDTH ? WIDTH : x + width_wall;
	vs->right_ceiling_limit.y = (HEIGHT / 2) - (r_height_wall / 2 + r_height_wall_diff) + s->player.y_eye + s->player.eyesight;
	vs->right_floor_limit.x = vs->right_ceiling_limit.x;
	vs->right_floor_limit.y = (HEIGHT / 2) + (r_height_wall / 2 - r_height_wall_diff) + s->player.y_eye + s->player.eyesight;

}

void	ft_draw_visu(t_main *s, t_sector *sct, t_visu vs)
{
	t_walls		*wall;
	t_int		*vtx;

	// s->player.eyesight = EYESIGHT + (ft_abs(sct->floor - sct->ceiling) - 2) * -50;
	vtx = sct->vertex;
	vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	if (!(vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id)))
		return ;
	draw_first_wall(s, vtx, &vs);
	if (vs.begin_wall_id == vs.end_wall_id)// cas 1 seul mur
	{
		// print_wall_list(s);
		wall = s->walls;
		if (wall != NULL)
		{
			while (wall)
			{
				ft_print_wall(s, wall);
				wall = wall->next;
			}
		}
		clear_wall_list(s);
		s->portal_nb = 0;
		set_visible_sprites(s, &vs);
		return ;
	}
	vtx = vtx->next;
	vtx = draw_mid_walls(s, vtx, &vs);
	draw_last_wall(s, vtx, &vs);
	wall = s->walls;
	// print_wall_list(s);
	while (wall)
	{
		// if (wall->w_or_p == 'c')
		ft_print_wall(s, wall);
		wall = wall->next;
		vtx = vtx->next;
	}
	clear_wall_list(s);
	s->portal_nb = 0;
	set_visible_sprites(s, &vs);
}
