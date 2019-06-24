#include "doom.h"

// int		keyboard_controls(t_main *s, int key)
// {
// 	if (key == SDLK_ESCAPE)
// 		return (0);
// 	// else if (key == SDLK_e)
// 	// 	open_door(s);
// 	// else if (key == SDLK_m && HEIGHT / SPACE <= s->height && WIDTH / SPACE
// 	// 	<= s->width)
// 	// {
// 	// 	s->active_map = !s->active_map;
// 	// 	draw_interface(s);
// 	// }
// 	return (1);
// }

void	handle_editor_keys(t_main *s)
{
	const Uint8 *keys;

	keys = SDL_GetKeyboardState(NULL);
	// if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
	// 	move_player(s, keys, keys[SPRINT]);
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
		// ft_draw_grid(s->sdl->editor);
		update_image(s, s->sdl->editor);
	// }
}

void	create_anchor(t_main *s, t_pos ori)
{
	//on dessine la carre la ou on a cliqué
	t_dpos		init;
	t_dpos		dest;
	short		size;
	t_vertex	*temp;

	size = 5;
	temp = s->vertex;
	init.x = ori.x - size;
	init.y = ori.y - size;
	dest.x = ori.x + size;
	dest.y = ori.y + size;
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y)
			return;
		temp = temp->next;

	}
	draw_rect(s->sdl->editor, init, dest, GREEN);
	ft_add_vertex(s, ori.x, ori.y);
	// temp = s->vertex;
	// while (temp)
	// {
	// 	printf("vertex.x = %d\n", temp->x);
	// 	temp = temp->next;
	//
	// }
}

void	editor_handler(t_main *s)
{
	int			editor;
	int			click;
	int rest;
	t_pos		ori;
	t_pos		dest;

	editor = 1;
	click = 0;

	// SDL_SetRelativeMouseMode(SDL_TRUE);
	// draw_interface(s);
	while (editor)
	{
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			// s->line.x2 = s->sdl->event.button.x;
			// s->line.y2 = s->sdl->event.button.y;
			// s->line.x2 = 20 * round(s->sdl->event.button.x / 20) + 10;
			// s->line.y2 = 20 * round(s->sdl->event.button.y / 20) + 10;
			if (s->sdl->event.type == SDL_QUIT)
				editor = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					if (click == 0)
					{
						ori.x = 20 * round(s->sdl->event.button.x / 20) + 10;
						ori.y = 20 * round(s->sdl->event.button.y / 20) + 10;
						//ajouer verif ancre
						create_anchor(s, ori);
						click = 1;
					}
					else
					{
						dest.x = 20 * round(s->sdl->event.button.x / 20) + 10;
						dest.y = 20 * round(s->sdl->event.button.y / 20) + 10;
						// s->line.x2 = 20 * round(s->sdl->event.button.x / 20) + 10;
						// s->line.y2 = 20 * round(s->sdl->event.button.y / 20) + 10;
						//ajouer verif ancre
						create_anchor(s, dest);
						// draw_wall(s, ori);
						click = 0;
					}
				}
			}


			if (s->sdl->event.type == SDL_KEYDOWN
				&& keyboard_controls(s, s->sdl->event.key.keysym.sym) == 0)
				editor = 0;
		}
		handle_editor_keys(s);
	}
}
