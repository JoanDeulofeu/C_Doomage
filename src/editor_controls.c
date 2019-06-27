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
	draw_rect(s->sdl->editor, init, dest, color);
}

void	create_anchor(t_main *s, t_pos ori)
{
	t_vertex	*temp;

	// if (ori.x < GRID_SIDE_MARGIN || ori.x > WIDTH - GRID_SIDE_MARGIN
	// 	|| ori.y < GRID_TOP_MARGIN || ori.y > HEIGHT - GRID_SIDE_MARGIN)
	// 	return;
	draw_anchor(s, ori, GREEN);
	temp = s->vertex;
	while (temp)
	{
		if (temp->x == ori.x && temp->y == ori.y)
		{
			draw_anchor(s, ori, BLUE);
			return;
		}
		temp = temp->next;

	}
	ft_add_vertex(s, ori.x, ori.y);
}

void	display_map(t_main *s)
{
	t_vertex	*temp;
	t_pos		pos;

	ft_draw_editor(s->editor, s->sdl->editor);
	temp = s->vertex;
	while (temp)
	{
		// printf("vertex.x = %d, vertex.y = %d\n", temp->x, temp->y);
		if (s->editor->decal_x % s->editor->space < s->editor->space / 2)
			pos.x = (temp->x - s->editor->ref.x) * s->editor->space + (s->editor->decal_x % s->editor->space);
		else
			pos.x = (temp->x - s->editor->ref.x) * s->editor->space - (s->editor->decal_x % s->editor->space);
		if (s->editor->decal_y % s->editor->space < s->editor->space / 2)
			pos.y = (temp->y - s->editor->ref.y) * s->editor->space + (s->editor->decal_y % s->editor->space);
		else
			pos.y = (temp->y - s->editor->ref.y) * s->editor->space - (s->editor->decal_y % s->editor->space);

		if (!(pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT))
			draw_anchor(s, pos, GREEN);
		temp = temp->next;
	}
}

void	print_grid(t_main *s)
{
	int i;
	int j;
	int grid_width;
	int	grid_height;

	grid_width = (WIDTH - (GRID_SIDE_MARGIN * 2)) / s->editor->space;
	grid_height = (HEIGHT - (GRID_TOP_MARGIN + GRID_SIDE_MARGIN)) / s->editor->space;
	i = 0;
	j = 0;
	while (i < grid_width)
	{
		while (j < grid_height)
		{
			printf(" %d %d |",s->grid[i][j].x, s->grid[i][j].y);
			j++;
		}
		printf(" %d %d |",s->grid[i][j].x, s->grid[i][j].y);
		i++;
		// printf("\n", j);
		j = 0;
	}
}

void	fill_grid(t_main *s)
{
	int i;
	int j;
	int grid_width;
	int	grid_height;

	grid_width = (WIDTH - (GRID_SIDE_MARGIN * 2)) / s->editor->space;
	// printf("grid width = %d\n", grid_width);
	grid_height = (HEIGHT - (GRID_TOP_MARGIN + GRID_SIDE_MARGIN)) / s->editor->space;
	i = 0;
	j = 0;
	while (i <= grid_width)
	{
		while (j <= grid_height)
		{
			s->grid[i][j].x = i * s->editor->space + GRID_SIDE_MARGIN;
			s->grid[i][j].y = j * s->editor->space + GRID_TOP_MARGIN;
			s->grid[i][j].anchor = 0;
			s->grid[i][j].clicked = 0;
			j++;
		}
		i++;
		j = 0;
	}
}

void	initialize_grid(t_main *s)
{
	int grid_width;
	int	grid_height;
	int i;

	i = 0;
	grid_width = WIDTH - (GRID_SIDE_MARGIN * 2) / s->editor->space;
	grid_height = HEIGHT - (GRID_TOP_MARGIN + GRID_SIDE_MARGIN) / s->editor->space;
	if (!(s->grid = (t_point**)malloc(sizeof(t_point*)
		* grid_width)))
		handle_error(s, MALLOC_ERROR);
	while (i < grid_width)
		s->grid[i++] = NULL;
	i = 0;
	while (i < grid_width)
	{
		if (!(s->grid[i] = (t_point*)malloc(sizeof(t_point) * grid_height)))
			handle_error(s, MALLOC_ERROR);
		i++;
	}
}

// void	get_vertex_data(t_main *s)
// {
//
// }

void	get_grid_tab(t_main *s)
{
	initialize_grid(s);
	fill_grid(s);
	// print_grid(s);
	// get_vertex_data(s);
}

void	editor_handler(t_main *s)
{
	int			zoom;
	int			editor;
	int			click;
	t_pos		ori;
	t_pos		dest;

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
				printf("buttonx = %d\n", s->sdl->event.wheel.x);
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
					if (click == 0)
					{
						ori.x = s->editor->space * round(s->sdl->event.button.x / (float)s->editor->space);
						ori.y = s->editor->space * round(s->sdl->event.button.y / (float)s->editor->space);
						printf("ori.x = %d ori .y = %d | souris = %d\n", ori.x, ori.y, s->sdl->event.button.x);
						//ajouer verif ancre
						create_anchor(s, ori);
						click = 1;
					}
					else
					{
						dest.x = s->editor->space * round(s->sdl->event.button.x / (float)s->editor->space);
						dest.y = s->editor->space * round(s->sdl->event.button.y / (float)s->editor->space);
						// s->line.x2 = 20 * round(s->sdl->event.button.x / 20) + 10;
						// s->line.y2 = 20 * round(s->sdl->event.button.y / 20) + 10;
						//ajouer verif ancre
						create_anchor(s, dest);
						// draw_wall(s, ori);
						click = 0;
					}
				}
			}
			if (s->sdl->event.type == SDL_MOUSEWHEEL)
			{
				printf("Mouse moved to (%f,%f)\n",s->ft_mouse.x, s->ft_mouse.y);
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
