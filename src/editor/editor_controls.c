#include "doom.h"

void	ft_nul(t_main *s)
{
	t_dpos		init;
	t_dpos		dest;

	// init.x = 0;
	// init.y = 150;
	// dest.x = WIDTH;
	// dest.y = 151;
	// draw_rect(s->sdl->game, init, dest, 0x622b2bff);
	// init.x = 0;
	// init.y = 300;
	// dest.x = WIDTH;
	// dest.y = 301;
	// draw_rect(s->sdl->game, init, dest, 0x622b2bff);
	init.x = 0;
	init.y = HEIGHT / 2;
	dest.x = WIDTH;
	dest.y = HEIGHT / 2 + 2;
	draw_rect(s->sdl->game, init, dest, 0x622b2bff);
	// init.x = 0;
	// init.y = 600;
	// dest.x = WIDTH;
	// dest.y = 601;
	// draw_rect(s->sdl->game, init, dest, 0x622b2bff);


	//trait verticaux
	// init.x = 400;
	// init.y = 0;
	// dest.x = 402;
	// dest.y = HEIGHT;
	// draw_rect(s->sdl->game, init, dest, 0x622b2bff);
	// init.x = 450;
	// init.y = 0;
	// dest.x = 452;
	// dest.y = HEIGHT;
	// draw_rect(s->sdl->game, init, dest, 0xffff00ff);
	// init.x = 880;
	// init.y = 0;
	// dest.x = 882;
	// dest.y = HEIGHT;
	// draw_rect(s->sdl->game, init, dest, 0xffff00ff);
	// init.x = 930;
	// init.y = 0;
	// dest.x = 932;
	// dest.y = HEIGHT;
	// draw_rect(s->sdl->game, init, dest, 0xffff00ff);
}

void		click_editor_menu(t_main *s, t_anim menu, int x)
{
	int		case_size;
	int		ori_x;

	ori_x = WIDTH / 2 - (s->editor->menu.image[s->editor->menu.current]->w / 2);
	case_size = menu.image[0]->w / 6;
	if (s->display_mode)
		return ;
	if (x < ori_x + case_size)
		change_mode(s, MOVE);
	else if (x < ori_x + (case_size * 2) && x > ori_x + case_size)
		change_mode(s, VERTEX);
	else if (x < ori_x + (case_size * 3) && x > ori_x + (case_size * 2))
		change_mode(s, WALL);
	else if (x < ori_x + (case_size * 4) && x > ori_x + (case_size * 3))
		change_mode(s, PLAYER);
	else if (x < ori_x + (case_size * 5) && x > ori_x + (case_size * 4))
		change_mode(s, PORTAL);
	else if (x < ori_x + (case_size * 6) && x > ori_x + (case_size * 5))
		change_mode(s, SAVE);
	else if (x < ori_x + (case_size * 7) && x > ori_x + (case_size * 6)
		&& s->editor->mode_floor == 0)
		s->editor->mode_floor = 1;
	else if (x < ori_x + (case_size * 7) && x > ori_x + (case_size * 6)
		&& s->editor->mode_floor != 0)
		s->editor->mode_floor = 0;
}

int			check_click_menu(t_main *s)
{
	int		x;
	int		y;
	int		ori_x;
	int		dest_x;
	int		case_size;

	x = s->ft_mouse.x;
	y = s->ft_mouse.y;
	case_size = s->editor->menu.image[0]->w / 6;
	ori_x = WIDTH / 2 - (s->editor->menu.image[s->editor->menu.current]->w / 2);
	dest_x = ori_x + s->editor->menu.image[s->editor->menu.current]->w;
	if (x >= ori_x && y >= 0 && x < dest_x + case_size && y <
		s->editor->menu.image[s->editor->menu.current]->h)
		return (1);
	else
		return (0);
}

int			key_controls_save(t_main *s, int key)
{
	if (key == SDLK_ESCAPE)
	{
		s->display_mode = 0;
		change_mode(s, MOVE);
	}
	if ((key >= SDLK_a && key <= SDLK_z) || key == MINUS || key == 32)
	{
		ft_add_letter_to_savemap(s, key);
	}
	if (key == DEL)
	{
		ft_del_letter_to_savemap(s);
	}
	if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
	{
		if (s->savemap->str[2] == '\0')
			ft_save_msg(s, 1);
		else
			ft_write_file(s);
	}
	return (1);
}

