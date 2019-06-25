
#include "doom.h"

//Dessine la direction dans laquelle regarde le joueur
// draw_view()
// {
// 	//utiliser fonction dessiner_ligne de FDF ?
// }

//Dessine le carré representant le joueur en debug
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
	ft_parsing(s);
	get_grid_tab(s);
	display_map(s);
	editor_handler(s);
	// event_handler(s);
}
