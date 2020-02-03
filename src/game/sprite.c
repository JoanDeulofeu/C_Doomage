#include "doom.h"

void		reset_statue(t_main *s)
{
	t_sprite *sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->name == bomb)
			sprite->current = 0;
		sprite = sprite->next;
	}
}

int		check_if_visible(t_main *s, t_sprite *sprite)
{
	t_walls	*wall;
	t_4dpos	pos;

	wall = s->walls;
	while (wall)
	{
		pos.pos1 = wall->player;
		pos.pos3 = wall->left;
		pos.pos4 = wall->right;
		if (wall->wall_or_portal == 'w')
		{
			pos.pos2.x = wall->player.x + cos(to_rad(angle_mod(sprite->angle + wall->angle))) * (sprite->r_dist * METRE);
			pos.pos2.y = wall->player.y - sin(to_rad(sprite->angle + wall->angle)) * (sprite->r_dist * METRE);
			// if (s->printf)
			// {
			// 	// printf("check sector (%d)    pos player (%.1f, %.1f)\n", wall->sct_id, wall->player.x, wall->player.y);
			// }
			draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, pos.pos2)), S_RED);
			if (ft_find_intersection(s, pos, 1))
			{
				sprite->set = 0;
				sprite->displayed = 0;
				return (0);
			}
		}
		wall = wall->next;
	}
	return (1);
}

void 	get_sprite_x(t_main *s, t_visu *vs, t_sprite *sprite)
{
	float		per;
	t_4dpos		pos;

	per = 0;
	pos.pos1 = vs->left_plan;
	pos.pos2 = vs->right_plan;
	pos.pos3 = vs->player;
	pos.pos4 = sprite->m_pos;
	ft_find_intersection(s, pos, 1);
	per = ft_dist_t_dpos(pos.pos1, s->tmp_intersect)
	* 100 / ft_dist_t_dpos(pos.pos1, pos.pos2);
	sprite->x = per * WIDTH* 0.01- sprite->anim.image[sprite->anim.current]->w;

}

void 	unset_sprites(t_main *s)
{
	t_sprite *sprite;

	if ((sprite = s->sprite) == NULL)
		return ;
	while (sprite)
	{
		sprite->dist = ft_dist_t_dpos(s->player.m_pos, sprite->m_pos);
		sprite->set = 0;
		sprite->displayed = 0;
		sprite = sprite->next;
	}
}

void 	set_visible_sprites(t_main *s, t_visu *vs)
{
	t_lsprite 	*liste;
	t_int		*wall;
	int			inter;
	t_4dpos		pos;


	liste = vs->sct->liste;
	// printf("test secteur tester par set_visibe_sprites (%d)\n", vs->sct->id);
	if(!liste)
		return ;
	wall = vs->vtx_gauche;
	if (wall == NULL || vs->vtx_droite == NULL)
		return ;
	while (liste)
	{
		inter = 0;
		wall = vs->vtx_gauche;
		pos.pos3 = vs->player;
		pos.pos4 = liste->sprite->m_pos;
		while (wall->id != vs->vtx_droite->next->id)
		{
			pos.pos1 = wall->ptr->m_pos;
			pos.pos2 = wall->next->ptr->m_pos;
			if (wall->wall_value == -1 && ft_find_intersection(s, pos, 1))
			{
				inter = 1;
				break;
			}
			wall = wall->next;
		}
		pos.pos1 = vs->left_plan;
		pos.pos2 = vs->right_plan;
		if (inter == 0 && ft_find_intersection(s, pos, 1))
		{
			liste->sprite->r_dist = ft_dist_t_dpos(vs->player, liste->sprite->m_pos) / METRE;
			liste->sprite->l_dist = ft_dist_t_dpos(vs->player, s->tmp_intersect);
			get_sprite_x(s, vs, liste->sprite);
			liste->sprite->angle = ft_find_angle_portal(&vs->player, &liste->sprite->m_pos, NULL, 1);
			if (liste->sprite->m_pos.y > vs->player.y)
				liste->sprite->angle = 180 + (180 - liste->sprite->angle);
			liste->sprite->angle = (angle_mod(liste->sprite->angle - vs->angle));
			liste->sprite->set = 1;
			liste->sprite->displayed = 1;
		}
		else
			liste->sprite->set = 0;
		liste = liste->next;
	}
}

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
	while (display) //tant quil reste des sprites a afficher
	{
		display = 0;
		far_away_dist = 0;
		far_away_id = 0;
		sprite = s->sprite;
		while (sprite) // cherche le sprite le plus loin
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
		while (sprite) //avance jusquau sprite le plus loin pour lafficher
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

void	set_sprite(t_main *s)
{
	t_sprite *tmp;

	tmp = s->sprite;
	while (tmp)
	{
		tmp->pos = get_px_r_pos(s, tmp->r_pos);
		tmp->m_pos.x = tmp->r_pos.x * METRE;
		tmp->m_pos.y = tmp->r_pos.y * METRE;
		tmp = tmp->next;
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

	draw_sprite_hitbox(s);
	wp = cur->anim.image[cur->current];
	pct = (cur->r_dist * METRE * 100) / cur->l_dist;
	height = HEIGHT / ((pct * 0.001) * 4) * cur->size * HEIGHT_MULT;
	pct = (100 * wp->w) / wp->h;
	width = (pct * height)* 0.01;
	i = 0;
	coord.x = cur->x - (width* 0.5);
	while (coord.x < cur->x + width* 0.5 && coord.x >= 0 && coord.x <= WIDTH)
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
