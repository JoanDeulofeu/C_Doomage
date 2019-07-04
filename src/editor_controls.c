#include "doom.h"

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
		s->editor->decal_x -= 5;
		s->player.pos.x -= 5;
	}
	if (key == SDLK_UP)
	{
		s->editor->decal_y -= 5;
		s->player.pos.y -= 5;
	}
	if (key == SDLK_DOWN)
	{
		s->editor->decal_y += 5;
		s->player.pos.y += 5;
	}
	if (key == MOVE || key == VERTEX || key == WALL || key == PLAYER
		|| key == SUPP)
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
		update_image(s, s->sdl->editor);
		// printf("MDR\n");
	// }
}

void set_player(t_main *s)
{
	t_pos		pos;
	t_editor 	*edi;
	int 		correc;

	correc = 0;
	edi = s->editor;
	//if (edi->decal_x <= 0)
//		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
//	else
	//	correc = 0;
	pos.x = (s->player.ori.x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);// + s->player.p_ori.x;
//	if (edi->decal_y <= 0)
//		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
//	else
	//	correc = 0;
	pos.y = (s->player.ori.y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);//+ s->player.p_ori.x;
	pos.x += s->player.p_ori.x;
	pos.y += s->player.p_ori.y;
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
			if (temp->selected == 1)
				draw_anchor(s, pos, BLUE);
			else
				draw_anchor(s, pos, GREEN);
		}
		temp = temp->next;
	}
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
					mouse_grid(s, mouse_save);
			}
			if (s->sdl->event.type == SDL_QUIT)
				editor = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONUP)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					if (s->editor->mode == vertex || s->editor->mode == supp)
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
					if (s->editor->mode == vertex || s->editor->mode == supp)
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
						mouse_save.x = s->ft_mouse.x;
						mouse_save.y = s->ft_mouse.y;

						selected = 1;
						// s->editor->decal_x = s->sdl->event.motion.x;
						// s->editor->decal_y = s->sdl->event.motion.y;
					}
					else if (s->editor->mode == sector)
					{
						ft_sector_mode(s, s->sdl->event.button.x, s->sdl->event.button.y);
					}
					else if (s->editor->mode == player)
					{
						s->player.pos.x = s->sdl->event.button.x;
						s->player.pos.y = s->sdl->event.button.y;
						s->player.ori.x = arround(s->editor->space, s->sdl->event.button.x - (s->editor->decal_x % s->editor->space));
						s->player.ori.y = arround(s->editor->space, s->sdl->event.button.y - (s->editor->decal_y % s->editor->space));
						s->player.p_ori.x = s->player.pos.x - s->player.ori.x;
						s->player.p_ori.y = s->player.pos.y - s->player.ori.y;
						s->player.ori = get_abs_pos(s,s->player.ori);
						//printf("player.pos.x = %d\n",s->player.pos.x);
						//printf("player.pos.y = %d\n",s->player.pos.y);
					//	printf("ori.x = %d\n",s->player.ori.x);
						//printf("ori.y = %d\n",s->player.ori.y);
						//printf("p_ori.x = %d\n",s->player.p_ori.x);
						//printf("p_ori.y = %d\n",s->player.p_ori.y);
					}
				}
			}
			if (s->sdl->event.type == SDL_MOUSEWHEEL)
			{
				if (s->sdl->event.wheel.y > 0 && zoom < 15)
				{
					s->editor->space += 5;
					zoom++;
				}
				else if (s->sdl->event.wheel.y < 0 && zoom > -3)
				{
					s->editor->space -= 5;
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
				&& selected == 1 && s->editor->mode == supp)
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
