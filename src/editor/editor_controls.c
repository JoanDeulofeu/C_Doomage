#include "doom.h"

void	click_editor_menu(t_main *s, t_anim menu, int x)
{
	int case_size;
	int ori_x;

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

int		check_click_menu(t_main *s)
{
	int x;
	int y;
	int ori_x;
	int dest_x;
	int case_size;

	x = s->ft_mouse.x;
	y = s->ft_mouse.y;
	case_size = s->editor->menu.image[0]->w / 6;
	ori_x = WIDTH / 2 - (s->editor->menu.image[s->editor->menu.current]->w / 2);
	dest_x = ori_x + s->editor->menu.image[s->editor->menu.current]->w;
	if (x >= ori_x && y >= 0 && x < dest_x + case_size && y < s->editor->menu.image[s->editor->menu.current]->h)
		return (1);
	else
		return (0);
}

int		key_controls_save(t_main *s, int key)
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

int		key_controls_game(t_main *s, int key)
{
	if (key == SDLK_ESCAPE)
		return (0);
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
	return (1);
}

int		key_controls_edi(t_main *s, int key)
{
	if (key == SDLK_ESCAPE)
		return (0);
	if (key == TAB)
		ft_test_chainlist(s);
	if ((key == SDLK_RETURN || key == SDLK_KP_ENTER) && s->display_mode < 2)
	{
		s->display_mode = s->display_mode == 1 ? 0 : 1;
	}
	if (key == SDLK_KP_PLUS)
	{
		s->editor->dply_floor = ft_prev_next_floor(s, 1);
	}
	if (key == SDLK_KP_MINUS)
	{
		s->editor->dply_floor = ft_prev_next_floor(s, 2);
	}
	if (key == SAVE)
	{
		s->display_mode = 2;
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
	if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER || key == PORTAL || key == SPRITE)
		change_mode(s, key);
	if (key == DELETE)
		return(2);
	return (1);
}


void	handle_editor_keys(t_main *s)
{
	const Uint8 *keys;

	s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos));
	keys = SDL_GetKeyboardState(NULL);
	if ((keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN] || keys[SPRINT]) && (s->player.sector_id != 0))
		ft_move_player(s, keys, 2);
	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
		rotate_player(s, keys);
	if (s->editor->mode == move && (keys[RIGHT_AR] || keys[LEFT_AR] || keys[UP_AR] || keys[DOWN_AR]))
		move_editor(s, keys);
	if (keys[LCTRL])
		crouch(s,1);
	else if (keys[SPACE])
	{
//		 jump(s,1);
	}
	else
	{
		crouch(s,-1);
		jump(s,-1);
	}

	// if (s->display_mode == editor)
	// {
	// 	if (s->editor->mode == vertex && (keys[DELETE]))
	// 		remove_selected_anchor(s);
	// 	if (s->editor->mode == sprite && (keys[DELETE]))
	// 		remove_sprite_by_select(s);
	// }

	ft_reset_color_screen(s->sdl->editor->content, WIDTH * HEIGHT);
	ft_reset_color_screen(s->sdl->game->content, WIDTH * HEIGHT);
	ft_reset_color_screen(s->sdl->save->content, WIDTH * HEIGHT);
	ft_draw_editor(s->editor, s->sdl->editor);
	display_map(s);
	ft_draw_all_wall(s);
	if (s->editor->mode_floor == 1)
	{
		s->editor->m_floor.current = 1;
		fill_sectors(s);
	}
	else
		s->editor->m_floor.current = 0;
	if (s->editor->mode == portal)// && get_pixel_color(s->sdl->editor, s->ft_mouse.x, s->ft_mouse.y) == COLOR_WALL)
		change_over_wall(s);
	draw_editor_menu(s, 0, WIDTH / 2 - (s->editor->menu.image[s->editor->menu.current]->w / 2), -1);
	draw_space_menu(s);

	// if (s->editor->mode == sprite)
	// 	draw_sprite_menu(s);

		//display_menu_sprite(s);
	//printf("mode = %d\n", s->editor->mode);
	if (s->player.sector_id == 0)
	{
		s->player.pos = handle_sector_zero(s, keys);
		set_player(s);
	}

	ft_visu_joan(s, keys);

	if (s->display_mode == 1)
	{
		play_anim(s);
		//	sprite_move(s);
		draw_sprite(s);
		draw_hud(s);
	}
	if (s->display_mode == 2)
	{
		ft_save_map(s);
	}

	if (s->display_mode == editor)
		update_image(s, s->sdl->editor);
	else if (s->display_mode == game)
		update_image(s, s->sdl->game);
	else if (s->display_mode == save)
		update_image(s, s->sdl->save);

	//	display_chainlist(s);

	// ft_test_chainlist(s);
	// printf("lol = %d\n", s->sector->vertex->->ptr->x);
	// printf("player.ori (%d, %d)\n",s->player.ori.x, s->player.ori.y);
	// printf("player.p_ori (%d, %d)\n",s->player.p_ori.x, s->player.p_ori.y);
	// printf("player.p_ref (%d, %d)\n",s->player.p_ref.x, s->player.p_ref.y);
	// printf("player.pos (%f, %f)\n",s->player.pos.x, s->player.pos.y);
	// printf("player.r_pos (%f, %f)\n\n\n",s->player.r_pos.x, s->player.r_pos.y);
}

