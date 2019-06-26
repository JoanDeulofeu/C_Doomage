#include "doom.h"

int		keyboard_controls(t_main *s, int key)
{
	(void)s;
	if (key == SDLK_ESCAPE)
		return (0);
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

void	handle_keys(t_main *s)
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
		ft_draw_editor(s->editor, s->sdl->editor);
		update_image(s, s->sdl->editor);
	// }
}

void	event_handler(t_main *s)
{
	int			game;

	game = 1;
	// SDL_SetRelativeMouseMode(SDL_TRUE);
	// draw_interface(s);
	while (game)
	{
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			if (s->sdl->event.type == SDL_QUIT)
				game = 0;
			// if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN
			// 	&& s->weapon.current == 0)
			// 	shoot(s);
			if (s->sdl->event.type == SDL_KEYDOWN
				&& keyboard_controls(s, s->sdl->event.key.keysym.sym) == 0)
				game = 0;
		}
		handle_keys(s);
	}
}
