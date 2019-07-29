#include "doom.h"

void	update_image(t_main *s, t_texture *texture)
{
	SDL_SetRenderTarget(s->sdl->prenderer, texture->texture);
	SDL_UpdateTexture(texture->texture, NULL, texture->content, WIDTH
		* sizeof(Uint32));
	SDL_SetRenderTarget(s->sdl->prenderer, NULL);
	SDL_RenderCopy(s->sdl->prenderer, texture->texture, NULL, NULL);
}

void	set_pixel(t_texture *text, Uint32 color, t_pos coord)
{
	if (coord.x >= 0 && coord.x < WIDTH && coord.y >= 0 && coord.y < HEIGHT)
	{
		text->content[coord.x + coord.y * WIDTH] = color;
	}
}

void	draw_rect(t_texture *text, t_dpos orig, t_dpos dest, Uint32 color)
{
	int			i;
	int			j;
	t_pos		coord;

	orig.x = orig.x < 0 ? 0 : orig.x;
	orig.y = orig.y < 0 ? 0 : orig.y;
	dest.x = dest.x > WIDTH ? WIDTH : dest.x;
	dest.y = dest.y > HEIGHT ? HEIGHT : dest.y;
	i = orig.x;
	while (i < dest.x)
	{
		j = orig.y;
		while (j < dest.y)
		{
			coord.x = i;
			coord.y = j++;
			set_pixel(text, color, coord);
		}
		i++;
	}
}
