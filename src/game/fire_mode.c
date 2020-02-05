#include "doom.h"

void 		set_weapon_range(t_main *s)
{
	if (s->player.wp_name == kick)
	{
		s->player.range = 10;
		s->player.power = 10;

	}
	else if (s->player.wp_name == gun)
	{
		s->player.range = 20;
		s->player.power = 30;

	}
	else if (s->player.wp_name == shotgun)
	{
		s->player.range = 10;
		s->player.power = 100;
	}
}

void		change_weapon(t_main *s, int up)
{
	if (up)
	{
		s->player.wp_name++;
		// printf(" up name = %d\n", s->player.wp_name);
		if (s->player.wp_name > 2)
			s->player.wp_name = 0;
		while (s->player.wp_wheel[s->player.wp_name] != 1)
		{
			s->player.wp_name++;
			if (s->player.wp_name > 2)
			s->player.wp_name = 0;
		}
	}
	if (up == 0)
	{
		if (s->player.wp_name == kick)
		{
			s->player.wp_name = 2;
		}
		else
			s->player.wp_name--;
		// printf(" down name = %d\n", s->player.wp_name);
		while (s->player.wp_wheel[s->player.wp_name] != 1)
		{
			if (s->player.wp_name == kick)
				s->player.wp_name = 2;
			else
				s->player.wp_name--;
		}
	}
	select_weapon_anim(s);
	set_weapon_range(s);
}

// int			check_exist_sprite(t_main *s)
// {
// 	t_sprite	*cur;
// 	double		value;
// 	t_dpos		ret;
// 	double		dist;
// 	int			i;
// 	int			j;
// 	int			id;
//
// 	i = 0;
// 	id = -1;
// 	cur = s->sprite;
// 	dist = -1;
// 	while (cur != NULL)
// 	{
// 		value = (WIDTH / (cur->r_dist)) / 60;
// 		i = 0;
// 		while (i < (cur->img->w) * value)
// 		{
// 			j = 0;
// 			ret.x = i;
// 			ret.x += cur->angle * (double)(WIDTH / 80)
// 				- ((cur->img->w * value)* 0.5);
// 			while (j < (cur->img->h) * value)
// 			{
// 				ret.y = j++;
// 				ret.y += HEIGHT* 0.5 + s->player.y_eye + s->player.eyesight
// 					- (((cur->img->h * value) / 3.5));
// 				if ((int)ret.x == (WIDTH* 0.5) && (int)ret.y == (HEIGHT* 0.5))
// 				{
// 					if (cur->r_dist < dist || dist == -1)
// 					{
// 						dist = cur->r_dist;
// 						id = cur->id;
// 					}
// 				}
// 			}
// 			i++;
// 		}
// 		cur = cur->next;
// 	}
// 	return (id);
// }

void		give_damage(t_main *s, int id)
{
	t_sprite	*cur;

	cur = s->sprite;
	while (cur != NULL)
	{
		if (cur->id == id && cur->life != 0)
		{
			cur->life = 0;
			cur->current = 0;
			// set_img(s, cur, 5, 0);
			break ;
		}
		cur = cur->next;
	}
}

void		fire(t_main *s)
{
	t_sprite 	*sprite;
	t_sprite	*save_sprite;
	double 		pct;
	double		height;
	double		width;
	double		diff_height_pxl;
	int			bottom;

	sprite = s->sprite;
	save_sprite = NULL;
	while (sprite)
	{
		if (sprite->name == storm && sprite->set == 1 && !sprite->destroy)
		 {
			pct = (sprite->r_dist * METRE * 100) / sprite->l_dist;
	 		height = HEIGHT / ((pct * 0.001) * 4) * sprite->size * HEIGHT_MULT;
	 		pct = (100 * sprite->anim.image[sprite->current]->w) / sprite->anim.image[sprite->current]->h;
	 		width = (pct * height)* 0.01;
			diff_height_pxl = ft_get_sprite_height_pxl(s, sprite, height);
			bottom = (HEIGHT* 0.5) + s->player.y_eye + diff_height_pxl;
			 if (sprite->r_dist < s->player.range
 			&& (WIDTH* 0.5) > sprite->x - (width * 0.5) && WIDTH * 0.5 <
 			sprite->x + (width * 0.5) && (HEIGHT * 0.5) > (HEIGHT* 0.5) - height + s->player.y_eye + diff_height_pxl
			&& (HEIGHT * 0.5) < bottom)
				{
					if (save_sprite)
					{
						if (sprite->r_dist < save_sprite->r_dist)
							save_sprite = sprite;
					}
					else
						save_sprite = sprite;
				}
		}
		sprite = sprite->next;
	}
	if (save_sprite)
	{
		printf("hit\n");
		save_sprite->life -= s->player.power;
		if (save_sprite->life <= 0 && save_sprite->a_name != dying)
		{
			save_sprite->anim = s->stormtrooper.dying;
			save_sprite->a_name = dying;
			save_sprite->current = 0;
		}
	}
}
