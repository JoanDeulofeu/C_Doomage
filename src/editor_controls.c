#include "doom.h"

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
		// ft_draw_editor(s->sdl->editor);
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

	if (ori.x < GRID_SIDE_MARGIN || ori.x > WIDTH - GRID_SIDE_MARGIN
		|| ori.y < GRID_TOP_MARGIN || ori.y > HEIGHT - GRID_SIDE_MARGIN)
		return;
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
		pos.x = temp->x * G_SPACE + GRID_SIDE_MARGIN;
		pos.y = temp->y * G_SPACE + GRID_TOP_MARGIN;
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

	grid_width = (WIDTH - (GRID_SIDE_MARGIN * 2)) / G_SPACE;
	grid_height = (HEIGHT - (GRID_TOP_MARGIN + GRID_SIDE_MARGIN)) / G_SPACE;
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
		printf("\n", j);
		j = 0;
	}
}

void	fill_grid(t_main *s)
{
	int i;
	int j;
	int grid_width;
	int	grid_height;

	grid_width = (WIDTH - (GRID_SIDE_MARGIN * 2)) / G_SPACE;
	// printf("grid width = %d\n", grid_width);
	grid_height = (HEIGHT - (GRID_TOP_MARGIN + GRID_SIDE_MARGIN)) / G_SPACE;
	i = 0;
	j = 0;
	while (i <= grid_width)
	{
		while (j <= grid_height)
		{
			s->grid[i][j].x = i * G_SPACE + GRID_SIDE_MARGIN;
			s->grid[i][j].y = j * G_SPACE + GRID_TOP_MARGIN;
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
	grid_width = WIDTH - (GRID_SIDE_MARGIN * 2) / G_SPACE;
	grid_height = HEIGHT - (GRID_TOP_MARGIN + GRID_SIDE_MARGIN) / G_SPACE;
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
						ori.x = G_SPACE * round(s->sdl->event.button.x / G_SPACE) + GRID_SIDE_MARGIN;
						ori.y = G_SPACE * round(s->sdl->event.button.y / G_SPACE) + GRID_SIDE_MARGIN;
						//ajouer verif ancre
						create_anchor(s, ori);
						click = 1;
					}
					else
					{
						dest.x = G_SPACE * round(s->sdl->event.button.x / G_SPACE) + GRID_SIDE_MARGIN;
						dest.y = G_SPACE * round(s->sdl->event.button.y / G_SPACE) + GRID_SIDE_MARGIN;
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
		ft_test_chainlist(s);
	}
}
