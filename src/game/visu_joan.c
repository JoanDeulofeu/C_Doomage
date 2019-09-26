#include "doom.h"

int		ft_find_wall2(t_main *s, t_dpos player, t_dpos point, Uint32 color, int sct_id)
{
	t_sector	*sct;
	t_int		*s_vtx;
	t_dpos		wall1;
	t_dpos		wall2;
	int			id_wall = 0;
	int			i;
	int			dist;
	int			new_dist;

	dist = 100000;
	new_dist = 0;
	sct = s->sector;
	if (sct_id == 0)
		handle_error(s, SECTOR_ERROR);
	while (sct_id != sct->id)
		sct = sct->next;
	s_vtx = sct->vertex;
	i = 0;
	while (i++ < sct->vertex->prev->id)
	{
		wall1.x = s_vtx->ptr->x * METRE;
		wall1.y = s_vtx->ptr->y * METRE;
		wall2.x = s_vtx->next->ptr->x * METRE;
		wall2.y = s_vtx->next->ptr->y * METRE;
		// printf("wall1(%.1f, %.1f) | wall2(%.1f, %.1f) | player(%.1f, %.1f) | point(%.1f, %.1f)\n", wall1.x, wall1.y, wall2.x, wall2.y, player.x, player.y, point.x, point.y);
		if (sct_id == 2)
		{
			s->line.x1 = player.x + s->editor->decal_x;
			s->line.y1 = player.y + s->editor->decal_y;
			s->line.x2 = point.x + s->editor->decal_x;
			s->line.y2 = point.y + s->editor->decal_y;
			get_line(s, color, 1);
		}
		if ((new_dist = ft_find_intersection(s, wall1, wall2, point, player, 1)) > 0)
		{
			s->line.x1 = player.x + s->editor->decal_x;
			s->line.y1 = player.y + s->editor->decal_y;
			s->line.x2 = point.x + s->editor->decal_x;
			s->line.y2 = point.y + s->editor->decal_y;
			get_line(s, color, 1);
			// printf("on test le mur[%d] : dist = %d, new_dist = %d\n", s_vtx->id, dist, new_dist);
			// printf("point(%.1f, %.1f), player(%.1f, %.1f), wall1(%.1f, %.1f), wall2(%.1f, %.1f)\n", point.x, point.y, player.x, player.y, wall1.x / METRE, wall1.y / METRE, wall2.x / METRE, wall2.y / METRE);
			// printf("play.y = %f | point.y = %f\n", player.y + s->editor->decal_y, point.y + s->editor->decal_y);
			// return (id_wall);
			if (new_dist < dist && new_dist != 0 && new_dist != -1)
			{
				// printf("on test le mur[%d] : dist = %d, new_dist = %d\n", s_vtx->id, dist, new_dist);
				id_wall = s_vtx->ptr->id;
				// printf("vertex = %d\n", id_wall);
				dist = new_dist;
			}

		}
		// id_wall++;
		s_vtx = s_vtx->next;
	}
	// printf("wall =  %d\n", get_t_int_by_vertex_id(sct->vertex, id_wall)->id);
	return (id_wall);
}

