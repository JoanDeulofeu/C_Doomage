#include "doom.h"

void	display_error(int error_nb)
{
	if (error_nb == FILE_ERROR)
		ft_putstr("Error : The file cannot be opened\n");
	else if (error_nb == SIZE_ERROR)
		ft_putstr("Error : Map of incorrect size (Must be 3x3 to 50x50)\n");
	else if (error_nb == SYNTAX_ERROR)
		ft_putstr("Error : Syntax error\n");
	else if (error_nb == MALLOC_ERROR)
		ft_putstr("Error : Malloc error\n");
	else if (error_nb == PLAYER_ERROR)
		ft_putstr("Error : One player position needed.\n");
	else if (error_nb == WALL_ERROR)
		ft_putstr("Error : Map must be limited by walls !\n");
}

void	handle_error(t_main *s, int error_nb)
{
	(void)s;
	if (error_nb != 0)
		display_error(error_nb);
	Mix_HaltMusic();
	Mix_CloseAudio();
	SDL_Quit();
	free_program(s);
	exit(-1);
}

void	ft_error_sdl(char *str)
{
	ft_putstr(str);
	ft_putchar(' ');
	ft_putstr(SDL_GetError());
	exit(-1);
}
