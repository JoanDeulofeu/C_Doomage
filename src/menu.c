#include "doom.h"

void	display_menu(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;

	coord.x = 0;
	coord.y = 0;
	while (i < WIDTH)
	{
		j = 0;
		coord.x = i;
		perx = (double)coord.x / (double)WIDTH;
		while (j < HEIGHT)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)HEIGHT;
			px = (int)(pery * (double)s->menu.image[s->menu.current]->h) * s->menu.image[s->menu.current]->w + (int)
			(perx * (double)s->menu.image[s->menu.current]->w);
			if (px >= 0 && px < s->menu.image[s->menu.current]->w * s->menu.image[s->menu.current]->h)
				set_pixel(s->sdl->game, s->menu.image[s->menu.current]->tex[px], coord);
		}
		i++;
	}
	update_image(s, s->sdl->game);
}

void	select_game_mode(t_main *s, int key)
{
	if (key == SDLK_a)
	{
		if (s->menu.current == 0 || s->menu.current == 2)
			s->menu.current = 1;
		else if (s->menu.current == 1)
			s->menu.current = 2;
	}
	if (key == SDLK_d)
	{
		if (s->menu.current == 0 || s->menu.current == 1)
			s->menu.current = 2;
		else if (s->menu.current == 2)
			s->menu.current = 1;
	}
	Mix_PlayChannel(2, s->sdl->sounds.select, 0);
	if(s->sdl->sounds.select == NULL)
		printf("true\n");
	display_menu(s, 0, 0);
}

int		handle_menu(t_main *s)
{
	int key;
	play_music(s);
	s->play_or_editor = 2;
	display_menu(s, 0, 0);
	while (1)
	{
		SDL_WaitEvent(&s->sdl->event);
		if (s->sdl->event.type == SDL_QUIT)
			return (0);
		else if (s->sdl->event.type == SDL_KEYDOWN)
		{
			key = s->sdl->event.key.keysym.sym;
			if (key == SDLK_RETURN
				|| s->sdl->event.key.keysym.sym == SDLK_KP_ENTER)
				break ;
			else if(key == SDLK_a || key == SDLK_d)
			{
				select_game_mode(s, key);
			}
			else if (key == SDLK_ESCAPE)
				return (0);
		}
		else
			continue;
	}
	if (s->sdl->musique != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(s->sdl->musique);
		s->sdl->musique = NULL;
	}
	if (s->menu.current == 2 || s->menu.current == 0)
		launch_editor(s);
	else
		launch_game(s);
	return (1);
}
