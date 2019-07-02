#include "doom.h"

int		keyboard_controls_edi(t_main *s, int key)
{
	(void)s;
	if (key == SDLK_ESCAPE)
		return (0);
	if (key == SDLK_RIGHT)
		s->editor->decal_x += 5;
	if (key == SDLK_LEFT)
		s->editor->decal_x -= 5;
	if (key == SDLK_UP)
		s->editor->decal_y -= 5;
	if (key == SDLK_DOWN)
		s->editor->decal_y += 5;
	if (key == MOVE || key == VERTEX || key == WALL)
		change_mode(s, key);
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
		update_image(s, s->sdl->editor);
	// }
}

void	draw_anchor(t_main *s, t_pos ori, Uint32 color)
{
	t_dpos		init;
	t_dpos		dest;
	short		size;

	size = 5;
	init.x = ori.x - size;
	init.y = ori.y - size;
	dest.x = ori.x + size;
	dest.y = ori.y + size;
	// printf("%f\n", init.x);
	draw_rect(s->sdl->editor, init, dest, color);
}

void	create_anchor(t_main *s, t_pos ori)
{
	t_vertex	*temp;
	int			correc_x;
	int			correc_y;

	draw_anchor(s, ori, GREEN);
	temp = s->vertex;
	correc_x = 0;
	correc_y = 0;
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y)
		{
			draw_anchor(s, ori, BLUE);
			return;
		}
		temp = temp->next;
	}
	if (s->editor->decal_x % s->editor->space != 0 && s->editor->decal_x < 0)
		correc_x = -1;
	if (s->editor->decal_y % s->editor->space != 0 && s->editor->decal_y < 0)
		correc_y = -1;
	ori.x = s->editor->ref.x + (ori.x / s->editor->space) + correc_x;
	ori.y = s->editor->ref.y + (ori.y / s->editor->space) + correc_y;
	// printf("ori.x = %d, modulo = %d\n", ori.x, s->editor->decal_x % s->editor->space);


	ft_add_vertex(s, ori.x, ori.y);
}

void	display_map(t_main *s)
{
	t_vertex	*temp;
	t_editor	*edi;
	t_pos		pos;
	int			correc = 0;

	ft_draw_editor(s->editor, s->sdl->editor);
	edi = s->editor;
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

		// printf("Etat[%d]   (%d) * %d + (%d)\n", etat, temp->x - edi->ref.x + correc, edi->space, edi->decal_x % edi->space);
		// printf("vertex.x = %d, vertex.y = %d | ref.x = %d, ref.y = %d | pos.x = %d, pos.y = %d | decalX = %d | correc %d\n", temp->x, temp->y, edi->ref.x, edi->ref.y, pos.x, pos.y, edi->decal_x, correc);

		if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
			draw_anchor(s, pos, GREEN);
		temp = temp->next;
	}
}

void	editor_handler(t_main *s)
{
	int			zoom;
	int			editor;
	int			click;
	t_pos		ori;
	// t_pos		dest;

	editor = 1;
	click = 0;
	zoom = 0;
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
			}
			// s->line.x2 = s->sdl->event.button.x;
			// s->line.y2 = s->sdl->event.button.y;
			// s->line.x2 = 20 * round(s->sdl->event.button.x / 20) + 10;
			// s->line.y2 = 20 * round(s->sdl->event.button.y / 20) + 10;
			if (s->sdl->event.type == SDL_QUIT)
				editor = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN)
			{
				// printf("buttonx = %d\n", s->sdl->event.wheel.x);
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					// if (click == 0)
					// {
					//orig.x = position de la souris arrondie pour etre sur un point
						// ori.x = s->editor->space * round(s->sdl->event.button.x / (float)s->editor->space);
					ori.x = arround(s->editor->space, s->sdl->event.button.x - (s->editor->decal_x % s->editor->space));							// printf ("vrai ori.x = %d | arrondi = %f\n", ori.x, round((s->sdl->event.button.x - (s->editor->decal_x % s->editor->space)) / (float)s->editor->space ));
					ori.y = arround(s->editor->space, s->sdl->event.button.y - (s->editor->decal_y % s->editor->space));

					// printf("ori.x = %d ori .y = %d | souris = %d\n", ori.x, ori.y, s->sdl->event.button.x);
					//ajouer verif ancre
					if (ori.x >= 0 && ori.x <= WIDTH
						&& ori.y >= 0 && ori.y <= HEIGHT)
						{
							// printf("ori.x = %d | ori.y = %d\n", ori.x, ori.y);
							create_anchor(s, ori);
						}

					click = 1;
					// }
					// else
					// {
					// 	dest.x = s->editor->space * round(s->sdl->event.button.x / (float)s->editor->space);
					// 	dest.y = s->editor->space * round(s->sdl->event.button.y / (float)s->editor->space);
					// 	// s->line.x2 = 20 * round(s->sdl->event.button.x / 20) + 10;
					// 	// s->line.y2 = 20 * round(s->sdl->event.button.y / 20) + 10;
					// 	//ajouer verif ancre
					// 	create_anchor(s, dest);
					// 	// draw_wall(s, ori);
					// 	click = 0;
					// }
				}
			}
			if (s->sdl->event.type == SDL_MOUSEWHEEL)
			{
				// printf("Mouse moved to (%f,%f)\n",s->ft_mouse.x, s->ft_mouse.y);
				if (s->sdl->event.wheel.y > 0 && zoom < 15)
				{
					s->editor->space += 5;
					s->editor->decal_x = WIDTH/2 - s->ft_mouse.x;
					s->editor->decal_y = HEIGHT/2 -s->ft_mouse.y;
					//printf("decalx = %d", s->editor->decal_x);
					//s->sdl->event.button.x;
					zoom++;
				}
				else if (s->sdl->event.wheel.y < 0 && zoom > -3)
				{
					s->editor->space -= 5;
					s->editor->decal_x = WIDTH/2 - s->ft_mouse.x;
					s->editor->decal_y = HEIGHT/2 -s->ft_mouse.y;
					zoom--;
				}
				//printf("buttonx = %d", s->sdl->event.button.x);
				//printf("buttony = %d", s->sdl->event.button.y);
			}
			if (s->sdl->event.type == SDL_KEYDOWN
				&& keyboard_controls_edi(s, s->sdl->event.key.keysym.sym) == 0)
				editor = 0;

		}
		handle_editor_keys(s);
		// printf("decalx = %d\n", s->editor->decal_x );
		// ft_test_chainlist(s);
	}
}
