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
		ft_memdel((void **)&tmp);
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
	// printf("3\n");

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
	// printf("MUHAHAHA\n");
	if (dist > 0)
	{
		wall->right = s->tmp_intersect;
		// printf("true\n");
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
//		printf("Mur[%d] ajouté\n", vtx->ptr->id);
	//	printf("%f et %f\n", ft_dist_t_dpos(wall->l_plan, vs->left_plan), ft_dist_t_dpos(wall->r_plan, vs->left_plan));
	}
	else
	{
		// printf("Mur[%d] caché\n", vtx->ptr->id);
	}
}

void	draw_first_wall(t_main *s, t_int *vtx, t_visu *vs)
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
		demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player, fake_vs.left_plan), METRE, WIDTHPLAN / 2);
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
		if ((ft_find_intersection(s, wall1, wall2, fake_vs.left_point, fake_player, 1)) == 0)
		{
			fake_vs.begin.x = fake_vs.vtx_gauche->ptr->x * METRE;
			fake_vs.begin.y = fake_vs.vtx_gauche->ptr->y * METRE;
		}
		else
			fake_vs.begin = s->tmp_intersect;
		if ((ft_find_intersection(s, wall1, wall2, fake_vs.right_point, fake_player, 1)) == 0)
		{
			fake_vs.end.x = fake_vs.vtx_droite->ptr->x * METRE;
			fake_vs.end.y = fake_vs.vtx_droite->ptr->y * METRE;
		}
		else
			fake_vs.end = s->tmp_intersect;

		// printf("begin = x:%f y:%f\n", fake_vs.begin.x, fake_vs.begin.y);
		// fake_vs.begin_wall_id = ft_find_wall2(s, fake_vs.begin, fake_vs.left_point, 0x37f3ffff, fake_vs.sct_id); // #37f3ff
		// printf("begin wall id = %d\n", fake_vs.begin_wall_id);
		// if (fake_vs.begin_wall_id == 0)
		// 	fake_vs.begin_wall_id = fake_vs.vtx_gauche->ptr->id;
		// tmp = s->tmp_intersect;
		// tmp.x += s->editor->decal_x;
		// tmp.y += s->editor->decal_y;

		// fake_vs.end_wall_id = ft_find_wall2(s, fake_vs.end, fake_vs.right_point, 0x37f3ffff, fake_vs.sct_id);
		// if (fake_vs.end_wall_id == 0)
		// 	fake_vs.end_wall_id = fake_vs.vtx_droite->ptr->id;
		// fake_vs.end.x = vtx->vtx_dest->ptr->x * METRE;
		// fake_vs.end.y = vtx->vtx_dest->ptr->y * METRE;
		// fake_vs.end.x -= s->editor->decal_x;
		// fake_vs.end.y -= s->editor->decal_y;
		// printf("end.x = %f end.y = %f, ptr id = %d\n", fake_vs.end.x, fake_vs.end.y, fake_vs.end_wall_id);
		// printf("begin  %d, end = %d\n", fake_vs.begin_wall_id, fake_vs.end_wall_id);
		// fake_vs.begin = ft_pos_to_dpos(vtx->vtx_dest->next->ptr->pos);
		// fake_vs.begin_wall = get_t_int_by_vertex_id(fake_vs.sct->vertex, fake_vs.begin_wall_id);
		// if (fake_vs.begin_wall== NULL)
		// 	handle_error(s, POINTER_ERROR);
		// printf("va ajouter portail\n");
		if (s->portal_nb < PORTAL_LIMIT)
			add_portal_to_list(s, fake_player, fake_vs.sct, fake_vs);
	}
	else
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
	int 	i;
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
				// printf("fplayer_pos.y = %f\n", s->fplayer_pos.y);
			}
			fake_vs.sct_id = vtx->sct_dest;
			fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
			fake_vs.vtx_droite = vtx->vtx_dest;
			if (fake_vs.vtx_droite == NULL)
				handle_error(s, POINTER_ERROR);
			fake_vs.vtx_gauche = vtx->vtx_dest->next;
			demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_player, fake_vs.left_plan), METRE, WIDTHPLAN / 2);
			// printf("demi_fov = %f\n",demi_fov);
			angle_left = fake_angle + demi_fov;
			angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
			angle_right = fake_angle - demi_fov;
			angle_right = angle_right < 0 ? angle_right + 360: angle_right;
			fake_vs = get_walls_to_draw(s, fake_player, angle_left, angle_right, fake_vs);
			wall1.x = fake_vs.vtx_gauche->ptr->x * METRE;
			wall1.y = fake_vs.vtx_gauche->ptr->y * METRE;
			wall2.x = fake_vs.vtx_droite->ptr->x * METRE;
			wall2.y = fake_vs.vtx_droite->ptr->y * METRE;
			// ft_find_intersection(s, wall1, wall2, fake_vs.left_point, fake_player, 1);
			// ft_find_wall2(s, fake_player, fake_vs.left_point, 0x37f3ffff, fake_vs.sct_id);
			if ((ft_find_intersection(s, wall1, wall2, fake_vs.left_point, fake_player, 1)) == 0)
			{
				fake_vs.begin.x = fake_vs.vtx_gauche->ptr->x * METRE;
				fake_vs.begin.y = fake_vs.vtx_gauche->ptr->y * METRE;
			}
			else
				fake_vs.begin = s->tmp_intersect;
			if ((ft_find_intersection(s, wall1, wall2, fake_vs.right_point, fake_player, 1)) == 0)
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

void draw_last_wall(t_main *s, t_int *vtx, t_visu *vs)
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
			ft_find_intersection(s, wall1, wall2, fake_vs.left_point, fake_player, 1);
			// ft_find_wall2(s, fake_player, fake_vs.left_point, 0x37f3ffff, fake_vs.sct_id);
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
			ft_create_new_wall(s, vtx, vs);
		}


}

void	ft_draw_visu(t_main *s, t_dpos player, t_sector *sct, t_visu vs)
{
	t_walls		*tmp;
	t_int		*vtx;
	(void)player;

	vtx = sct->vertex;
	vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	if (!(vtx = get_t_int_by_vertex_id(vtx, vs.begin_wall_id)))
		return ;
		// handle_error(s, POINTER_ERROR);
	draw_first_wall(s, vtx, &vs);
	if (vs.begin_wall_id == vs.end_wall_id) // cas 1 seul mur
	{
		tmp = s->walls;
		if (tmp != NULL)
		{
			while (tmp)
			{
				ft_print_wall(s, tmp->x, tmp->player, tmp->left, tmp->right, tmp->l_plan, tmp->r_plan);
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
	// print_wall_list(s);
	tmp = s->walls;
	while(tmp)
	{
		ft_print_wall(s, tmp->x, tmp->player, tmp->left, tmp->right, tmp->l_plan, tmp->r_plan);
		tmp = tmp->next;
	}
	// print_wall_list(s);
	clear_wall_list(s);
	s->portal_nb = 0;
	// s->line.x1 = s->visu.tmp_wall.x + s->editor->decal_x;
	// s->line.y1 = s->visu.tmp_wall.y + s->editor->decal_y;
	// s->line.x2 = plan_right.x + s->editor->decal_x;
	// s->line.y2 = plan_right.y + s->editor->decal_y;
	// get_line(s, 0xea7cfcff);
	// printf("---------------------------------------------\n");
}
