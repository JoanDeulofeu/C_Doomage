#include "doom.h"

// t_visu		fill_visu_values_2(t_main *s, t_visu fake_vs, double fake_angle)
// {
// 	double	demi_fov;
//
// 	demi_fov = ft_find_angle_plan(ft_dist_t_dpos(fake_vs.player,
// 		fake_vs.left_plan), METRE, WIDTHPLAN / 2);
// 	fake_vs.angle = angle_mod(fake_angle);
// 	fake_vs = get_walls_to_draw(s, fake_vs.player, fake_vs);
// 	return (fake_vs);
// }

t_visu		fill_visu_values(t_main *s, t_visu *vs, t_int *vtx)
{
	double	fake_angle;
	t_visu	fake_vs;
	t_dpos	fake_player;

	if (s->printf)
	{
		s->display_mode = editor;
		ft_reset_color_screen(s->sdl->editor->content, WIDTH * HEIGHT);
		ft_draw_editor(s->editor, s->sdl->editor);
		display_map(s);
		draw_sprites_ori(s);
		ft_draw_all_wall(s);
			if (s->editor->mode == portal)
			change_over_wall(s);
		draw_editor_menu(s, 0, WIDTH / 2
			- (s->editor->menu.image[s->editor->menu.current]->w / 2), -1);
		draw_space_menu(s);
	}
	fake_angle = 0;
	fake_player = ft_get_fake_player(s, vs->player, vtx, &fake_angle, vs->angle);
	fake_vs = ft_place_view_plan(s, fake_player, fake_angle, 0x4bd9ffff); // #4bd9ff
	fake_vs.player = fake_player;
	fake_vs.prev_sct_id = vtx->sct;
	fake_vs.sct_id = vtx->sct_dest;
	// printf("sct_id = %d\n", fake_vs.sct_id);
	fake_vs.sct = get_sector_by_id(s, vtx->sct_dest);
	fake_vs.angle = angle_mod(fake_angle);
	fake_vs = get_walls_to_draw(s, fake_vs.player, fake_vs);
	// printf("begin wall = %d, end wall = %d\n", fake_vs.begin_wall_id, fake_vs.end_wall_id);
	fake_vs.vtx_droite = vtx->vtx_dest;
	if (fake_vs.vtx_droite == NULL)
		handle_error(s, POINTER_ERROR);
	fake_vs.vtx_gauche = vtx->vtx_dest->next;
	return (fake_vs);
}

int			check_portal_doover(t_main *s, t_int *vtx)
{
	t_walls *wall;

	wall = s->walls;
	while (wall)
	{
		if (wall->portal_value == vtx->ptr->id)
			return (0);
		wall = wall->next;
	}
	return (1);
}

void		handle_visu_portal(t_main *s, t_int *vtx, t_visu *vs, int swich)
{
	t_visu	fake_vs;
	t_4dpos	pos;

	fake_vs = fill_visu_values(s, vs, vtx);
	pos.pos1 = vtx->vtx_dest->next->ptr->m_pos;
	pos.pos2 = vtx->vtx_dest->ptr->m_pos;
	// printf("id1 = %d, id2 = %d\n", vtx->vtx_dest->next->ptr->id, vtx->vtx_dest->ptr->id);
	pos.pos3 = fake_vs.left_point;
	pos.pos4 = fake_vs.player;
	if ((ft_find_intersection(s, pos, 1)) == 0)
		fake_vs.begin = fake_vs.vtx_gauche->ptr->m_pos;
	else
		fake_vs.begin = s->tmp_intersect;
	pos.pos3 = fake_vs.right_point;
	if ((ft_find_intersection(s, pos, 1)) == 0)
		fake_vs.end = fake_vs.vtx_droite->ptr->m_pos;
	else
		fake_vs.end = s->tmp_intersect;
	// printf("fake_vs.end = %d\n", fake_vs.vtx_droite->ptr->id);
	ft_limit_ceiling_floor(s, pos.pos1, pos.pos2, &fake_vs, swich);
	if (!check_portal_doover(s, vtx))
		return ;
	if (!check_portal_validity(s, vtx, &fake_vs))
		return ;
	if (s->printf)
	{
		s->display_mode = editor;
		printf("sector %d", vs->sct_id);
		printf("     angle %.2f\n", vs->angle);
		update_image(s, s->sdl->editor);
		sleep(1);
	}
	ft_create_new_wall(s, vtx, vs, 'p');
	if (s->portal_nb < PORTAL_LIMIT)
		add_portal_to_list(s, fake_vs.player, fake_vs.sct, fake_vs);
}

int		ft_nb_walls(t_main *s)
{
	t_walls *tmp;
	int i;

	tmp = s->walls;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void		create_all_walls(t_main *s, t_int *vtx, t_visu *vs, int end)
{
	t_4dpos		pos;

	while (end && ft_nb_walls(s) < 600) //MERDE a enlever la securitê si possible
	{
		// printf("DEBUT BOUCLE\n");
		if (vtx->wall_value != -1)
		{
			// printf("portail entree(%d)   ", s->portal_nb);

			if (vtx->ptr->id == vs->begin_wall_id)
			{
				if (vtx->ptr->id == vs->end_wall_id)
					handle_visu_portal(s, vtx, vs, 4);
				else
					handle_visu_portal(s, vtx, vs, 1);
			}
			else if (vtx->ptr->id == vs->end_wall_id)
				handle_visu_portal(s, vtx, vs, 3);
			else
				handle_visu_portal(s, vtx, vs, 2);
				// printf("sortie(%d)\n", s->portal_nb);
		}
		else
		{
			// printf("wall\n");
			vs->begin = vtx->ptr->m_pos;
			vs->tmp_wall = vtx->next->ptr->m_pos;
			ft_create_new_wall(s, vtx, vs, 'w');
			pos.pos1 = vs->begin;
			pos.pos2 = vs->player;
			pos.pos3 = vs->left_plan;
			pos.pos4 = vs->right_plan;
			if (vtx->ptr->id == vs->end_wall_id)
				ft_find_intersection(s, pos, 1);
		}
		if ((vtx->ptr->id == vs->begin_wall_id && vs->begin_wall_id
			== vs->end_wall_id) || vtx->ptr->id == vs->end_wall_id)
			end = 0;
		vtx = vtx->next;
	}
	// printf("\n\n");
}
