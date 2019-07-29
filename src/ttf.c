#include "doom.h"

TTF_Font	*ft_init_font(void)
{
	TTF_Font	*font;

	if ((font = TTF_OpenFont("sdl_font/press-start.ttf", 10)) != NULL)
		return (font);
	if ((font = TTF_OpenFont("sdl_font/Open.ttf", 10)) != NULL)
		return (font);
	if ((font = TTF_OpenFont("sdl_font/Roboto.ttf", 10)) != NULL)
		return (font);
	if ((font = TTF_OpenFont("sdl_font/Stylish.ttf", 10)) != NULL)
		return (font);
	ft_error_ttf("Erreur initialisation ft_init_font: ");
	return (font);
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
}

void	ft_draw_ttf(t_main *s)
{
	t_ttf		ttf;

	if (s->editor->mode_floor == 1)
	{
		ttf.r = 255;
		ttf.g = 255;
		ttf.b = 255;
		ttf.pos.x = 658;
		ttf.pos.y = 35;
		ttf.str = ft_strdup("1");
		ft_create_ttf(ttf, s, s->font);
	}
}
