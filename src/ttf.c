#include "doom.h"

void	ft_all_ttf_to_null(t_main *s)
{
	s->font->press_start = NULL;
	s->font->press_start25 = NULL;
	s->font->open = NULL;
	s->font->roboto = NULL;
	s->font->stylish = NULL;
	s->font->stylish100 = NULL;
}

void	ft_init_font(t_main *s)
{
	ft_all_ttf_to_null(s);
	while ((s->font->press_start = TTF_OpenFont("sdl_font/press-start.ttf", 10)) == NULL)
		;
	while ((s->font->press_start25 = TTF_OpenFont("sdl_font/press-start.ttf", 25)) == NULL)
		;
	while ((s->font->open = TTF_OpenFont("sdl_font/Open.ttf", 10)) == NULL)
		;
	while ((s->font->roboto = TTF_OpenFont("sdl_font/Roboto.ttf", 20)) == NULL)
		;
	while ((s->font->stylish = TTF_OpenFont("sdl_font/Stylish.ttf", 10)) == NULL)
		;
	while ((s->font->stylish100 = TTF_OpenFont("sdl_font/Stylish.ttf", 100)) == NULL)
		;
	// ft_error_ttf("Erreur initialisation ft_init_font: ");
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

void	ft_draw_ttf_play(t_main *s)
{
	t_ttf		ttf;
	// char*		str;

	ft_display_message(s);
	ttf.r = 255;
	ttf.g = 255;
	ttf.b = 255;
	ttf.pos.x = 50;
	ttf.pos.y = 750;
	ttf.str = ft_strdup("100");
	ft_create_ttf(ttf, s, s->font->press_start);
}

void	ft_draw_ttf_editor(t_main *s)
{
	t_ttf		ttf;
	char*		str;

	ft_display_message(s);
	if (s->editor->mode_floor == 1 && s->display_mode == editor)
	{
		ttf.r = 255;
		ttf.g = 255;
		ttf.b = 255;
		ttf.pos.x = 658;
		ttf.pos.y = 35;
		ttf.str = ft_strdup("1");
		ft_create_ttf(ttf, s, s->font->press_start);
	}
	if (s->display_mode == game)
	{
		ttf.r = 255;
		ttf.g = 255;
		ttf.b = 255;
		ttf.pos.x = 920;
		ttf.pos.y = 4;
		ttf.str = ft_strdup("FPS");
		ft_create_ttf(ttf, s, s->font->roboto);
		str = ft_itoa(s->time->fps);
		ttf.r = 255;
		ttf.g = 255;
		ttf.b = 255;
		ttf.pos.x = 960;
		ttf.pos.y = 4;
		ttf.str = ft_strdup(str);
		ft_create_ttf(ttf, s, s->font->roboto);
		ft_memdel((void **)&str);
	}
	if (s->display_mode == save)
	{
		ttf.r = 255;
		ttf.g = 0;
		ttf.b = 0;
		ttf.pos.x = 200;
		ttf.pos.y = 200;
		ttf.str = ft_strdup("SAUVEGARDE");
		ft_create_ttf(ttf, s, s->font->stylish100);
		ttf.r = 255;
		ttf.g = 255;
		ttf.b = 255;
		ttf.pos.x = 240;
		ttf.pos.y = 400;
		ttf.str = ft_strdup("Veuillez entrer le nom de la map a sauvegarder :");
		ft_create_ttf(ttf, s, s->font->press_start);
		if (s->savemap->str[0] != '\0')
		{
			ttf.r = 255;
			ttf.g = 255;
			ttf.b = 255;
			ttf.pos.x = 240;
			ttf.pos.y = 465;
			ttf.str = ft_strdup(s->savemap->str);
			ft_create_ttf(ttf, s, s->font->press_start);
		}
		if (s->savemap->error_msg == 1)
		{
			ttf.r = 255;
			ttf.g = 0;
			ttf.b = 0;
			ttf.pos.x = 200;
			ttf.pos.y = 620;
			ttf.str = ft_strdup("ERROR : Le nom du fichier doit contenir au moins 3 caracteres.");
			ft_create_ttf(ttf, s, s->font->roboto);
		}
		else if (s->savemap->error_msg == 2)
		{
			ttf.r = 0;
			ttf.g = 255;
			ttf.b = 0;
			ttf.pos.x = 350;
			ttf.pos.y = 620;
			ttf.str = ft_strdup("Sauvegarde de la map reussi.");
			ft_create_ttf(ttf, s, s->font->roboto);
		}
	}
}
