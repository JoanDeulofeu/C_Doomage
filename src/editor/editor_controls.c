#include "doom.h"

void	click_editor_menu(t_main *s, t_anim menu, int x)
{
	int case_size;
	int ori_x;

	ori_x = WIDTH / 2 - (s->editor->menu.image[s->editor->menu.current]->w / 2);
	case_size = menu.image[0]->w / 5;
	if (x < ori_x + case_size)
		change_mode(s, MOVE);
	else if (x < ori_x + (case_size * 2) && x > ori_x + case_size)
		change_mode(s, VERTEX);
	else if (x < ori_x + (case_size * 3) && x > ori_x + (case_size * 2))
		change_mode(s, WALL);
	else if (x < ori_x + (case_size * 4) && x > ori_x + (case_size * 3))
		change_mode(s, PLAYER);
	else if (x < ori_x + (case_size * 5) && x > ori_x + (case_size * 4))
		change_mode(s, SAVE);
	else if (x < ori_x + (case_size * 6) && x > ori_x + (case_size * 5)
		&& s->editor->mode_floor == 0)
		s->editor->mode_floor = 1;
	else if (x < ori_x + (case_size * 6) && x > ori_x + (case_size * 5)
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
	case_size = s->editor->menu.image[0]->w / 5;
	ori_x = WIDTH / 2 - (s->editor->menu.image[s->editor->menu.current]->w / 2);
	dest_x = ori_x + s->editor->menu.image[s->editor->menu.current]->w;
	if (x >= ori_x && y >= 0 && x < dest_x + case_size && y < s->editor->menu.image[s->editor->menu.current]->h)
		return (1);
	else
		return (0);
}

int		keyboard_controls_edi(t_main *s, int key)
{
	// (void)s;
	if (key == SDLK_ESCAPE)
		return (0);
	// if (key == SDLK_RIGHT)
	// {
	// 	s->editor->decal_x += 5;
	// 	s->player.pos.x += 5;
	// }
	// if (key == SDLK_LEFT)
	// {
	// 	s->player.pos.x -= 5;
	// 	s->editor->decal_x -= 5;
	// }
	// if (key == SDLK_UP)
	// {
	// 	s->player.pos.y -= 5;
	// 	s->editor->decal_y -= 5;
	// }
	// if (key == SDLK_DOWN)
	// {
	// 	s->player.pos.y += 5;
	// 	s->editor->decal_y += 5;
	// }

	/*if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		move_player(s,key);
		set_player(s);
	}*/
	//if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER)

	if (key == SDLK_KP_PLUS)
	{
		s->editor->dply_floor = ft_prev_next_floor(s, 1);
	}
	if (key == SDLK_KP_MINUS)
	{
		s->editor->dply_floor = ft_prev_next_floor(s, 2);
	}
	if (key == ROTATE_LEFT)
	{
		s->player.angle += 2;
		if (s->player.angle > 360)
			s->player.angle -= 360;
	}
	if (key == ROTATE_RIGHT)
	{
		s->player.angle -= 2;
		if (s->player.angle < 0)
			s->player.angle += 360;
	}
	// if (key == VISU)
	// {
	// 	ft_visu(s);
	// }
	if (key == FLOOR)
	{
		// printf("lol\n");
		if (s->editor->mode_floor == 1)
			s->editor->mode_floor = 0;
		else
			s->editor->mode_floor = 1;
		// s->editor->mode_floor = 1;
		// ft_reset_color_vertex(s);
	}
	if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER)
		change_mode(s, key);
	if (key == DELETE)
		return(2);
	//f (key == UP)
	// else if (key == SDLK_e)
	// 	open_door(s);
	// else if (key == SDLK_m && HEIGHT / SPACE <= s->height && WIDTH / SPACE
	// 	<= s->width)
	// {
	// 	s->active_map = !s->active_map;
	// 	draw_interface(s);
	// }
	return (1);
}