void		ft_change_height(t_main *s, int key)
{
	t_sector *sct;

	sct = get_sector_by_id(s, s->player.sector_id);
	if (key == PAGE_DOWN && sct->floor > 0)
	{
		sct->floor--;
		ft_create_message(s, 0, 1000, "Floor down");
	}
	else if (key == END && sct->ceiling > 0 && sct->ceiling > sct->floor + 1)
	{
		sct->ceiling--;
		ft_create_message(s, 0, 1000, "Ceiling down");
	}
	else if (key == PAGE_UP && sct->floor < 10 && sct->ceiling > sct->floor + 1)
	{
		sct->floor++;
		ft_create_message(s, 0, 1000, "Floor up");
	}
	else if (key == HOME && sct->ceiling < 10)
	{
		sct->ceiling++;
		ft_create_message(s, 0, 1000, "Ceiling up");
	}
}

int			key_controls_game(t_main *s, int key)
{
	if (key == SDLK_ESCAPE)
		return (0);
	if ((!s->player.fly) && (key == HOME || key == END || key == PAGE_UP || key == PAGE_DOWN))
		ft_change_height(s, key);
	if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
	{
		s->display_mode = s->display_mode == 1 ? 0 : 1;
	}
	if (key == ROTATE_LEFT)
	{
		s->player.angle += 20;
		if (s->player.angle > 360)
			s->player.angle -= 360;
	}
	if (key == ROTATE_RIGHT)
	{
		s->player.angle -= 20;
		if (s->player.angle < 0)
			s->player.angle += 360;
	}
	if (key == TAB)
		ft_test_chainlist(s);
	if (key == SDLK_KP_PLUS)
		// ft_create_message(s, 2, 4000, "Vive le chocolat !");
		tp_first_sector(s);
		// s->player.y_eye = 0;
		// ft_print_sprite_list(s);
	return (1);
}

int			key_controls_edi(t_main *s, int key, int selected)
{
	(void)selected; //MERDE
	if (key == SDLK_ESCAPE)
		return (0);
	if (key == TAB)
		ft_test_chainlist(s);
	if ((key == SDLK_RETURN || key == SDLK_KP_ENTER) && s->display_mode < 2)
	{
		s->display_mode = s->display_mode == 1 ? 0 : 1;
	}
	if (s->editor->mode_floor == 1)
	{
		if (key == SDLK_KP_PLUS)
		{
			s->editor->dply_floor = ft_prev_next_floor(s, 1);
		}
		if (key == SDLK_KP_MINUS)
		{
			s->editor->dply_floor = ft_prev_next_floor(s, 2);
		}
	}
	if (key == SAVE)
	{
		s->display_mode = save;
	}
	if (key == ROTATE_LEFT)
	{
		s->player.angle += 20;
		if (s->player.angle > 360)
			s->player.angle -= 360;
	}
	if (key == ROTATE_RIGHT)
	{
		s->player.angle -= 20;
		if (s->player.angle < 0)
			s->player.angle += 360;
	}
	if (key == FLOOR)
	{
		if (s->editor->mode_floor == 1)
			s->editor->mode_floor = 0;
		else
			s->editor->mode_floor = 1;
		// s->editor->mode_floor = 1;
		// ft_reset_color_vertex(s);
	}
	if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER ||
		key == PORTAL || key == SPRITE)
		change_mode(s, key);
	if (s->display_mode == editor)
	{
		if (s->editor->mode == vertex && (key == DELETE))
			remove_selected_anchor(s);
		if (s->editor->mode == sprite && (key == DELETE))
		{
			remove_selected_sprite(s);
			// ft_print_sprite_list(s);
		}

	}
	if (key == DELETE)
		return(2);
	return (1);
}

