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

void	put_wall_after(t_main *s, t_walls *new, t_walls *current)
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
			put_wall_after(s, new, tmp);
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

	x = ft_draw_wall(s, x, l_height_wall, r_height_wall, width_wall);
	// printf("Hauteur du mur Gauche (%d)\n",l_height_wall);
	// printf("Hauteur du mur Droit  (%d)\n\n\n",r_height_wall);

	return(x);
}

int		draw_first_wall(t_main *s, t_int *vtx, t_visu *vs, int x)
{
	if (vs->begin_wall_id != vs->end_wall_id)
	{
		vs->tmp_wall.x = vtx->ptr->x * METRE;
		vs->tmp_wall.y = vtx->ptr->y * METRE;
	}
	else
	{
		vs->tmp_wall.x = vs->end.x;
		vs->tmp_wall.y = vs->end.y;
	}
	ft_find_intersection(s, vs->tmp_wall, vs->player, vs->left_plan, vs->right_plan, 1);
	x = ft_print_wall(s, x, vs->player, vs->begin, vs->tmp_wall, vs->left_plan, s->tmp_intersect);
	return(x);
}

t_int *draw_mid_walls(t_main *s, t_int *vtx, t_visu *vs)
{
	t_walls		*wall;

while (vtx->id != vs->end_wall_id)
{
	if (!(wall = (t_walls*)malloc(sizeof(t_walls))))
		handle_error(s, MALLOC_ERROR);
	wall->next = NULL;
	wall->prev = NULL;
	wall->player = vs->player;
	wall->left.x = vtx->ptr->x * METRE;
	wall->left.y = vtx->ptr->y * METRE;
	wall->right.x = vtx->next->ptr->x * METRE;
	wall->right.y = vtx->next->ptr->y * METRE;
	vs->begin = vs->tmp_wall;
	vtx = vtx->next;
	vs->tmp_wall.x = vtx->ptr->x * METRE;
	vs->tmp_wall.y = vtx->ptr->y * METRE;
	ft_find_intersection(s, wall->left, vs->player, vs->left_plan, vs->right_plan, 1);
	wall->l_plan = s->tmp_intersect;
	ft_find_intersection(s, wall->right, vs->player, vs->left_plan, vs->right_plan, 1);
	wall->r_plan = s->tmp_intersect;
	wall->x = (ft_dist_t_dpos(vs->left_plan, wall->l_plan) / WIDTHPLAN) * WIDTH;
	wall->distance = max(wall->left.x, vs->player.x) - min(wall->left.x, vs->player.x)
	+ max(wall->left.y, vs->player.y) - min(wall->left.y, vs->player.y)
	+ max(wall->right.x, vs->player.x) - min(wall->right.x, vs->player.x)
	+ max(wall->right.y, vs->player.y) - min(wall->right.y, vs->player.y);
	if (ft_dist_t_dpos(wall->l_plan, vs->left_plan) <
	ft_dist_t_dpos(wall->r_plan, vs->left_plan))
		add_wall_to_list(s, wall);

		{s->line.x1 = wall->l_plan.x + s->editor->decal_x;
		s->line.y1 = wall->l_plan.y + s->editor->decal_y;
		s->line.x2 = wall->left.x + s->editor->decal_x;
		s->line.y2 = wall->left.y + s->editor->decal_y;
		get_line(s, 0xea7cfcff);}
		{s->line.x1 = wall->r_plan.x + s->editor->decal_x;
		s->line.y1 = wall->r_plan.y + s->editor->decal_y;
		s->line.x2 = wall->right.x + s->editor->decal_x;
		s->line.y2 = wall->right.y + s->editor->decal_y;
		get_line(s, 0xea7cfcff);}
}
	return(vtx);
}

void draw_last_wall(t_main *s, t_int *vtx, t_visu *vs)
{
	vs->begin.x = vtx->ptr->x * METRE;
	vs->begin.y = vtx->ptr->y * METRE;
	vs->tmp_wall.x = vtx->next->ptr->x * METRE;
	vs->tmp_wall.y = vtx->next->ptr->y * METRE;
}

void	ft_draw_visu(t_main *s, t_dpos player, t_sector *sct, t_visu vs)
{
	t_walls *tmp;
	t_dpos		plan_left;
	int			x;
	t_int		*vtx;
	int				new_x;

	x = 0;
	new_x = 0;
	vtx = get_t_int_by_id(sct->vertex, vs.begin_wall_id)->next;// trouver le deuxieme vertex du premier mur
	x = draw_first_wall(s, vtx, &vs, x);
	plan_left = s->tmp_intersect;
	if (vs.begin_wall_id == vs.end_wall_id)
		return ;
	// printf("point gauche x = %f, y = %f\n",vs.begin.x, vs.begin.y);
	// printf("vertex %d, x = %f, y = %f\n", vtx->id, vs.tmp_wall.x, vs.tmp_wall.y);
	// {s->line.x1 = vs.tmp_wall.x + s->editor->decal_x;
	// s->line.y1 = vs.tmp_wall.y + s->editor->decal_y;
	// s->line.x2 = plan_right.x + s->editor->decal_x;
	// s->line.y2 = plan_right.y + s->editor->decal_y;
	// get_line(s, 0xea7cfcff);}
	// plan_left = plan_right;
	vtx = draw_mid_walls(s, vtx, &vs);
	// ft_test_chainlist(s);
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
	clear_wall_list(s);
	draw_last_wall(s, vtx, &vs);
	ft_print_wall(s, x, player, vs.begin, vs.end, plan_left, vs.right_plan);


	// s->line.x1 = s->visu.tmp_wall.x + s->editor->decal_x;
	// s->line.y1 = s->visu.tmp_wall.y + s->editor->decal_y;
	// s->line.x2 = plan_right.x + s->editor->decal_x;
	// s->line.y2 = plan_right.y + s->editor->decal_y;
	// get_line(s, 0xea7cfcff);
	// printf("---------------------------------------------\n\n\n\n");
}