void	editor_handler(t_main *s)
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
	t_mode			tmp_mode;


	// t_pos		dest;

	ingame = 1;
	selected = 0;
	zoom = 0;
	id = 0;
	remove_achr = 0;
	tmp_move.x = 0;
	tmp_move.y = 0;
	remove = 0;
	// SDL_SetRelativeMouseMode(SDL_TRUE);
	// draw_interface(s);
	while (ingame)
	{
		tmp_mode = s->editor->mode;
		v= s->vertex;

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
					get_pixel_color(s->sdl->editor, s->ft_mouse.x, s->ft_mouse.y) == BLACK_SCREEN)
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
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
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
						if (!id && s->editor->mode == vertex && (s->ft_mouse.x == mouse_save.x || s->ft_mouse.y == mouse_save.y) && remove == 0)
						{

							create_anchor(s, ori); //creation ancre

						}
						selected = 0;
						if (s->editor->selected == 0)
						{
							deselect_vertex(s);
						}
						if (s->editor->selected == 1)
						{
							select_vertex(s);
						}

						 	// printf("mouse (%d, %d)\n",s->ft_mouse.x, s->ft_mouse.y);
						 	// printf("mouse_save (%d, %d)\n",mouse_save.x, mouse_save.y);
					}
					else if (s->editor->mode == sprite)
					{
						if ((s->ft_mouse.x == mouse_save.x || s->ft_mouse.y == mouse_save.y) && remove == 0)
						{
							add_sprite(s,get_abs_r_pos(s,s->ft_mouse),s->choice_sprite->id);

							//add_sprite(s,get_abs_r_pos(s,s->ft_mouse),1);
							//deselect_sprite(s);
							s->editor->selected = 0;
						}
						if (s->editor->selected == 0)
						{
							deselect_sprite(s);
						}
						if (s->editor->selected == 1)
						{
							select_sprite(s);

						}
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
						if (s->editor->mode == sprite && !check_click_menu(s) && (check_sprite_menu_click(s,s->ft_mouse) == -1))
						{
						//	check_sprite_menu_click(s,s->ft_mouse);
							deselect_sprite(s);
							selected = set_selected_sprite(s,&mouse_save);
							//add_sprite(s,get_abs_r_pos(s,s->ft_mouse),1);
						}
						if (check_click_menu(s))
						{
							click_editor_menu(s, s->editor->menu, s->ft_mouse.x);
							// printf("mode = %u\n", s->editor->mode);
						}
						if (s->editor->mode == portal && !check_click_menu(s))
						{
							edit_portal(s);
						}
						if (s->editor->mode == vertex && !check_click_menu(s))
						{
							//deselect_vertex(s);
							selected = exist_vertex(s,&mouse_save,&id,&ori);
						}
						else if (s->editor->mode == move && !check_click_menu(s))
						{
							tmp.x = s->editor->decal_x;
							tmp.y = s->editor->decal_y;
							mouse_save.x = s->sdl->event.button.x;
							mouse_save.y = s->sdl->event.button.y;
							selected = 1;

						}
						else if (s->editor->mode == sector && !check_click_menu(s))
						{
							ori.x = arround(s->editor->space, s->sdl->event.button.x - (s->editor->decal_x % s->editor->space));
							ori.y = arround(s->editor->space, s->sdl->event.button.y - (s->editor->decal_y % s->editor->space));
							if (ori.x >= 0 && ori.x <= WIDTH
								&& ori.y >= 0 && ori.y <= HEIGHT)
								{
									if ((id = anchor_exists(s, ori)) != 0)
										set_selected(s, ori, s->editor->color_sector);
								}
							s->editor->color_sector = ft_sector_mode(s, s->sdl->event.button.x, s->sdl->event.button.y);


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
						else if (s->editor->mode == player && !check_click_menu(s))
						{
							tmp2.x = s->sdl->event.button.x;
							tmp2.y = s->sdl->event.button.y;

							if (ft_is_in_sector(s, tmp2) != 0)
							{
								s->player.pos.y = tmp2.y;
								s->player.pos.x = tmp2.x;
								s->player.set = 1;
								s->player.correc = 0;

							}
						}
					}
					else if (s->display_mode == game)
					{
						shoot(s,1);
					}
					else if (s->display_mode == save)
					{
						ft_click_save(s);
					}
				}
			}
			if (s->sdl->event.type == SDL_MOUSEWHEEL)
			{
				if (s->sdl->event.wheel.y > 0 && zoom < 15 && !s->display_mode)
				{
					ft_zoom(s,s->ft_mouse, 5);
					zoom++;
				}
				else if (s->sdl->event.wheel.y < 0 && zoom > -3 && !s->display_mode)
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
					if ((remove_achr = key_controls_edi(s, s->sdl->event.key.keysym.sym)) == 0)
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
		handle_editor_keys(s);
		//printf("mode = %d,%d\n",tmp_mode,s->editor->mode);
		if (tmp_mode != s->editor->mode)
			deselect_vertex(s);
		// printf("decalx = %d\n", s->editor->decal_x );
		// ft_test_chainlist(s);
	}
}
