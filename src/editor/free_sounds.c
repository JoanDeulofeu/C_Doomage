/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:56:14 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 14:07:19 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_music(Mix_Music *music)
{
	if (music)
		Mix_FreeMusic(music);
}

void	free_sound(Mix_Chunk *sound)
{
	if (sound)
		Mix_FreeChunk(sound);
}
