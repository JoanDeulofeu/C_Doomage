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

	i = -1;
	while (anim.image[++i] != NULL)
		free_image(anim.image[i]);
}

void	free_lanim(t_lanim *anim) // A TESTER
{
	int	i;

	i = -1;
	while (anim->image[++i] != NULL)
		free_image(anim->image[i]);
}

void	free_lsprite(t_main *s)
{
	t_lsprite	*lst;
	t_lsprite	*tmp;

	lst = s->lsprite;
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->img != NULL)
			free_image(tmp->img);
		if (tmp->anim != NULL)
			free_lanim(tmp->anim);
		ft_memdel((void **)&tmp);
	}
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
	free_lsprite(s);
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
	// (void)s;
	// free_areas(s);
	// free_image(s->weapon.image[0]);
	// free_image(s->weapon.image[1]);
	// free_image(s->weapon.image[2]);
	// free_image(s->door);
	// free_image(s->interface);
	// free_image(s->win);
	free_anim(s->menu);
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
	free_sprite(s);
	free_texture(s->sdl->map);
	free_texture(s->sdl->game);
	free_texture(s->sdl->editor);
	SDL_DestroyRenderer(s->sdl->prenderer);
	ft_memdel((void **)&s->sdl);
	ft_memdel((void **)&s->editor);
	ft_memdel((void **)&s->map_name);
	ft_memdel((void **)&s->savemap);
	ft_memdel((void **)&s);
}
