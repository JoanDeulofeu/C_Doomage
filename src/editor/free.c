#include "doom.h"

void	free_image(t_image *img)
{
	if (!img)
		return ;
	ft_memdel((void **)&img->tex);
	ft_memdel((void **)&img);
}

void	free_anim(t_anim anim)
{
	int	i;
	if (!anim.image[0] && anim.image[1])
		i = 0;
	else
		i = -1;
	while (anim.image[++i] != NULL)
		free_image(anim.image[i]);
}

void	free_sprite(t_main *s)
{
	t_sprite	*sprite;
	t_sprite	*tmp;

	sprite = s->sprite;
	while (sprite != NULL)
	{
		tmp = sprite;
		sprite = sprite->next;
		ft_memdel((void **)&tmp);
	}
	// free_lsprite(s);
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
	// printf ("structure principale vertex = %p, sector = %p, grid = %p, sr_vtx = %p\n", s->vertex, s->sector, s->grid, s->str_vtx);
		// t_sdl			*sdl;
		// t_editor		*editor;
		// t_dpos			p_pos;
		// t_mouse			ft_mouse;
		// t_line			line;
		// t_player		player;
		// t_vertex		*vertex;
		// t_sector		*sector;
		// t_point			**grid;
		// char			*str_vtx;
	// printf ("true\n");
}

void	free_images(t_main *s)
{
	free_anim(s->menu);
	free_anim(s->editor->menu);
	free_anim(s->editor->sprite_menu);
	free_anim(s->editor->m_floor);
	free_anim(s->stormtrooper.face);
	free_anim(s->stormtrooper.back);
	free_anim(s->stormtrooper.prof);
	free_anim(s->stormtrooper.prof_face);
	free_anim(s->stormtrooper.prof_back);
	free_anim(s->stormtrooper.dying);
	free_anim(s->stormtrooper.shooting);
	free_anim(s->wp_anims.gun);
	free_anim(s->wp_anims.shotgun);
	free_anim(s->wp_anims.kick);
	free_anim(s->items.table);
	free_anim(s->items.lamp);
	free_anim(s->items.gun);
	free_anim(s->items.shotgun);
	free_anim(s->items.big_g_ammo);
	free_anim(s->items.big_s_ammo);
	free_anim(s->items.jetpack);
	free_anim(s->editor->all_texture);
	// free_anim(s->editor->all_sprite);
	free_anim(s->gameover);
	free_anim(s->skybox);
	free_image(s->interface);
	free_image(s->savemap->croix_rouge);
	free_image(s->player.hud);
	free_image(s->player.crosshair);
}

void	free_texture(t_texture *tex)
{
	if (!tex)
		return ;
	ft_memdel((void **)&tex->content);
	SDL_DestroyTexture(tex->texture);
	ft_memdel((void **)&tex);
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
		Mix_FreeChunk(s->sdl->sounds.explode);
		Mix_FreeChunk(s->sdl->sounds.select);
		Mix_FreeChunk(s->sdl->sounds.shotgun);
		Mix_FreeChunk(s->sdl->sounds.blaster);
		Mix_FreeChunk(s->sdl->sounds.gun);
		Mix_CloseAudio();
	}
	clear_wall_list(s);
	free_images(s);
	free_sectors(s);
	free_sprite(s);
	free_fonts(s);
	TTF_Quit();
	ft_memdel((void **) &s->font);
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
	while (1);
}
