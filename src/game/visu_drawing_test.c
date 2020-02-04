#include "doom.h"

void	ft_create_new_wall2(t_walls *wall, t_int *vtx, t_visu *vs, int part)
{
	if (part == 1)
	{
		if (vtx->image)
			wall->image = vtx->image;
		wall->nb_tex = vtx->tex_nb;
		wall->player = vs->player;
		wall->angle = vs->angle;
		wall->sct_id = vs->sct_id;
	}
	else
	{
		wall->left_ceiling_limit = vs->left_ceiling_limit;
		wall->left_floor_limit = vs->left_floor_limit;
		wall->right_ceiling_limit = vs->right_ceiling_limit;
		wall->right_floor_limit = vs->right_floor_limit;
		wall->floor_height = vs->sct->floor;
		wall->ceiling_height = vs->sct->ceiling;
	}
}

t_walls	*ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs, char w_or_p)
{
	t_walls		*wall;
	int			dist;
	t_4dpos		pos;
	t_dpos		left;
	t_dpos		right;
	t_sector	*sct;

	if (!(wall = (t_walls*)malloc(sizeof(t_walls))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void *)wall, sizeof(t_walls));
	sct = NULL;
	wall->id = ++s->wall_fk_id;
	ft_create_new_wall2(wall, vtx, vs, 1);
	wall->wall_or_portal = w_or_p;
	left = vtx->ptr->m_pos;
	right = vtx->next->ptr->m_pos;
	wall->r_right = right;
	wall->r_left = left;

	// if (vs->prev_sector == 0)
	// 	pos.pos2 = vs->player;
	// else
	// 	pos.pos2 =
	 draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, (vs->begin))), BLUE);
	  draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, (vs->end))), S_RED);
	pos.pos1 = vs->left_point;
	pos.pos2 = vs->player;
	pos.pos3 = left;
	pos.pos4 = right;
	dist = ft_find_intersection(s, pos, 1);
	// ft_find_wall2(s, vs->player, vs->left_point, APPLE_GREEN, vs->sct_id);
	if (dist > 0)
		wall->left = s->tmp_intersect;
	else
		wall->left = left;
	pos.pos1 = wall->left;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	wall->l_plan = s->tmp_intersect;
	if (dist > 0 && !s->walls)
		wall->x = 0;
	else
		wall->x = (ft_dist_t_dpos(pos.pos3, wall->l_plan) / WIDTHPLAN) * WIDTH;
	pos.pos1 = vs->right_point;
	pos.pos3 = left;
	pos.pos4 = right;
	dist = ft_find_intersection(s, pos, 1);
	if (dist > 0)
		wall->right = s->tmp_intersect;
	else
		wall->right = right;
	wall->portal_value = 0;
	pos.pos1 = wall->right;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	ft_find_intersection(s, pos, 1);
	wall->r_plan = s->tmp_intersect;
	get_wall_distance(wall, vs);
	if (ft_dist_t_dpos(wall->l_plan, vs->left_plan)
	<= ft_dist_t_dpos(wall->r_plan, vs->left_plan)
	&& abs(ceil(ft_dist_t_dpos(wall->r_plan, vs->player))
	- ceil(ft_dist_t_dpos(vs->left_plan, vs->player)) < 1))
		add_wall_to_list(s, wall);
	else
	{
		ft_memdel((void **)&wall);
		return (NULL);
	}
	ft_create_new_wall2(wall, vtx, vs, 2);
	if (w_or_p == 'p')
	{
		sct = get_sector_by_id(s, vtx->sct_dest);
		wall->floor_height_dest = sct->floor;
		wall->ceiling_height_dest = sct->ceiling;
		wall->portal_value = vtx->vtx_dest->ptr->id;
	}
	wall->screen_width_wall = (WIDTH * ((ft_dist_t_dpos(wall->l_plan, wall->r_plan) * 100.0) / WIDTHPLAN))* 0.01;
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
	int		width_wall; //largeur du mur en pixel a l'ecran

	l_big_dist = ft_dist_t_dpos(wall->player, wall->left);
	r_big_dist = ft_dist_t_dpos(wall->player, wall->right);
	l_small_dist = ft_dist_t_dpos(wall->player, wall->l_plan);
	r_small_dist = ft_dist_t_dpos(wall->player, wall->r_plan);

	l_pct = (l_big_dist * 100.0) / l_small_dist;
	r_pct = (r_big_dist * 100.0) / r_small_dist;

	l_height_wall = HEIGHT / ((l_pct * 0.001) * 4) * (double)abs(wall->floor_height - wall->ceiling_height) * HEIGHT_MULT;
	r_height_wall = HEIGHT / ((r_pct * 0.001) * 4) * (double)abs(wall->floor_height - wall->ceiling_height) * HEIGHT_MULT;

	width_wall = wall->screen_width_wall;
	ft_init_diff_and_min(wall);

	return (ft_draw_wall(s, wall, l_height_wall, r_height_wall, width_wall));
}

