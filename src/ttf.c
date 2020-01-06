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
	while ((s->font->digit = TTF_OpenFont("sdl_font/digit.ttf", 20)) == NULL)
		;
	while ((s->font->digit42 = TTF_OpenFont("sdl_font/digit.ttf", 42)) == NULL)
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
}

void	ft_draw_ttf_play(t_main *s)
{
	t_ttf		ttf;
	char*		str;

	ft_display_message(s);

	ttf.r = 210;
	ttf.g = 0;
	ttf.b = 0;
	ttf.pos.x = 57;
	ttf.pos.y = 730;
	str = ft_itoa(s->player.health);
	ttf.str = ft_strdup(str);
	ft_create_ttf(ttf, s, s->font->digit42);
	ft_memdel((void **)&str);

	ttf.pos.x = 163;
	str = ft_itoa(s->player.armor);
	ttf.str = ft_strdup(str);
	ft_create_ttf(ttf, s, s->font->digit42);
	ft_memdel((void **)&str);

	ttf.pos.x = 630;
	if (s->player.wp_name == kick)
	{
		ttf.str = ft_strdup("inf");
	}
	else if (s->player.wp_name == gun && s->player.wp_wheel[gun] == 1)
	{
		str = ft_itoa(s->player.mun_gun);
		ttf.str = ft_strdup(str);
	}
	else if (s->player.wp_name == shotgun && s->player.wp_wheel[shotgun] == 1)
	{
		str = ft_itoa(s->player.mun_shotgun);
		ttf.str = ft_strdup(str);
	}
	ft_create_ttf(ttf, s, s->font->digit42);
	ft_memdel((void **)&str);

	ttf.pos.x = 896;
	str = ft_itoa(s->player.keys);
	ttf.str = ft_strdup(str);
	ft_create_ttf(ttf, s, s->font->digit42);
	ft_memdel((void **)&str);

	ttf.pos.x = 732;
	if (s->player.jetpack)
	{
		ttf.str = get_jetpack_value(s);
		ttf.r = 0;
		ttf.b = 0;
		ttf.g = 250;
		ft_create_ttf(ttf, s, s->font->digit);
	}
	else
	{
		ttf.str = ft_strdup("Empty");
		ft_create_ttf(ttf, s, s->font->digit42);
	}
	ft_memdel((void **)&str);



	ttf.r = 0;
	ttf.g = 140;
	ttf.b = 0;
	if (s->player.wp_name == kick)
		ttf.g = 250;
	ttf.pos.x = 290;
	ttf.pos.y = 715;
	ttf.str = ft_strdup("Weapon 1 : Kick");
	ft_create_ttf(ttf, s, s->font->digit);

	if (s->player.wp_wheel[gun] == 1)
	{
		ttf.g = 140;
		if (s->player.wp_name == gun)
			ttf.g = 255;
		ttf.pos.y = 737;
		ttf.str = ft_strdup("Weapon 2 : Gun");
		ft_create_ttf(ttf, s, s->font->digit);
	}
	if (s->player.wp_wheel[shotgun] == 1)
	{
		ttf.g = 140;
		if (s->player.wp_name == shotgun)
			ttf.g = 250;
		ttf.pos.y = 759;
		ttf.str = ft_strdup("Weapon 3 : Shotgun");
		ft_create_ttf(ttf, s, s->font->digit);
	}
}

void	ft_draw_ttf_editor(t_main *s)
{
	t_ttf		ttf;
	char*		str;

	ft_display_message(s);
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

		//---------- ft_nul
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 10;
		// ttf.pos.y = 150;
		// ttf.str = ft_strdup("150");
		// ft_create_ttf(ttf, s, s->font->roboto);
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 10;
		// ttf.pos.y = 300;
		// ttf.str = ft_strdup("300");
		// ft_create_ttf(ttf, s, s->font->roboto);
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 10;
		// ttf.pos.y = 450;
		// ttf.str = ft_strdup("450");
		// ft_create_ttf(ttf, s, s->font->roboto);
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 10;
		// ttf.pos.y = 600;
		// ttf.str = ft_strdup("600");
		// ft_create_ttf(ttf, s, s->font->roboto);
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 200;
		// ttf.pos.y = 10;
		// ttf.str = ft_strdup("200");
		// ft_create_ttf(ttf, s, s->font->roboto);
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 400;
		// ttf.pos.y = 10;
		// ttf.str = ft_strdup("400");
		// ft_create_ttf(ttf, s, s->font->roboto);
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 600;
		// ttf.pos.y = 10;
		// ttf.str = ft_strdup("600");
		// ft_create_ttf(ttf, s, s->font->roboto);
		// ttf.r = 255;
		// ttf.g = 255;
		// ttf.b = 255;
		// ttf.pos.x = 800;
		// ttf.pos.y = 10;
		// ttf.str = ft_strdup("800");
		// ft_create_ttf(ttf, s, s->font->roboto);

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