void		handle_editor_keys(t_main *s)
{
	const Uint8	*keys;

	s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos));
	keys = SDL_GetKeyboardState(NULL);
	if ((keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN] || keys[SPRINT])
		&& (s->player.sector_id != 0))
		ft_move_player(s, keys, PLAYER_SPEED);
	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
		rotate_player(s, keys);
	if (s->editor->mode == move && (keys[RIGHT_AR] || keys[LEFT_AR] ||
		keys[UP_AR] || keys[DOWN_AR]))
		move_editor(s, keys);

	if (s->player.jump_height == 0 && !s->player.fly)
		ft_crouch(s, keys);
	if (s->player.size == PLAYER_SIZE && !s->player.fly)
		ft_jump(s, keys);



	if (keys[SDL_SCANCODE_F5])
		ft_activ_fly(s);
	if (s->player.fly)
		ft_fly_mode(s, keys);
	// printf("-\n-\n-\n-\n-\n");

	if (s->display_mode == editor)
	{
		ft_reset_color_screen(s->sdl->editor->content, WIDTH * HEIGHT);
		ft_draw_editor(s->editor, s->sdl->editor);
		display_map(s);
		draw_sprites_ori(s);
		ft_draw_all_wall(s);
		if (s->editor->mode_floor == 1)
		{
			s->editor->m_floor.current = 1;
			fill_sectors(s);
		}
		else
			s->editor->m_floor.current = 0;
		if (s->editor->mode == portal)
			change_over_wall(s);
		draw_editor_menu(s, 0, WIDTH / 2
			- (s->editor->menu.image[s->editor->menu.current]->w / 2), -1);
		draw_space_menu(s);
		handle_sector_zero(s);
		unset_sprites(s);
		ft_visu_joan(s, keys);
		clear_wall_list(s);
		if (s->editor->select_sprite)
			display_sprite_menu(s);
		update_image(s, s->sdl->editor);
	}
	if (s->display_mode == game)
	{
		display_sky(s);
		display_map(s);

		handle_sector_zero(s);
		unset_sprites(s);
		ft_visu_joan(s, keys);

		display_sprites(s);
		clear_wall_list(s);
		// draw_hud(s);
		animate_weapon(s);
		update_image(s, s->sdl->game);
	}
	if (s->display_mode == save)
	{
		ft_reset_color_screen(s->sdl->save->content, WIDTH * HEIGHT);
		ft_save_map(s);
		update_image(s, s->sdl->save);
	}
	// printf("s->player.y_eye = %d\ns->player.eyesight = %d\n\n", s->player.y_eye, s->player.eyesight);
}

