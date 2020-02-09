/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:12:13 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 14:04:38 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_texture(t_texture *tex)
{
	if (!tex)
		return ;
	ft_memdel((void **)&tex->content);
	SDL_DestroyTexture(tex->texture);
	ft_memdel((void **)&tex);
}

void	free_sectors(t_main *s)
{
	t_vertex	*v_tmp;
	t_sector	*s_tmp;

	v_tmp = s->vertex;
	while (s->sector)
	{
		s_tmp = s->sector;
		s->sector = s_tmp->next;
		free_sector_struct(s_tmp);
		ft_memdel((void **)&s_tmp);
	}
	while (s->vertex)
	{
		v_tmp = s->vertex;
		s->vertex = s->vertex->next;
		ft_memdel((void **)&v_tmp);
	}
}

void	free_fonts(t_main *s)
{
	TTF_CloseFont(s->font->press_start);
	TTF_CloseFont(s->font->press_start25);
	TTF_CloseFont(s->font->open);
	TTF_CloseFont(s->font->roboto);
	TTF_CloseFont(s->font->stylish);
	TTF_CloseFont(s->font->stylish100);
	TTF_CloseFont(s->font->digit);
	TTF_CloseFont(s->font->digit42);
}

void	free_sounds(t_main *s)
{
	Mix_HaltMusic();
	free_music(s->sdl->musique);
	free_music(s->sdl->game_musique);
	free_sound(s->sdl->sounds.explode);
	free_sound(s->sdl->sounds.select);
	free_sound(s->sdl->sounds.shotgun);
	free_sound(s->sdl->sounds.blaster);
	free_sound(s->sdl->sounds.gun);
	free_sound(s->sdl->sounds.hurt);
	Mix_CloseAudio();
}

void	free_program(t_main *s)
{
	free_sounds(s);
	clear_wall_list(s);
	free_images_1(s);
	free_sectors(s);
	free_sprite(s);
	free_fonts(s);
	TTF_Quit();
	ft_memdel((void **)&s->font);
	free_texture(s->sdl->map);
	free_texture(s->sdl->game);
	free_texture(s->sdl->editor);
	free_texture(s->sdl->save);
	SDL_Quit();
	SDL_DestroyRenderer(s->sdl->prenderer);
	ft_memdel((void **)&s->map_name);
	ft_memdel((void **)&s->msg);
	ft_memdel((void **)&s->sdl);
	ft_memdel((void **)&s->editor);
	ft_memdel((void **)&s->time);
	ft_memdel((void **)&s->savemap);
	ft_memdel((void **)&s->str_vtx);
	ft_memdel((void **)&s->player);
	ft_memdel((void **)&s);
}
