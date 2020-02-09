/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:22:46 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 16:27:23 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	create_sounds(t_sdl *sdl)
{
	Mix_AllocateChannels(10);
	Mix_Volume(1, MIX_MAX_VOLUME / 2);
	sdl->sounds.select = Mix_LoadWAV("sounds/menu_mode.wav");
	sdl->sounds.explode = Mix_LoadWAV("sounds/explosion.wav");
	sdl->sounds.shotgun = Mix_LoadWAV("sounds/shotgun.wav");
	sdl->sounds.gun = Mix_LoadWAV("sounds/Pistol.wav");
	sdl->sounds.blaster = Mix_LoadWAV("sounds/blaster.wav");
	sdl->sounds.hurt = Mix_LoadWAV("sounds/hurt.wav");
	sdl->musique = Mix_LoadMUS("musics/menu.wav");
	sdl->game_musique = Mix_LoadMUS("musics/mandalorian.wav");
	if (sdl->musique == NULL || !sdl->game_musique)
		ft_putstr("Error : music not loaded\n");
}

void	play_music(Mix_Music *music)
{
	Mix_PlayMusic(music, -1);
}
