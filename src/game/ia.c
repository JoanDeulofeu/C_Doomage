#include "doom.h"

int			check_exist(t_main *s, t_dpos target, int id)
{
	t_sprite	*cur;
	double		hitbox;

	hitbox = 0.5;
	cur = s->sprite;
	// if (id == found_closer(s) && cur->id != id)
	//   return (cur->id);
	while (cur != NULL)
	{
		//cur->id == found_closer(s)
		// value = HEIGHT / (cur->dist);
		if (((target.x >= (cur->r_pos.x - hitbox)
			&& target.x <= (cur->r_pos.x + hitbox))
				&& (target.y >= (cur->r_pos.y - hitbox))
					&& target.y <= (cur->r_pos.y + hitbox))
						&& cur->id != id)
		{
			return (cur->id);
		}
		cur = cur->next;
	}
	return (-1);
}

double		found_player(t_main *s, t_sprite *cur)
{
	t_dpos	ctr_l;
	double	angle;
	t_pos	ret;

	angle = 0;
	ctr_l.x = cur->pos.x + cos(to_rad(angle)) * cur->dist;
	ctr_l.y = cur->pos.y - sin(to_rad(angle)) * cur->dist;
	while (angle <= 360)
	{
		ctr_l.x = cur->pos.x + cos(to_rad(angle)) * cur->dist;
		ctr_l.y = cur->pos.y - sin(to_rad(angle)) * cur->dist;
		ret = ft_dpos_to_pos(ctr_l);
		//	 set_pixel(s->sdl->editor, BLUE, ret);
		if ((ret.x >= (s->player.pos.x - HITBOX)
			&& ret.x <= (s->player.pos.x + HITBOX))
				&& (ret.y >= (s->player.pos.y - HITBOX)
					&& ret.y <= (s->player.pos.y + HITBOX)))
			break ;
		angle += 0.1;
	}
	return (angle);
}

void		rand_move(t_main *s)
{
	t_dpos		target;
	double		angle;
	t_sprite	*sprite;
	// printf("rand\n\n");
	// printf("sprite->angle =%f\n\n",sprite->angle);

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->set == 1 && sprite->name == storm && sprite->destroy == 0 && sprite->a_name == walking)
		{
			target.x = sprite->r_pos.x;
			target.y = sprite->r_pos.y;
			target.x += cos(to_rad(sprite->s_angle)) * SPRITE_MOVE_SPEED;
			target.y -= sin(to_rad(sprite->s_angle)) * SPRITE_MOVE_SPEED;
			if (ft_is_in_sector(s, get_px_r_pos(s, target)) != 0)
			{
				sprite->r_pos = target;
				set_sprite(s);
			}
			else
			{
				angle = (int)(rand() / (double)RAND_MAX * (ANGLE_MAX - 1));
				// printf("angle =%f\n",angle);
				sprite->s_angle = angle;
			}
		}
		sprite = sprite->next;

	}
	//  angle = found_player(s,cur);

	//target = get_px_r_pos(s,target);
	//   printf("cur->pos (%d,%d)\n",cur->pos.x,cur->pos.y);
	// printf("target (%f,%f)\n\n",target.x,target.y);
}

void		sprite_move_on_player(t_main *s, t_sprite *cur)
{
	t_dpos	target;
	double	angle;

	target.x = cur->r_pos.x;
	target.y = cur->r_pos.y;
	angle = found_player(s, cur);
	target.x += cos(to_rad(angle)) * SPRITE_MOVE_SPEED;
	target.y -= sin(to_rad(angle)) * SPRITE_MOVE_SPEED;
	//target = get_px_r_pos(s,target);
	//  printf("angle =%f\n",angle);
	// printf("cur->dist =%f\n",cur->dist);
	//  printf("cur->pos (%d,%d)\n",cur->pos.x,cur->pos.y);
	// printf("target (%f,%f)\n\n",target.x,target.y);
	if (ft_is_in_sector(s, get_px_r_pos(s, target)) != 0
		&& cur->dist > SPRITE_SHOT_DIST
			&& check_exist(s, target, cur->id) == -1)
	{
		cur->r_pos = target;//sget_abs_r_pos(s,ft_dpos_to_pos(target));
		cur->s_angle = angle;
	}
}

// void		ia(t_main *s, t_sprite *cur)
// {
// 	// rand_move(s, cur);
// 	//    sprite_move_on_player(s,cur);
// }
