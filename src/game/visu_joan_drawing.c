#include "doom.h"

void	ft_draw_column(t_main *s, t_pos coord, int end, Uint32 color)
{
	int i;
	int begin;

	i = 0;
	begin = coord.y ;
	coord.y = 0 ;
	while (i++ < begin)
	{
		set_pixel(s->sdl->game, 0x485050ff, coord);
		coord.y++;
	}
	coord.y--;
	while (coord.y++ < end)
		set_pixel(s->sdl->game, color, coord);
	while (end++ < HEIGHT)
	{
		set_pixel(s->sdl->game, 0xa8b08eff, coord);
		coord.y++;
	}
}

int		ft_draw_wall(t_main *s, int x, int l_height_wall, int r_height_wall, double width_wall)
{
	int		diff_wall;
	double	i;
	int		height_wall;
	t_pos	coord;
	int		bottom;
	double	pct_avcm; //pourcentage avancement

	i = 0;
	diff_wall = abs(l_height_wall - r_height_wall); //calcule de la diff de hauteur entre les deux murs div par deux (pour haut et bas)
	// printf("diff = %d\n",diff_wall);
	height_wall = l_height_wall;
	coord.x = x;
	// printf("Largeur du mur = %f\n", width_wall);
	while (i++ < width_wall)
	{
		coord.y = (HEIGHT / 2) - height_wall / 2 +s->player.y_eye +  s->player.eyesight; //haut du mur
		bottom = (HEIGHT / 2) + height_wall / 2 + s->player.y_eye + s->player.eyesight; //bas du mur
		if (i == 1 || i == width_wall)
			ft_draw_column(s, coord, bottom, 0x000000FF);
		else
			ft_draw_column(s, coord, bottom, 0xb0842fff);
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

void clear_wall_list(t_main *s)
{
	t_walls *tmp;

	tmp = s->walls;
	while (s->walls)
	{
		tmp = s->walls;
		s->walls = s->walls->next;
		free(tmp);
	}
	s->walls = NULL;
}

void	put_wall_before(t_main *s, t_walls *new, t_walls *current)
{
	if (current->prev == NULL)
	{
		new->next = current;
		current->prev = new;
		s->walls = new;
	}
	else
	{
		new->next = current;
		new->prev = current->prev;
		new->prev->next = new;
		current->prev = new;
	}

}

void	put_wall_after(t_walls *new, t_walls *current)
{
	if (current->next == NULL)
	{
		current->next = new;
		new->prev = current;
	}
	else
	{
		new->next = current->next;
		new->prev = current;
		current->next->prev = new;
		current->next = new;
	}

}

void	add_wall_to_list(t_main *s, t_walls *new)
{
	t_walls *tmp;

	tmp = s->walls;
	// printf("new->distqnce = %f\n", new->distance);
	if (tmp == NULL) //S'il n'y a aucun mur dans la liste
	{
		s->walls = new;
		// printf("pas de mur\n");
		return ;
	}

	while (tmp->next && new->distance < tmp->distance) //On avance tant que la distance du nouveau mur est plus petite que le mur actuek
		tmp = tmp->next;
		if (new->distance > tmp->distance)
			put_wall_before(s, new, tmp);
		else
			put_wall_after(new, tmp);
}

int		ft_print_wall(t_main *s, int x, t_dpos player, t_dpos lwall, t_dpos rwall, t_dpos lplan, t_dpos rplan)
{
	double	l_big_dist;
	double	r_big_dist;
	double	l_small_dist;
	double	r_small_dist;
	double	l_pct;
	double	r_pct;
	int		l_height_wall;
	int		r_height_wall;
	double	pct_plan;
	double	width_wall;

	l_big_dist = ft_dist_t_dpos(player, lwall);
	r_big_dist = ft_dist_t_dpos(player, rwall);
	l_small_dist = ft_dist_t_dpos(player, lplan);
	r_small_dist = ft_dist_t_dpos(player, rplan);

	l_pct = (l_big_dist * 100.0) / l_small_dist; //calcule des ratios mur gauche et droit
	r_pct = (r_big_dist * 100.0) / r_small_dist;

	l_height_wall = HEIGHT / ((l_pct * 0.001) * 4); //calcule des hauteur des murs gauche et droit
	r_height_wall = HEIGHT / ((r_pct * 0.001) * 4);

	pct_plan = (ft_dist_t_dpos(lplan, rplan) * 100.0) / WIDTHPLAN; //calcule de la largeur du mur dans la fenetre
	width_wall = (WIDTH * pct_plan) / 100;
	// printf("Mur vtx gauche(%.2f, %.2f)      vtx droit(%.2f, %.2f)    ",lwall.x / METRE, lwall.y / METRE, rwall.x / METRE, rwall.y / METRE);
	// printf("\nx entree = %d", x);
	x = ft_draw_wall(s, x, l_height_wall, r_height_wall, width_wall);
	// printf("      x sortie= %d\n", x);
	// printf("Hauteur du mur Gauche (%d)\n",l_height_wall);
	// printf("Hauteur du mur Droit  (%d)\n\n\n",r_height_wall);

	return(x);
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

	// printf("vs->left_point.x = %f, vs->left_point.y = %f\n", vs->left_point.x, vs->left_point.y);
	dist = ft_find_intersection(s, vs->left_point, vs->player, left, right, 1);
	if (dist > 0)
		wall->left = s->tmp_intersect;
	else
		wall->left = left;
	ft_find_intersection(s, wall->left, vs->player, vs->left_plan, vs->right_plan, 1);
	wall->l_plan = s->tmp_intersect;
	if (dist > 0)
		wall->x = 0;
	else
		wall->x = (ft_dist_t_dpos(vs->left_plan, wall->l_plan) / WIDTHPLAN) * WIDTH;

	dist = ft_find_intersection(s, vs->right_point, vs->player, left, right, 1);
	if (dist > 0)
	{
		wall->right = s->tmp_intersect;
		printf("true\n");
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
		printf("Mur[%d] ajouté\n", vtx->ptr->id);
		printf("%f et %f\n", ft_dist_t_dpos(wall->l_plan, vs->left_plan), ft_dist_t_dpos(wall->r_plan, vs->left_plan));
	}
	else
	{
		printf("Mur[%d] caché\n", vtx->ptr->id);
	}
}

void	draw_first_wall(t_main *s, t_int *vtx, t_visu *vs)
{
	// if (vs->begin_wall_id != vs->end_wall_id)
	// {
	// 	vs->tmp_wall.x = vtx->ptr->x * METRE;
	// 	vs->tmp_wall.y = vtx->ptr->y * METRE;
	// }
	// else
	// {
	// 	vs->tmp_wall.x = vs->end.x;
	// 	vs->tmp_wall.y = vs->end.y;
	// }
	// ft_find_intersection(s, vs->tmp_wall, vs->player, vs->left_plan, vs->right_plan, 1);
	// if (vtx->wall_value != -1)
	// 	ft_print_portal(s, 0, vs->player, vs->begin, vs->tmp_wall, vs->left_plan, vs->right_plan, vtx);
	// else
		ft_create_new_wall(s, vtx, vs);
}

t_int	*draw_mid_walls(t_main *s, t_int *vtx, t_visu *vs)
{
	t_visu	fake_vs;
	t_dpos	fake_player;
	double	fake_angle;
	double	angle_right;
	double	angle_left;
	double	demi_fov;
	t_int 	*vtx_ori;
	int 	i;

	vtx_ori = vtx;
	i = 0;
	while (vtx->ptr->id != vs->end_wall_id)
	{
		if (vtx->wall_value != -1)
		{
			fake_angle = 0;
			fake_player = ft_get_fake_player(s, vs->player, vtx, &fake_angle);
			printf("player angle = %f, fake angle = %f\n",s->player.angle, fake_angle);
			fake_vs = ft_place_view_plan(s, fake_player, fake_angle, 0x4bd9ffff);
			fake_vs.sct_id = vtx->sct_dest;
			demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player, fake_vs.left_plan), METRE, WIDTHPLAN / 2);
			// printf("demi_fov = %f\n",demi_fov);
			angle_left = fake_angle + demi_fov;
			angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
			angle_right = fake_angle - demi_fov;
			angle_right = angle_right < 0 ? angle_right + 360: angle_right;
			fake_vs = get_walls_to_draw(s, fake_player, angle_left, angle_right, fake_vs);
			fake_vs.begin_wall_id = vtx->vtx_dest->ptr->id;
			fake_vs.end_wall_id = vtx->vtx_dest->prev->ptr->id;
			// vtx = get_t_int_from_vertex(vtx, vtx->vtx_dest->ptr->id);

			// printf("PORTAIL SECTEUR = %d\n", vtx->sct_dest);
			// add_portal_to_list(s, fake_player, get_sector_by_id(s, vtx->sct_dest), fake_vs);
		}

		else
			ft_create_new_wall(s, vtx, vs);
		vtx = vtx_ori->next;
		// {s->line.x1 = wall->l_plan.x + s->editor->decal_x;
		// 	s->line.y1 = wall->l_plan.y + s->editor->decal_y;
		// 	s->line.x2 = wall->left.x + s->editor->decal_x;
		// 	s->line.y2 = wall->left.y + s->editor->decal_y;
		// 	get_line(s, 0xea7cfcff);
		// s->line.x1 = wall->r_plan.x + s->editor->decal_x;
		// s->line.y1 = wall->r_plan.y + s->editor->decal_y;
		// s->line.x2 = wall->right.x + s->editor->decal_x;
		// s->line.y2 = wall->right.y + s->editor->decal_y;
		// get_line(s, 0xea7cfcff);}
	}
	return(vtx);
}

