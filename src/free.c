#include "doom.h"

void	free_image(t_image *img)
{
	if (!img)
		return ;
	ft_memdel((void **)&img->tex);
	ft_memdel((void **)&img);
}

void	free_sectors(t_main *s)
{
	int id;

	id = 0;
	while (s->sector)
	{
		remove_sector(s, id, 0, 0);
	}
}

void	free_images(t_main *s)
{
	// free_areas(s);
	// free_image(s->skybox);
	// free_image(s->weapon.image[0]);
	// free_image(s->weapon.image[1]);
	// free_image(s->weapon.image[2]);
	// free_image(s->door);
	// free_image(s->interface);
	// free_image(s->win);
	// free_image(s->menu);
	// free_image(s->coupe);
}

void	free_texture(t_texture *tex)
{
	if (!tex)
		return ;
	ft_memdel((void **)&tex->content);
	SDL_DestroyTexture(tex->texture);
	ft_memdel((void **)&tex);
}

void	free_program(t_main *s)
{
	int i;

	i = 0;
	// if (s->map != NULL)
	// {
	// 	while (i < s->height)
	// 		ft_memdel((void **)&s->map[i++]);
	// 	ft_memdel((void **)&s->map);
	// }
	if (s->sdl->musique != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(s->sdl->musique);
		// Mix_FreeChunk(s->sdl->sounds.door);
		// Mix_FreeChunk(s->sdl->sounds.shot);
		Mix_CloseAudio();
	}
	free_images(s);
	free_sectors(s);
	free_texture(s->sdl->map);
	free_texture(s->sdl->game);
	free_texture(s->sdl->editor);
	SDL_DestroyRenderer(s->sdl->prenderer);
	ft_memdel((void **)&s->sdl);
	ft_memdel((void **)&s);
}
