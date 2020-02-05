#include "doom.h"

void	create_sounds(t_sdl *sdl)
{
	Mix_AllocateChannels(10);
	Mix_Volume(1, MIX_MAX_VOLUME * 0.5);
	sdl->sounds.select = Mix_LoadWAV("sounds/menu_mode.wav");
	sdl->sounds.explode = Mix_LoadWAV("sounds/explosion.wav");
	sdl->sounds.shotgun = Mix_LoadWAV("sounds/shotgun.wav");
	sdl->sounds.gun = Mix_LoadWAV("sounds/Pistol.wav");
	sdl->sounds.blaster = Mix_LoadWAV("sounds/blaster.wav");
	if (sdl->sounds.select == NULL)
		printf("Mix_LoadWAV: %s\n", Mix_GetError());;
}

void	play_music(t_main *s)
{
	s->sdl->musique = Mix_LoadMUS("musics/menu.wav");
	if (s->sdl->musique == NULL)
		ft_putstr("Error : music not loaded\n");
	else
		Mix_PlayMusic(s->sdl->musique, -1);
}
