#include "doom.h"

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
}

int			check_exist_sprite(t_main *s)
{
	t_sprite	*cur;
	double		value;
	t_dpos		ret;
	double		dist;
	int			i;
	int			j;
	int			id;

	i = 0;
	id = -1;
	cur = s->sprite;
	dist = -1;
	while (cur != NULL)
	{
		value = (WIDTH / (cur->r_dist)) / 60;
		i = 0;
		while (i < (cur->img->w) * value)
		{
			j = 0;
			ret.x = i;
			ret.x += cur->angle * (double)(WIDTH / 80)
				- ((cur->img->w * value) / 2);
			while (j < (cur->img->h) * value)
			{
				ret.y = j++;
				ret.y += HEIGHT / 2 + s->player.y_eye + s->player.eyesight
					- (((cur->img->h * value) / 3.5));
				if ((int)ret.x == (WIDTH / 2) && (int)ret.y == (HEIGHT / 2))
				{
					if (cur->r_dist < dist || dist == -1)
					{
						dist = cur->r_dist;
						id = cur->id;
					}
				}
			}
			i++;
		}
		cur = cur->next;
	}
	return (id);
}

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

	sprite = s->sprite;
	save_sprite = NULL;
	while (sprite)
	{
		if (sprite->name == storm && sprite->set == 1 && sprite->r_dist < 6
			&& (WIDTH / 2) > sprite->x && WIDTH / 2 <
			sprite->x + (sprite->anim.image[sprite->current]->w
				* ((HEIGHT / sprite->r_dist) / 60)))
		{
			if (save_sprite)
			{
				if (sprite->r_dist < save_sprite->r_dist)
					save_sprite = sprite;
			}
			else
				save_sprite = sprite;
		}
		sprite = sprite->next;
	}
	if (save_sprite)
	{
		save_sprite->anim = s->stormtrooper.dying;
		save_sprite->a_name = dying;
		save_sprite->current = 0;
	}
}