void	handle_editor_keys(t_main *s)
{
	const Uint8 *keys;

	keys = SDL_GetKeyboardState(NULL);
	if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
	{
		//ft_move_player(s, keys);
		ft_move_player(s, keys,1);
	}
	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
		rotate_player(s, keys);
	if (keys[RIGHT_AR] || keys[LEFT_AR] || keys[UP_AR] || keys[DOWN_AR])
		move_editor(s, keys);

	ft_reset_color_screen(s->sdl->editor->content, WIDTH * HEIGHT);
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
	draw_editor_menu(s, 0, WIDTH / 2 - (s->editor->menu.image[s->editor->menu.current]->w / 2), -1);
	draw_space_menu(s);
	ft_visu(s);
	update_image(s, s->sdl->editor);
	// printf("player.ori (%d, %d)\n",s->player.ori.x, s->player.ori.y);
	// printf("player.p_ori (%d, %d)\n",s->player.p_ori.x, s->player.p_ori.y);
	// printf("player.p_ref (%d, %d)\n",s->player.p_ref.x, s->player.p_ref.y);
	// printf("player.pos (%f, %f)\n",s->player.pos.x, s->player.pos.y);
	// printf("player.r_pos (%f, %f)\n",s->player.r_pos.x, s->player.r_pos.y);

}

void	editor_handler(t_main *s)
{
	int			zoom;
	int			editor;
	int			selected;
	t_pos		ori;
	int			id;
	t_pos		mouse_save;
	t_pos 		tmp;
	t_pos 		tmp2;
	t_pos		diff;
	int			yoan;

	// t_pos		dest;

	editor = 1;
	selected = 0;
	zoom = 0;
	id = 0;
	yoan = 0;
	// SDL_SetRelativeMouseMode(SDL_TRUE);
	// draw_interface(s);
	while (editor)
	{
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			if (s->sdl->event.type == SDL_MOUSEMOTION)
			{
				s->ft_mouse.x = s->sdl->event.motion.x;
				s->ft_mouse.y = s->sdl->event.motion.y;
				if (selected && s->editor->mode == vertex)
					move_anchor(s, id);
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
				editor = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONUP)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					if (s->editor->mode == vertex)
					{
						selected = 0;
						set_selected(s, ori, 0);
					}
					else if (s->editor->mode == move)
					{
						selected = 0;
					}
				}
			}
			if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					if (check_click_menu(s))
					{
						click_editor_menu(s, s->editor->menu, s->ft_mouse.x);
						// printf("mode = %u\n", s->editor->mode);
					}

					if (s->editor->mode == vertex && !check_click_menu(s))
					{
						ori.x = arround(s->editor->space, s->sdl->event.button.x - (s->editor->decal_x % s->editor->space));
						ori.y = arround(s->editor->space, s->sdl->event.button.y - (s->editor->decal_y % s->editor->space));
						if (ori.x >= 0 && ori.x <= WIDTH
							&& ori.y >= 0 && ori.y <= HEIGHT)
							{
								if ((id = anchor_exists(s, ori)) != 0)
								{
									selected = 1;
									set_selected(s, ori, 1);
								}
								else if (!id && s->editor->mode == vertex)
									create_anchor(s, ori);
							}
					}
					// else if (s->editor->mode == supp && selected == 1)
					// 	remove_anchor(s, id);
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
			}
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
				}
			}

			if (s->sdl->event.type == SDL_MOUSEWHEEL)
			{
				if (s->sdl->event.wheel.y > 0 && zoom < 15)
				{
					s->editor->space += 5;
					s->player.pos.x = ((double)s->player.pos.x / (double)s->player.init_space) * s->editor->space;
					s->player.pos.y = ((double)s->player.pos.y / (double)s->player.init_space) * s->editor->space;
					zoom++;
				}
				else if (s->sdl->event.wheel.y < 0 && zoom > -3)
				{
					s->editor->space -= 5;
					s->player.pos.x = ((double)s->player.pos.x / (double)s->player.init_space) * s->editor->space;
					s->player.pos.y = ((double)s->player.pos.y / (double)s->player.init_space) * s->editor->space;
					zoom--;

				}
			}
			if (s->sdl->event.type == SDL_KEYDOWN
				&& (yoan = keyboard_controls_edi(s, s->sdl->event.key.keysym.sym)) == 0)
				editor = 0;
			else if (s->sdl->event.type == SDL_KEYDOWN
				&& yoan == 2 && selected == 1)
				{
					remove_anchor(s, id);
					id = 0;
				}

		}
		handle_editor_keys(s);
		// printf("decalx = %d\n", s->editor->decal_x );
		// ft_test_chainlist(s);
	}
}
