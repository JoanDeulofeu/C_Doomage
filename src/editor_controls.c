#include "doom.h"

void set_player(t_main *s)
{
	t_pos		pos;
	t_editor 	*edi;
	int 		correc;
	t_dpos 		res;

	correc = 0;
	edi = s->editor;
	s->player.ori.x = arround(s->editor->space, s->player.pos.x - (s->editor->decal_x % s->editor->space));
	s->player.ori.y = arround(s->editor->space, s->player.pos.y - (s->editor->decal_y % s->editor->space));
	s->player.p_ori.x = s->player.pos.x - s->player.ori.x;
	s->player.p_ori.y = s->player.pos.y - s->player.ori.y;
	s->player.ori = get_abs_pos(s,s->player.ori);
	s->player.init_space = s->editor->space;
	s->player.p_ref = get_px_pos(s, s->editor->ref);
	if (s->editor->decal_x <= 0)
		s->player.correc = s->editor->decal_x % s->editor->space != 0 ? 1 : 0;
	else
		s->player.correc = 0;
	s->player.ori.x += s->player.correc;
	if (s->editor->decal_y <= 0)
		s->player.correc = s->editor->decal_y % s->editor->space != 0 ? 1 : 0;
	else
		s->player.correc = 0;
	s->player.ori.y += s->player.correc;

	if (edi->decal_x <= 0)
		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	//s->player.ori.x += correc;
	pos.x = (s->player.ori.x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
	if (edi->decal_y <= 0)
		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (s->player.ori.y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
	res.x = ((double)s->player.p_ori.x / (double)s->player.init_space) * edi->space;
	res.y = ((double)s->player.p_ori.y / (double)s->player.init_space) * edi->space;
	pos.x += (int)res.x - s->player.p_ref.x;
	pos.y += (int)res.y - s->player.p_ref.y;
	s->player.r_pos.x = (double)s->player.ori.x + ((double)s->player.p_ori.x / edi->space);
	s->player.r_pos.y = (double)s->player.ori.y + ((double)s->player.p_ori.y / edi->space);
	if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
		draw_anchor(s, pos, BLUE);
	// printf("r_pos.x = %f\n",s->player.r_pos.x);
	// printf("r_pos.y = %f\n",s->player.r_pos.y);
}

int		keyboard_controls_edi(t_main *s, int key)
{
	(void)s;
	if (key == SDLK_ESCAPE)
		return (0);
	if (key == SDLK_RIGHT)
	{
		s->editor->decal_x += 5;
		s->player.pos.x += 5;
	}
	if (key == SDLK_LEFT)
	{
		s->player.pos.x -= 5;
		s->editor->decal_x -= 5;
	}
	if (key == SDLK_UP)
	{
		s->player.pos.y -= 5;
		s->editor->decal_y -= 5;
	}
	if (key == SDLK_DOWN)
	{
		s->player.pos.y += 5;
		s->editor->decal_y += 5;
	}

	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		move_player(s,key);
		set_player(s);
	}
	//if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER)

	if (key == SDLK_KP_PLUS)
	{
		s->editor->dply_floor = ft_prev_next_floor(s, 1);
	}
	if (key == SDLK_KP_MINUS)
	{
		s->editor->dply_floor = ft_prev_next_floor(s, 2);
	}
	if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER || key == FLOOR)
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
	// if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
	// 	keyboard_controls_edi(s, keys);
	// if (keys[LEFT_AR] || keys[RIGHT_AR] || keys[UP_AR] || keys[DOWN_AR])
	// 	turn_camera(s, keys, 0);
	// if (s->sdl->event.type == SDL_MOUSEMOTION)
	// 	turn_camera(s, keys, 1);
	// if (s->active_map && HEIGHT / SPACE <= s->height && WIDTH / SPACE
	// 	<= s->width)
	// 	draw_minimap(s, 0, 0);
	// else
	// {
	// 	raycast_visualization(s);
		// draw_player(s, s->p_pos);
		// update_image(s, s->sdl->game);
		// ft_bzero(s->sdl->editor->content, WIDTH * HEIGHT * 4);
		ft_reset_color_screen(s->sdl->editor->content, WIDTH * HEIGHT);
		ft_draw_editor(s->editor, s->sdl->editor);
		display_map(s);
		ft_draw_all_wall(s);
		// printf("test .x = %d, test.y =%d\n", test.x, test.y);
		// draw_sector(s, test.x, test.y, YELLOW);
		fill_sectors(s);
		update_image(s, s->sdl->editor);
		// printf("MDR\n");
	// }
}

t_pos 	get_px_pos(t_main *s, t_pos ref)
{
	t_pos		pos;
	t_editor 	*edi;
	int 		correc;

	correc = 0;
	edi = s->editor;
	if (edi->decal_x <= 0)
		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.x = (ref.x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
	if (edi->decal_y <= 0)
		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (ref.y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
	return (pos);
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
	// t_pos 		tmp2;
	t_pos		diff;

	// t_pos		dest;

	editor = 1;
	selected = 0;
	zoom = 0;
	id = 0;
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
					if (s->editor->mode == vertex)
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
						printf("SECTOR IS %d\n", iii);
						// printf("\n\n\n\n\n\n\n\n-------------------------------------\n\n\n");
					}
					else if (s->editor->mode == player)
					{
						s->player.correc = 0;
						s->player.pos.x = s->sdl->event.button.x;
						s->player.pos.y = s->sdl->event.button.y;
					}
				}
			}
			if (s->sdl->event.type == SDL_MOUSEBUTTONUP)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					if (s->editor->mode == move)
					{
						s->editor->decal_x = tmp.x;
						s->editor->decal_y = tmp.y;
						diff.x = s->ft_mouse.x - mouse_save.x;
						diff.y = s->ft_mouse.y - mouse_save.y;
						mouse_grid(s, diff);
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
				&& keyboard_controls_edi(s, s->sdl->event.key.keysym.sym) == 0)
				editor = 0;
			else if (s->sdl->event.type == SDL_KEYDOWN
				&& keyboard_controls_edi(s, s->sdl->event.key.keysym.sym) == 2
				&& selected == 1)
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
