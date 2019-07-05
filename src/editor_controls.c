#include "doom.h"

int		keyboard_controls_edi(t_main *s, int key)
{
	(void)s;
	if (key == SDLK_ESCAPE)
		return (0);
	if (key == SDLK_RIGHT)
	{
		s->editor->decal_x += 5;
	}
	if (key == SDLK_LEFT)
	{
		s->editor->decal_x -= 5;
	}
	if (key == SDLK_UP)
	{
		s->editor->decal_y -= 5;
	}
	if (key == SDLK_DOWN)
	{
		s->editor->decal_y += 5;
	}
	if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER)
		change_mode(s, key);
	if (key == DELETE)
		return(2);
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
	t_pos test;

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
		ft_bzero(s->sdl->editor->content, WIDTH * HEIGHT * 4);
		ft_draw_editor(s->editor, s->sdl->editor);
		display_map(s);
		ft_draw_all_wall(s);
		test.x = s->vertex->pos.x + 30;
		test.y = s->vertex->pos.y + 20;
		// printf("test .x = %d, test.y =%d\n", test.x, test.y);
		draw_sector(s, test.x, test.y);
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

void set_player(t_main *s)
{
	t_pos		pos;
	t_editor 	*edi;
	int 		correc;
	t_dpos 		res;

	correc = 0;
	edi = s->editor;

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
	//s->player.ori.y += correc;

	pos.y = (s->player.ori.y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
	res.x = ((double)s->player.p_ori.x / (double)s->player.init_space) * edi->space;
	res.y = ((double)s->player.p_ori.y / (double)s->player.init_space) * edi->space;
	//printf("decalx = %d\n", s->editor->decal_x );
	//printf("decaly = %d\n", s->editor->decal_y );

	pos.x += (int)res.x - s->player.p_ref.x;
	pos.y += (int)res.y - s->player.p_ref.y;
	if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
		draw_anchor(s, pos, BLUE);
}

void	display_map(t_main *s)
{
	t_vertex	*temp;
	t_editor	*edi;
	t_pos		pos;
	int			correc = 0;


	ft_draw_editor(s->editor, s->sdl->editor);
	temp = NULL;
	edi = s->editor;
	if (s->vertex)
		temp = s->vertex;
	while (temp)
	{
		if (edi->decal_x <= 0)
			correc = edi->decal_x % edi->space != 0 ? 1 : 0;
			// correc = 0;
		else
			correc = 0;
		if (edi->decal_x < 0)
			pos.x = (temp->x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
		else
			pos.x = (temp->x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
			// pos.x = (temp->x * edi->space - (edi->ref.x * edi->space + (edi->decal_x % edi->space)));
		// printf("correc = %d | pos.x = %d\n", correc, pos.x);

		if (edi->decal_y <= 0)
			correc = edi->decal_y % edi->space != 0 ? 1 : 0;
		else
			correc = 0;
		pos.y = (temp->y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
		temp->pos = pos;
		if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
		{
			if (temp->selected == 2)
				draw_anchor(s, pos, PINK);
			else if (temp->selected == 1)
				draw_anchor(s, pos, BLUE);
			else
				draw_anchor(s, pos, GREEN);
		}
		temp = temp->next;
	}
	// printf("decalx = %d\n", s->editor->decal_x );

	//player anchor
		//draw_anchor(s, s->player.pos, BLUE);
		set_player(s);
}

void	editor_handler(t_main *s)
{
	int			zoom;
	int			editor;
	int			selected;
	t_pos		ori;
	int			id;
	t_pos		mouse_save;
	char		color_sector;
	t_pos 		tmp;
	// t_pos 		tmp2;
	t_pos		diff;

	// t_pos		dest;

	editor = 1;
	selected = 0;
	zoom = 0;
	id = 0;
	color_sector = 2;
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
					// s->editor->decal_x = tmp2.x + s->ft_mouse.x - mouse_save.x;
					// s->editor->decal_y = tmp2.y + s->ft_mouse.y - mouse_save.y;
					s->editor->decal_x = tmp.x + s->ft_mouse.x - mouse_save.x;
					s->editor->decal_y = tmp.y + s->ft_mouse.y - mouse_save.y;
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
						// tmp2.x = s->editor->decal_x;
						// tmp2.y = s->editor->decal_y;
						tmp.x = s->editor->decal_x;
						tmp.y = s->editor->decal_y;
						mouse_save.x = s->sdl->event.button.x;
						mouse_save.y = s->sdl->event.button.y;
						//printf("mouse save X = %d et save Y = %d\n", mouse_save.x, mouse_save.y);
						//printf("decalx = %d\n", s->editor->decal_x );
						//printf("decaly = %d\n", s->editor->decal_y );
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
									set_selected(s, ori, color_sector);
							}

						color_sector = ft_sector_mode(s, s->sdl->event.button.x, s->sdl->event.button.y);
					}
					else if (s->editor->mode == player)
					{
						s->player.correc = 0;
						s->player.pos.x = s->sdl->event.button.x;
						s->player.pos.y = s->sdl->event.button.y;
						s->player.ori.x = arround(s->editor->space, s->sdl->event.button.x - (s->editor->decal_x % s->editor->space));
						s->player.ori.y = arround(s->editor->space, s->sdl->event.button.y - (s->editor->decal_y % s->editor->space));
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

						//printf("refx = %d\n", s->player.p_ref.x);
						//printf("refy = %d\n", s->player.p_ref.y);
						//printf("player.pos.x = %d\n",s->player.pos.x);
						//printf("player.pos.y = %d\n",s->player.pos.y);
						//printf("ori.x = %d\n",s->player.ori.x);
						//printf("ori.y = %d\n",s->player.ori.y);
						//printf("p_ori.x = %d\n",s->player.p_ori.x);
						//printf("p_ori.y = %d\n",s->player.p_ori.y);

						//printf("space = %d\n", s->editor->space );
						//printf("init_space = %d\n", s->player.init_space);
						//printf("decalx = %d\n", s->editor->decal_x );
						//printf("decaly = %d\n", s->editor->decal_y );

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
					//s->player.p_ori.x = s->player.ori.x + (s->player.p_ori.x + 5);
					//s->player.p_ori.y = s->player.ori.y + (s->player.p_ori.y + 5);
					//s->player.p_ori.y += s->player.ori.y * 5;
					zoom++;
				}
				else if (s->sdl->event.wheel.y < 0 && zoom > -3)
				{
					s->editor->space -= 5;
					//s->player.p_ori.x = s->player.ori.x + (s->player.p_ori.x - 5);
					//s->player.p_ori.y = s->player.ori.y + (s->player.p_ori.y - 5);
					//s->editor->space -= 5;

					zoom--;
				}
				//printf("buttonx = %d", s->sdl->event.button.x);
				//printf("buttony = %d", s->sdl->event.button.y);
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
