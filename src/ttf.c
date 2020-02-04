#include "doom.h"

void	ft_all_ttf_to_null(t_main *s)
{
	s->font->press_start = NULL;
	s->font->press_start25 = NULL;
	s->font->open = NULL;
	s->font->roboto = NULL;
	s->font->stylish = NULL;
	s->font->stylish100 = NULL;
	s->font->digit = NULL;
	s->font->digit42 = NULL;
}

void	ft_init_font(t_main *s)
{
	ft_all_ttf_to_null(s);
	while ((s->font->press_start = TTF_OpenFont("font/ps.ttf", 10)) == NULL)
		;
	while ((s->font->press_start25 = TTF_OpenFont("font/ps.ttf", 25)) == NULL)
		;
	while ((s->font->open = TTF_OpenFont("font/Open.ttf", 10)) == NULL)
		;
	while ((s->font->roboto = TTF_OpenFont("font/Roboto.ttf", 20)) == NULL)
		;
	while ((s->font->stylish = TTF_OpenFont("font/Styli.ttf", 10)) == NULL)
		;
	while ((s->font->stylish100 = TTF_OpenFont("font/Styli.ttf", 100)) == NULL)
		;
	while ((s->font->digit = TTF_OpenFont("font/digit.ttf", 20)) == NULL)
		;
	while ((s->font->digit42 = TTF_OpenFont("font/digit.ttf", 42)) == NULL)
		;
}

void	ft_create_ttf(t_ttf ttf, t_main *s, TTF_Font *police)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = TTF_RenderText_Shaded(police, ttf.str,
		(SDL_Color){ttf.r, ttf.g, ttf.b, 255}, (SDL_Color){70, 70, 70, 0});
	SDL_SetColorKey(surface, SDL_TRUE, 0);
	texture = SDL_CreateTextureFromSurface(s->sdl->prenderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &ttf.pos.w, &ttf.pos.h);
	if (surface != NULL)
		SDL_FreeSurface(surface);
	SDL_RenderCopy(s->sdl->prenderer, texture, NULL, &ttf.pos);
	ft_memdel((void **)&ttf.str);
}
