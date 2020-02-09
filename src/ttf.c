/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:21:16 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/09 21:49:02 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

TTF_Font		*load_ttf(char *str, int size)
{
	int			i;
	TTF_Font	*font;

	i = 0;
	while (i++ < 100)
	{
		font = TTF_OpenFont(str, size);
		if (font)
			return (font);
	}
	return (NULL);
}

void			ft_all_ttf_to_null(t_main *s)
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

void			ft_init_font(t_main *s)
{
	ft_all_ttf_to_null(s);
	if (!(s->font->press_start = load_ttf("font/ps.ttf", 10)))
		handle_error(s, TTF_ERROR);
	if (!(s->font->press_start25 = load_ttf("font/ps.ttf", 25)))
		handle_error(s, TTF_ERROR);
	if (!(s->font->open = load_ttf("font/Open.ttf", 10)))
		handle_error(s, TTF_ERROR);
	if (!(s->font->roboto = load_ttf("font/Roboto.ttf", 20)))
		handle_error(s, TTF_ERROR);
	if (!(s->font->stylish = load_ttf("font/Styli.ttf", 10)))
		handle_error(s, TTF_ERROR);
	if (!(s->font->stylish100 = load_ttf("font/Styli.ttf", 100)))
		handle_error(s, TTF_ERROR);
	if (!(s->font->digit = load_ttf("font/digit.ttf", 20)))
		handle_error(s, TTF_ERROR);
	if (!(s->font->digit42 = load_ttf("font/digit.ttf", 42)))
		handle_error(s, TTF_ERROR);
}

void			ft_create_ttf(t_ttf ttf, t_main *s, TTF_Font *police)
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
