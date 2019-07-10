#include "doom.h"

void	draw_player(t_main *s, t_dpos p_pos)
{
	t_dpos p_size;

	p_size.x = p_pos.x + 20;
	p_size.y = p_pos.y + 20;
	draw_rect(s->sdl->game, p_pos, p_size, s->sdl->game->color_tmp);
}

int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_main *s;

	s = initialize_main();
	s->p_pos.x = 500;
	s->p_pos.y = 330;
	draw_player(s, s->p_pos);
	SDL_ShowCursor(1);
	ft_parsing(s, 0, 0, 0);
	// get_grid_tab(s);
	display_map(s);
	editor_handler(s);
	Mix_HaltMusic();
	Mix_CloseAudio();
	SDL_Quit();
	free_program(s);
	// event_handler(s);
}
