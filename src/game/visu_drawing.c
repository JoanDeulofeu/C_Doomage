#include "doom.h"

t_walls	*ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs, char w_or_p)
{
	t_walls		*wall;
	int			dist;
	t_dpos		left;
	t_dpos		right;
	t_sector	*sct;

	if (!(wall = (t_walls*)malloc(sizeof(t_walls))))
		handle_error(s, MALLOC_ERROR);
	sct = NULL;
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
	wall->angle = vs->angle;
	wall->sct_id = vs->sct_id;
	// printf("vs angle = %f\n", vs->angle);

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
	if (ft_dist_t_dpos(wall->l_plan, vs->left_plan)
	<= ft_dist_t_dpos(wall->r_plan, vs->left_plan)
	&& abs(ceil(ft_dist_t_dpos(wall->r_plan, vs->player))
	- ceil(ft_dist_t_dpos(vs->left_plan, vs->player)) < 1))
	{
		add_wall_to_list(s, wall);
	}

	wall->left_ceiling_limit = vs->left_ceiling_limit;
	wall->left_floor_limit = vs->left_floor_limit;
	wall->right_ceiling_limit = vs->right_ceiling_limit;
	wall->right_floor_limit = vs->right_floor_limit;
	wall->floor_height = vs->sct->floor;
	wall->ceiling_height = vs->sct->ceiling;
	if (w_or_p == 'p')
	{
		sct = get_sector_by_id(s, vtx->sct_dest);
		wall->floor_height_dest = sct->floor;
		wall->ceiling_height_dest = sct->ceiling;
	}
	else
	{
		wall->floor_height_dest = 0;
		wall->ceiling_height_dest = 0;
	}
	return (wall);
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

	s->player.eyesight = s->player.foot_height - vs->sct->floor + s->player.size;
	l_height_wall_diff = ft_get_diff_height_pxl(s, vs->sct->ceiling, vs->sct->floor, l_height_wall);
	r_height_wall_diff = ft_get_diff_height_pxl(s, vs->sct->ceiling, vs->sct->floor, r_height_wall);
	// printf("height_wall (%.2f, %.2f)\nles deux diff (%.2f, %.2f)\n", l_height_wall, r_height_wall, l_height_wall_diff, r_height_wall_diff);
	vs->left_ceiling_limit.x = (int)x;
	vs->left_ceiling_limit.y = (HEIGHT / 2) - (l_height_wall) + s->player.y_eye + l_height_wall_diff;
	vs->left_floor_limit.x = (int)x;
	vs->left_floor_limit.y = (HEIGHT / 2) + s->player.y_eye + l_height_wall_diff;

	vs->right_ceiling_limit.x = x + width_wall > WIDTH ? WIDTH : x + width_wall;
	vs->right_ceiling_limit.y = (HEIGHT / 2) - (r_height_wall) + s->player.y_eye + r_height_wall_diff;
	vs->right_floor_limit.x = vs->right_ceiling_limit.x;
	vs->right_floor_limit.y = (HEIGHT / 2) + s->player.y_eye + r_height_wall_diff;
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
		set_visible_sprites(s, &vs);
		s->portal_nb = 0;
		return ;
	}
	vtx = vtx->next;
	vtx = draw_mid_walls(s, vtx, &vs);
	draw_last_wall(s, vtx, &vs);
	wall = s->walls;
	while (wall)
	{
		ft_print_wall(s, wall);
		wall = wall->next;
		vtx = vtx->next;
	}
	set_visible_sprites(s, &vs);
	s->portal_nb = 0;
}
