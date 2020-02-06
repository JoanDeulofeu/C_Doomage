/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_initialize_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:26:46 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/06 14:40:38 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		initialize_sdl(t_main *s, t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		ft_error_sdl("Échec de l'initialisation de la SDL");
	if (TTF_Init() == -1)
		ft_error_ttf("Erreur initialisation TTF_Init: ");
	if (!(sdl->pwindow = SDL_CreateWindow("Doom Nukem", 100,
					100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error_sdl("Échec de creation de la fenetre");
	if (!(sdl->prenderer = SDL_CreateRenderer(sdl->pwindow, -1, 0)))
		ft_error_sdl("Échec de chargement du renderer");
	if (!(sdl->map = initialize_texture(sdl, WIDTH, HEIGHT)))
		handle_error(s, MALLOC_ERROR);
	if (!(sdl->game = initialize_texture(sdl, WIDTH, HEIGHT)))
		handle_error(s, MALLOC_ERROR);
	if (!(sdl->editor = initialize_texture(sdl, WIDTH, HEIGHT)))
		handle_error(s, MALLOC_ERROR);
	if (!(sdl->save = initialize_texture(sdl, WIDTH, HEIGHT)))
		handle_error(s, MALLOC_ERROR);
	sdl->musique = NULL;
	create_sounds(sdl);
	ft_init_font(s);
}
