#include "doom.h"

void 	display_sprites(t_main *s)
{
	t_sprite	*sprite;
	int			display;
	int			far_away_dist;
	int			far_away_id;

	sprite = s->sprite;
	display = 1;
	if (!sprite)
		return ;
	while (display)
	{
		display = 0;
		far_away_dist = 0;
		far_away_id = 0;
		sprite = s->sprite;
		while (sprite)
		{
			if (sprite->displayed == 1 && sprite->dist > far_away_dist && sprite->destroy == 0)
			{
				display = 1;
				far_away_dist = sprite->dist;
				far_away_id = sprite->id;
			}
			sprite = sprite->next;
		}
		if (!display)
			break ;
		sprite = s->sprite;
		while (sprite)
		{
			if (sprite->id == far_away_id && sprite->displayed == 1 && sprite->set == 1 & sprite->destroy == 0 && check_if_visible(s, sprite))
			{
				play_sprites_anims(s);
				draw_sprite(s, sprite->angle, sprite);
				sprite->displayed = 0;
			}
			sprite = sprite->next;
		}
	}
}


int		ft_get_sprite_height_pxl(t_main *s, t_sprite *sprite, double height)
{
	double		pct_eyesight; //pourcentage vision player
	t_sector 	*sct;

	sct = get_sector_by_id(s, sprite->sct_id);

	s->player.eyesight = s->player.foot_height - sct->floor + s->player.size;
	pct_eyesight = (s->player.eyesight * 100 / sprite->size);
	// printf("pct = %.2f      ", pct_eyesight);
	return ((pct_eyesight * height)* 0.01);
}

void		draw_sprite(t_main *s, double angle, t_sprite *cur)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	int			i;
	int			j;
	double		height;
	double		width;
	double 		pct;
	double		diff_height_pxl;
	int			bottom;
	int			tmp;
	(void)angle;

	// draw_sprite_hitbox(s);
	wp = cur->anim.image[cur->current];
	pct = (cur->r_dist * METRE * 100) / cur->l_dist;
	height = HEIGHT / ((pct * 0.001) * 4) * cur->size * HEIGHT_MULT;
	pct = (100 * wp->w) / wp->h;
	width = (pct * height)* 0.01;
	i = 0;
	coord.x = cur->x - (width * 0.5);
	while (coord.x < cur->x + width * 0.5 && coord.x >= 0 && coord.x <= WIDTH)
	{
		j = 0;
		// coord.x = cur->x + i;
		perx = (double)((coord.x - cur->x - width* 0.5) * 100) / (width);
		// printf("perx = %f\n", perx);

		diff_height_pxl = ft_get_sprite_height_pxl(s, cur, height);
		coord.y = (HEIGHT* 0.5) - height + s->player.y_eye + diff_height_pxl;
		bottom = (HEIGHT* 0.5) + s->player.y_eye + diff_height_pxl;
		tmp = coord.y;
		while (coord.y < bottom) //J'ai ajouté la protection pour pas que ca rame mais ça fait disparaitre le sprite quand on ets trop pres
		{
			pery = (double)((coord.y - tmp) * 100) / height;
			if (cur->inverse == 0)
				px = (int)(pery* 0.01* (double)wp->h) * wp->w
					+ (int)(perx* 0.01* (double)wp->w);
			else
				px = (int)(pery* 0.01* (double)wp->h) * wp->w
					- (int)(perx* 0.01* (double)wp->w);

			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 65280)
				set_pixel(s->sdl->game, wp->tex[px], coord);
			coord.y++;
		}
		coord.x++;
	}
}