void	ft_limit_ceiling_floor(t_main *s, t_dpos left, t_dpos right, t_visu *vs, char swich)
{
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
	t_4dpos	pos;
	t_dpos	l_plan;
	t_dpos	r_plan;

	pos.pos1 = vs->player;
	// printf("switch = %d\n", swich);
	// if (swich == 1 || swich == 4)
	// {
		// l_plan = vs->left_plan;
	pos.pos2 = left;
	// pos.pos2 = vs->right_plan;
	pos.pos3 = vs->left_plan;
	pos.pos4 = vs->right_plan;
	// pos.pos4 = right;
	ft_find_intersection(s, pos, 1);
	l_big_dist = (ft_dist_t_dpos(vs->player, left) / METRE);
	l_plan = s->tmp_intersect;
	// }
	// else
	// {
	// 	pos.pos1 = left;
	// 	pos.pos3 = vs->left_plan;
	// 	pos.pos4 = vs->right_plan;
	// 	ft_find_intersection(s, pos, 1);
	// 	l_plan = s->tmp_intersect;
	// 	l_big_dist = (ft_dist_t_dpos(vs->player, left) / METRE);
	// }
	// if (swich == 3 || swich == 4)
	// {
		pos.pos2 = right;
		// pos.pos2 = vs->right_plan;
		pos.pos3 = vs->left_plan;
		pos.pos4 = vs->right_plan;
		// pos.pos1 = vs->right_plan;
		// pos.pos3 = left;
		// pos.pos4 = right;
		ft_find_intersection(s, pos, 1);
		r_big_dist = (ft_dist_t_dpos(vs->player, right) / METRE);
		r_plan = s->tmp_intersect;
	// }
	// else
	// {
	// 	pos.pos1 = right;
	// 	pos.pos3 = vs->left_plan;
	// 	pos.pos4 = vs->right_plan;
	// 	ft_find_intersection(s, pos, 1);
	// 	r_plan = s->tmp_intersect;
	// 	r_big_dist = (ft_dist_t_dpos(vs->player, right) / METRE);
	// }
	l_small_dist = (ft_dist_t_dpos(vs->player, l_plan) / METRE);
	r_small_dist = (ft_dist_t_dpos(vs->player, r_plan) / METRE);
	l_height_wall = HEIGHT / ((((l_big_dist * 100.0) / l_small_dist) * 0.001) * 4)
	* ft_abs(vs->sct->floor - vs->sct->ceiling) * HEIGHT_MULT;
	r_height_wall = HEIGHT / ((((r_big_dist * 100.0) / r_small_dist) * 0.001) * 4)
	* ft_abs(vs->sct->floor - vs->sct->ceiling) * HEIGHT_MULT;
	width_wall = (WIDTH * ((ft_dist_t_dpos(l_plan, r_plan) * 100.0) / WIDTHPLAN))* 0.01;
	pos.pos1 = vs->left_point;
	pos.pos2 = vs->player;
	pos.pos3 = left;
	pos.pos4 = right;
	if (ft_find_intersection(s, pos, 1) > 0)
		x = 0;
	else
		x = (ft_dist_t_dpos(vs->left_plan, l_plan) / WIDTHPLAN) * WIDTH;
	s->player.eyesight = s->player.foot_height - vs->sct->floor + s->player.size;
	l_height_wall_diff = ft_get_diff_height_pxl(s->player.eyesight, vs->sct->ceiling, vs->sct->floor, l_height_wall);
	r_height_wall_diff = ft_get_diff_height_pxl(s->player.eyesight, vs->sct->ceiling, vs->sct->floor, r_height_wall);
	vs->left_ceiling_limit.x = (int)x;
	vs->left_ceiling_limit.y = (HEIGHT* 0.5) - (l_height_wall) + s->player.y_eye + l_height_wall_diff;
	vs->left_floor_limit.x = (int)x;
	vs->left_floor_limit.y = (HEIGHT* 0.5) + s->player.y_eye + l_height_wall_diff;
	vs->right_ceiling_limit.x = x + width_wall;
	vs->right_ceiling_limit.y = (HEIGHT* 0.5) - (r_height_wall) + s->player.y_eye + r_height_wall_diff;
	vs->right_floor_limit.x = vs->right_ceiling_limit.x;
	vs->right_floor_limit.y = (HEIGHT* 0.5) + s->player.y_eye + r_height_wall_diff;
}

void	ft_draw_visu(t_main *s, t_sector *sct, t_visu vs)
{
	t_walls		*wall;
	t_int		*vtx;

	vtx = sct->vertex;
	vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	if (!(vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id)))
		return ;
	create_all_walls(s, vtx, &vs, 1);
	// print_wall_list(s);
	wall = s->walls;
	// ft_multi_threading(s);
	while (wall)
	{
		ft_print_wall(s, wall);
		wall = wall->next;
	}
	set_visible_sprites(s, &vs);
	s->portal_nb = 0;
	// printf("--- FIN VISU ---\n\n");
}
