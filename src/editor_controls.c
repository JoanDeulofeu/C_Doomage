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

void	draw_anchor(t_main *s, t_pos ori)
{
	t_dpos		init;
	t_dpos		dest;
	short		size;

	size = 5;
	init.x = ori.x - size;
	init.y = ori.y - size;
	dest.x = ori.x + size;
	dest.y = ori.y + size;
	draw_rect(s->sdl->editor, init, dest, GREEN);
}

void	create_anchor(t_main *s, t_pos ori)
{
	t_vertex	*temp;

	if (ori.x < GRID_SIDE_MARGIN || ori.x > WIDTH - GRID_SIDE_MARGIN
		|| ori.y < GRID_TOP_MARGIN || ori.y > HEIGHT - GRID_SIDE_MARGIN)
		return;
	draw_anchor(s, ori);
	temp = s->vertex;
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y)
			return;
		temp = temp->next;

	}
	ft_add_vertex(s, ori.x, ori.y);
}

void	display_map(t_main *s)
{
	t_vertex	*temp;
	t_pos		pos;

	ft_draw_grid(s->sdl->editor);
	temp = s->vertex;
		while (temp)
	{
		// printf("vertex.x = %d, vertex.y = %d\n", temp->x, temp->y);
		pos.x = temp->x * G_SPACE + GRID_SIDE_MARGIN;
		pos.y = temp->y * G_SPACE + GRID_TOP_MARGIN;
		draw_anchor(s, pos);
		temp = temp->next;
	}
}

// void	get_grid_tab(t_main *s)
// {
// 	// if (!(s->grid = (t_point**)malloc(sizeof(t_point) * (WIDTH))))
// 	// 	return (NULL);
// }

void	editor_handler(t_main *s)
{
	int			editor;
	int			click;
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