void draw_last_wall(t_int *vtx, t_visu *vs)
{
	vs->begin.x = vtx->ptr->x * METRE;
	vs->begin.y = vtx->ptr->y * METRE;
	vs->tmp_wall.x = vtx->next->ptr->x * METRE;
	vs->tmp_wall.y = vtx->next->ptr->y * METRE;
}

void	ft_draw_visu(t_main *s, t_dpos player, t_sector *sct, t_visu vs)
{
	t_walls		*tmp;
	t_dpos		plan_left;
	int			x;
	t_int		*vtx;
	int			new_x;

	x = 0;
	new_x = 0;
	// printf("sct->vertex")
	vtx = sct->vertex;
	vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	draw_first_wall(s, vtx, &vs);

	plan_left = s->tmp_intersect;
	printf("end wall id = %d\n", get_t_int_by_vertex_id(sct->vertex, vs.end_wall_id)->id);
	if (vs.begin_wall_id == vs.end_wall_id) // cas 1 seul mur
	{
		tmp = s->walls;
		ft_print_wall(s, tmp->x, player, tmp->left, tmp->right, tmp->l_plan, tmp->r_plan);
		clear_wall_list(s);
		return ;
	}

	vtx = vtx->next;
	vtx = draw_mid_walls(s, vtx, &vs);

	draw_last_wall(vtx, &vs);
	ft_find_intersection(s, vs.begin, vs.player, vs.left_plan, vs.right_plan, 1);
	// plan_left = s->tmp_intersect;
	// x = (ft_dist_t_dpos(vs.left_plan, plan_left) / WIDTHPLAN) * WIDTH;
	ft_create_new_wall(s, vtx, &vs);

	// print_wall_list(s);
	tmp = s->walls;
	if ((tmp = s->walls) != NULL)
		x = tmp->x;
	while(tmp)
	{
		if ((new_x = ft_print_wall(s, tmp->x, player, tmp->left, tmp->right, tmp->l_plan, tmp->r_plan)) > x)
		{
			x = new_x;
			plan_left = tmp->r_plan;
		}
		tmp = tmp->next;
	}
	// print_wall_list(s);
	clear_wall_list(s);
	// s->line.x1 = s->visu.tmp_wall.x + s->editor->decal_x;
	// s->line.y1 = s->visu.tmp_wall.y + s->editor->decal_y;
	// s->line.x2 = plan_right.x + s->editor->decal_x;
	// s->line.y2 = plan_right.y + s->editor->decal_y;
	// get_line(s, 0xea7cfcff);
	// printf("---------------------------------------------\n");
}