t_visu	ft_place_view_plan(t_main *s, t_dpos player, double angle, Uint32 color)
{
	// printf("chocolat\n");
	t_dpos	ctr_p; //center plan
	t_visu	vs;

	ctr_p.x = player.x + cos(to_rad(angle)) * METRE;
	ctr_p.y = player.y - sin(to_rad(angle)) * METRE;
	vs.left_plan.x = ctr_p.x + cos(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.left_plan.y = ctr_p.y - sin(to_rad(angle + 90)) * WIDTHPLAN / 2;
	vs.right_plan.x = ctr_p.x + cos(to_rad(angle - 90)) * WIDTHPLAN / 2;
	vs.right_plan.y = ctr_p.y - sin(to_rad(angle - 90)) * WIDTHPLAN / 2;

	s->line.x1 = vs.left_plan.x + s->editor->decal_x;
	s->line.y1 = vs.left_plan.y + s->editor->decal_y;
	s->line.x2 = vs.right_plan.x + s->editor->decal_x;
	s->line.y2 = vs.right_plan.y + s->editor->decal_y;
	get_line(s, color, 1);
	return(vs);
}

t_visu get_walls_to_draw(t_main *s, t_dpos player, double l_angle, double r_angle, t_visu vs)
{
	// printf("entree-----------\n");
	vs.left_point.x = player.x + cos(to_rad(l_angle)) * 2000;
	vs.left_point.y = player.y - sin(to_rad(l_angle)) * 2000;
	vs.begin_wall_id = ft_find_wall2(s, player, vs.left_point, 0xffed00ff, vs.sct_id);
	// if(vs.begin_wall_id == 0)
	// 	exit(0);
	vs.begin = s->tmp_intersect;
// printf("------MUR DROITE------\n");
	vs.right_point.x = player.x + cos(to_rad(r_angle)) * 2000;
	vs.right_point.y = player.y - sin(to_rad(r_angle)) * 2000;
	vs.end_wall_id = ft_find_wall2(s, player, vs.right_point, 0x59ff00ff, vs.sct_id);
	if(vs.end_wall_id == 0 && vs.begin_wall_id != 0)
		vs.end_wall_id = get_t_int_by_vertex_id(get_sector_by_id(s, vs.sct_id)->vertex, vs.begin_wall_id)->next->ptr->id;
	// 	exit(0);
	vs.end = s->tmp_intersect;
	// printf("TEST vs.end (%.1f, %.1f)\n", vs.end.x, vs.end.y);
	vs.player = player;
	// printf("\nsortie-----------\n\n");
	return(vs);
}

t_dpos	to_metre(t_pos pos)
{
	t_dpos	new;

	new.x = pos.x * METRE;
	new.y = pos.y * METRE;
	return (new);
}

void 	teleport_player(t_main *s, const unsigned char *keys)
{
	t_dpos	player_haut;
	t_dpos	player_bas;
	int		ptr_id;
	int		sct_id;
	t_int	*wall;
	int		nb;

	(void)keys;
	nb = 10;
	ptr_id = 0;
	// printf("x = %f, y = %f\n", s->col_pos.x, s->col_pos.y);
	player_haut = s->col_pos;
	player_bas = s->col_pos;
	player_haut.y += nb;
	player_bas.y -= nb;
	// new_pos.x = 0;
	// new_pos.y = 0;
	sct_id = s->player.sector_id;
	if (sct_id == 0)
		printf ("FUUUUUUUUU\n");
	while (ptr_id == 0)
	{
		player_haut = s->col_pos;
		player_bas = s->col_pos;
		player_haut.y += nb;
		player_bas.y -= nb;
		if ((ptr_id = ft_find_wall2(s, player_bas, player_haut, BLUE, sct_id)) == 0)
		{
			player_haut = s->col_pos;
			player_bas = s->col_pos;
			player_haut.x += nb;
			player_bas.x -= nb;
			ptr_id = ft_find_wall2(s, player_bas, player_haut, BLUE, sct_id);
		}
		nb++;
	}
		wall = get_t_int_by_vertex_id(get_sector_by_id(s, sct_id)->vertex, ptr_id);
		if (wall->vtx_dest == NULL)
		{
			printf("true\n");
			// if (wall->next->vtx_dest != NULL && wall->prev->vtx_dest != NULL)
			// {
			// 	printf("true\n");
			// 	if (ft_dist_t_dpos(ft_pos_to_dpos(wall->next->vtx_dest->ptr->pos), s->col_pos) <
			// 	ft_dist_t_dpos(ft_pos_to_dpos(wall->prev->vtx_dest->ptr->pos), s->col_pos))
			// 		wall = wall->next;
			// 	else
			// 		wall = wall->prev;
			// 	printf("cas particulier\n");
			// }
			if (wall->next->vtx_dest != NULL) // Au cas où find intersection ne renvoie pas le bon mur, on check lequel a coté est un portail
				wall = wall->next;
			else if (wall->prev->vtx_dest != NULL)
				wall = wall->prev;
			printf("securité intersection marche\n");
		}
		if (wall == NULL)
			printf("ptr_id = %d\n", ptr_id);
		//TROUVER POURQUOI IL TROUVE UN SECTEUR A 0 !!!

		s->player.pos = ft_get_fake_player(s, s->col_pos, wall, &s->player.angle);
		// player = s->player.pos;
		// player.y--;
		//changer secteur en fonction de la teleportation
		s->player.sector_id = wall->sct_dest;
		s->portal_nb = 0;
		// if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
		// 	s->player.pos = get_direction(s, keys, 1, s->player.pos);
		if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
			ft_move_player(s, keys, 1);
}

void	ft_visu_joan(t_main *s, const unsigned char *keys)
{
	double	angle_left;
	double	angle_right;
	double	demi_fov;
	// t_dpos	point;
	t_visu	vs;
	// t_visu	*vsu = &s->visu;
	t_dpos	player;
	// int		dist;
	// double	angle;

	// sct_id = s->player.sector_id;
	bzero(&vs, sizeof(t_visu));
	// printf("visu\n");
	(void)keys;
	// s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos));
	// printf("r_pos x = %f, pos.x = %f\n", s->player.r_pos.x, s->player.pos.x);
	player.x = s->player.r_pos.x * METRE;
	player.y = s->player.r_pos.y * METRE;
	// }


	// printf("s->visu = %f et vs->left_plan = %f\n", s->visu.left_plan.x, vs.left_plan.x);
	vs = ft_place_view_plan(s, player, s->player.angle, 0x4bd9ffff);
	// printf("sct id = %d\n", s->player.sector_id);
	vs.sct_id = s->player.sector_id;
	vs.sct = get_sector_by_id(s, s->player.sector_id);

	demi_fov = ft_find_angle_plan(ft_dist_t_dpos(player, vs.left_plan), METRE, WIDTHPLAN / 2);
	// printf("demi_fov = %f\n",demi_fov);
	angle_left = s->player.angle + demi_fov;
	angle_left = angle_left > 360 ? angle_left - 360 : angle_left;
	angle_right = s->player.angle - demi_fov;
	angle_right = angle_right < 0 ? angle_right + 360: angle_right;
	// draw_anchor(s, ft_dpos_to_pos(player), PINK);
	// update_image(s, s->sdl->editor);
	vs = get_walls_to_draw(s, player, angle_left, angle_right, vs);
	// draw_skybox(s, vs);
	// printf("s->player->angle = %f, vs.angle = %f, vs.sct = %d, player.x = %f, player.y = %f\n", s->player.angle, vs.angle, vs.sct->id, player.x, player.y);
	ft_draw_visu(s, player, get_sector_by_id(s, s->player.sector_id), vs);
// printf("------  SORTIE  ------\n");

	// printf("mur gauche = %d\nmur droite = %d\n", vs.begin_wall_id, vs.end_wall_id);
	// printf("angle gauche = %.2f\nangle droite = %.2f\n\n", angle_left, angle_right);

}










//lol <== hey... è.é