void		editor_handler(t_main *s)
{
	int			zoom;
	int 		remove;
	int			ingame;
	int			selected;
	t_pos		ori;
	int			id;
	t_pos		mouse_save;
	t_pos 		tmp;
	t_pos 		tmp2;
	t_pos		tmp_move;
	t_pos		diff;
	int			remove_achr;
	t_vertex    *v;
	t_mode		tmp_mode;

	ingame = 1;
	selected = 0;
	zoom = 0;
	id = 0;
	remove_achr = 0;
	tmp_move.x = 0;
	tmp_move.y = 0;
	remove = 0;
	s->play_or_editor = 1;
	// SDL_SetRelativeMouseMode(SDL_TRUE);
	// draw_interface(s);
	while (ingame)
	{
		tmp_mode = s->editor->mode;
		v = s->vertex;
		s->time->time_ms = SDL_GetTicks();
		ft_fps(s);
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			if (s->sdl->event.type == SDL_MOUSEMOTION)
			{
				if (s->editor->mode == vertex || s->editor->mode == sprite)
				{
					s->editor->line.x2 = s->sdl->event.motion.x;
					s->editor->line.y2 = s->sdl->event.motion.y;
				}
				s->ft_mouse.x = s->sdl->event.motion.x;
				s->ft_mouse.y = s->sdl->event.motion.y;
				if (selected && s->editor->mode == vertex && !s->display_mode)
				{
					move_anchor(s, id);
					move_vertex(s, tmp_move, ori, id);
				}
				if(s->display_mode == 1)
				{
					SDL_SetRelativeMouseMode(SDL_TRUE);
					rotate_mouse(s);
					s->editor->mode = move;
				}
				else
					SDL_SetRelativeMouseMode(SDL_FALSE);
				if (s->editor->mode == portal &&
					get_pixel_color(s->sdl->editor, s->ft_mouse.x,
						s->ft_mouse.y) == BLACK_SCREEN)
				{
					s->editor->over_portal = 0;
					s->editor->over_sector2 = 0;
					if (s->editor->portal_temp == 1)
					{
						if (s->editor->wall2)
							s->editor->wall2->selected = 0;
						s->editor->wall2 = NULL;
					}
					else if (s->editor->portal_temp == 0)
					{
						if (s->editor->wall && !s->editor->wall2)
						{
							s->editor->wall->selected = 0;
							s->editor->wall = NULL;
						}
						else
							s->editor->over_sector = 0;
					}
				}
				if (s->editor->mode == move && selected == 1)
				{
					s->player.pos.x -= s->editor->decal_x;
					s->player.pos.y -= s->editor->decal_y;
					s->editor->decal_x = tmp.x + s->ft_mouse.x - mouse_save.x;
					s->editor->decal_y = tmp.y + s->ft_mouse.y - mouse_save.y;
					s->player.pos.x += s->editor->decal_x;
					s->player.pos.y += s->editor->decal_y;
				}
			}
			if (s->sdl->event.type == SDL_QUIT)
				ingame = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONUP)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT && s->display_mode == editor)
				{
					if (s->editor->mode == move && selected == 1)
					{
						s->editor->decal_x = tmp.x;
						s->editor->decal_y = tmp.y;
						diff.x = s->ft_mouse.x - mouse_save.x;
						diff.y = s->ft_mouse.y - mouse_save.y;
						mouse_grid(s, diff);
						selected = 0;
					}
					if (s->editor->mode == vertex)
					{
						//printf("mouse (%d, %d)\n",s->ft_mouse.x, s->ft_mouse.y);
						//printf("mouse_save (%d, %d)\n",mouse_save.x, mouse_save.y);
						if (!id && s->editor->mode == vertex
							&& (s->ft_mouse.x == mouse_save.x || s->ft_mouse.y
								== mouse_save.y) && remove == 0)
						{
							create_anchor(s, ori); //creation ancre
						}
						selected = 0;
						if (s->editor->selected == 0)
						{
							deselect_vertex(s);
							ft_check_move_vertex_validity(s, id);
						}
						if (s->editor->selected == 1)
						{
							select_vertex(s);
						}
					}
					else if (s->editor->mode == sprite && !s->editor->select_sprite)
					{

						// s->editor->selected = 0;
						if (!is_sprite_selected(s) && !is_sprite_under_mouse(s) && selected == 0)
						{
							create_new_sprite(s, none, get_abs_r_pos(s, s->ft_mouse));
							// deselect_sprite(s);
						}
						else if (is_sprite_selected(s))
						{
							// printf("deselect sprite\n");
							deselect_sprite(s);
							selected = 0;
						}
						// if (s->editor->selected == 1)
						// {
						// 	if (!is_sprite_selected(s))
						// 		{
						// 			select_sprite(s);
						// 			selected = 1;
						// 		}
						// }
					}
					else if (s->editor->mode == move)
					{
						selected = 0;
					}
					remove = 0;
				}
				else if(s->sdl->event.button.button == SDL_BUTTON_RIGHT)
				{
					if (s->editor->mode == portal)
						remove_portal(s);
				}
			}
			if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					if (s->display_mode == editor)
					{
						if (check_click_menu(s))
						{
							click_editor_menu(s, s->editor->menu, s->ft_mouse.x);
							// printf("mode = %u\n", s->editor->mode);
						}
						else if (s->editor->mode == sprite)
						{
							if (!is_sprite_selected(s) && !s->editor->select_sprite)
								selected = select_sprite(s);
							else if (!is_sprite_selected(s) && s->editor->select_sprite)
								select_sprite_type(s);
						}
						else if (s->editor->mode == portal)
						{
							edit_portal(s);
						}
						else if (s->editor->mode == vertex)
						{
							//deselect_vertex(s);
							selected = exist_vertex(s, &mouse_save, &id, &ori);
							s->save_coord_vtx.x = ori.x;
							s->save_coord_vtx.y = ori.y;
						}
						else if (s->editor->mode == move)
						{
							tmp.x = s->editor->decal_x;
							tmp.y = s->editor->decal_y;
							mouse_save.x = s->sdl->event.button.x;
							mouse_save.y = s->sdl->event.button.y;
							selected = 1;
						}
						else if (s->editor->mode == sector)
						{
							ori.x = arround(s->editor->space,
								s->sdl->event.button.x -
								(s->editor->decal_x % s->editor->space));
							ori.y = arround(s->editor->space,
								s->sdl->event.button.y -
								(s->editor->decal_y % s->editor->space));
							if (ori.x >= 0 && ori.x <= WIDTH
								&& ori.y >= 0 && ori.y <= HEIGHT)
							{
								if ((id = anchor_exists(s, ori)) != 0)
									set_selected(s, ori, s->editor->color_sector);
							}
							s->editor->color_sector = ft_sector_mode(s,
								s->sdl->event.button.x, s->sdl->event.button.y);
							t_pos point_2;
							int iii = -1;
							point_2.x = s->sdl->event.button.x;
							point_2.y = s->sdl->event.button.y;
							iii = ft_is_in_sector(s, point_2);
							if (iii == 0)
								printf("SECTOR IS %d\n", iii);
							else
								printf("\033[31mSECTOR IS %d\033[0m\n", iii);
							// printf("\n\n\n\n\n\n\n\n-------------------------------------\n\n\n");
						}
						else if (s->editor->mode == player)
						{
							tmp2.x = s->sdl->event.button.x;
							tmp2.y = s->sdl->event.button.y;
							if (ft_is_in_sector(s, tmp2) != 0)
							{
								s->player.r_pos= get_abs_r_pos(s,tmp2);
								s->player.set = 1;
								s->player.correc = 0;
							}
						}
					}
					else if (s->display_mode == game)
					{
						shoot(s);
					}
					else if (s->display_mode == save)
					{
						ft_click_save(s);
					}
				}
				else if (s->sdl->event.button.button == SDL_BUTTON_RIGHT)
				{
					if (s->editor->mode == sprite && !s->editor->select_sprite)
						s->editor->select_sprite = 1;
					else if (s->editor->mode == sprite
						&& s->editor->select_sprite)
						s->editor->select_sprite = 0;
				}

			}
			if (s->sdl->event.type == SDL_MOUSEWHEEL)
			{
				if (s->sdl->event.wheel.y > 0 && zoom < 15 && !s->display_mode)
				{
					ft_zoom(s,s->ft_mouse, 5);
					zoom++;
				}
				else if (s->sdl->event.wheel.y < 0 && zoom > -3 &&
					!s->display_mode)
				{
					ft_zoom(s,s->ft_mouse, -5);
					zoom--;
				}
			}
			if (s->sdl->event.type == SDL_KEYDOWN)
			{
				// printf("key = %d\n", s->sdl->event.key.keysym.sym);
				if (s->display_mode == editor)
				{
					if ((remove_achr = key_controls_edi(s,
						s->sdl->event.key.keysym.sym, selected)) == 0)
						ingame = 0;
					else if (remove_achr == 2 && selected == 1)
						{
							remove_anchor(s, id);
							remove = 1;
							id = 0;
						}
				}
				else if (s->display_mode == game)
				{
					if (key_controls_game(s, s->sdl->event.key.keysym.sym) == 0)
						ingame = 0;
				}
				else if (s->display_mode == save)
				{
					key_controls_save(s, s->sdl->event.key.keysym.sym);
				}
			}
		}
		if (s->display_mode == editor && s->editor->mode == sprite)
			move_sprite(s);
		handle_editor_keys(s);
		if (tmp_mode != s->editor->mode)
			deselect_vertex(s);
		s->wall_fk_id = 0;
		printf("\n\n\n");
		// ft_test_chainlist(s);
	}
}
