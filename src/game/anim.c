#include "doom.h"

void	play_g_o_anim(t_main *s)
{
	t_pos	pos;
	int		time;

	pos.x = 0;
	pos.y = 0;
	if (s->time->g_o_ms == 0)
		s->time->g_o_ms = s->time->time_ms;
	time = s->time->time_ms - s->time->g_o_ms;
	if (time < 250)
		draw_plain_sprite(s, pos, s->gameover.image[0], s->sdl->game);
	else if (time >= 250 && time < 500)
		draw_plain_sprite(s, pos, s->gameover.image[1], s->sdl->game);
	else if (time >= 500 && time < 750)
		draw_plain_sprite(s, pos, s->gameover.image[2], s->sdl->game);
	else if (time >= 750 && time < 1000)
		draw_plain_sprite(s, pos, s->gameover.image[3], s->sdl->game);
	else if (time >= 1000 && time < 1250)
		draw_plain_sprite(s, pos, s->gameover.image[4], s->sdl->game);
	else if (time >= 1250 && time < 1500)
		draw_plain_sprite(s, pos, s->gameover.image[5], s->sdl->game);
	else if (time >= 1500 && time < 2000)
	{
		draw_plain_sprite(s, pos, s->gameover.image[6], s->sdl->game);
	}

}

void		select_weapon_anim(t_main *s)
{
	if (s->player.wp_name == kick)
		s->player.weapon = s->wp_anims.kick;
	else if (s->player.wp_name == gun)
		s->player.weapon = s->wp_anims.gun;
	else if (s->player.wp_name == shotgun)
		s->player.weapon = s->wp_anims.shotgun;
	s->player.weapon.current = 0;
}

void		sprite_shooting(t_main *s, t_sprite *cur)
{
	if (cur->anim.image[cur->current] != NULL)
	{
		// cur->s_angle = s->player.angle + 180;
		if (cur->r_dist < STORM_RANGE && !ft_find_wall(s, s->player.m_pos, cur->m_pos, s->player.sector_id))
		{
			cur->current = 1;
			if (s->time->time_ms - cur->shoot_ms > 1000)
			{
				cur->shoot_ms = s->time->time_ms;
				Mix_PlayChannel(6, s->sdl->sounds.blaster, 0);
				if (s->player.armor > 0)
					s->player.armor -= 20;
				else
				{
					s->player.health -= 10;
					if (s->player.health <= 0)
						s->player.dead = 1;
				}
			}
		}
		else
		{
			cur->a_name = walking;
			cur->current = 0;
		}
	}
}

void	play_sprites_anims(t_main *s)
{
	t_sprite *sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->name == storm)
		{
			if (sprite->a_name == shooting && !sprite->destroy)
			{
				// printf ("shooting\n");
				sprite->current = 0;
				sprite->anim = s->stormtrooper.shooting;
				sprite_shooting(s, sprite);
			}
			if (sprite->a_name == walking && !sprite->destroy)
			{
				if (sprite->set)
					select_anim(s, sprite);
				enemy_walk_anim(s, sprite);
			}
			else if (sprite->a_name == dying && !sprite->destroy)
			{
				kill_anim(s, sprite);
			}

		}
		sprite = sprite->next;
	}
}

void		kill_anim(t_main *s, t_sprite *sprite)
{
	if (s->time->time_ms - sprite->anim_ms > 50)
	{
		sprite->current++;
		if (!sprite->anim.image[sprite->current])
		{
			sprite->destroy = 1;
			sprite->set = 0;
			sprite->displayed = 0;
			sprite->current = 0;
		}

		sprite->anim_ms = s->time->time_ms;
	}
}

void 	enemy_walk_anim(t_main *s, t_sprite *sprite)
{
	if (s->time->time_ms - sprite->anim_ms > 200)
	{
		sprite->current++;
		if (!sprite->anim.image[sprite->current])
			sprite->current = 1;
		sprite->anim_ms = s->time->time_ms;
	}
}

void 	select_anim(t_main *s, t_sprite *sprite)
{
	t_walls 	*wall;
	double		angle = 0.0;
	// t_dpos		point;

	wall = s->walls;
	while (wall && wall->sct_id != sprite->sct_id)
		wall = wall->next;
	// point.x = sprite->m_pos.x + cos(to_rad(sprite->s_angle)) * 2;
	// point.y = sprite->m_pos.y - sin(to_rad(sprite->s_angle)) * 2;
	// printf("angle sprite = %f\n", sprite->s_angle);
	// angle = ft_find_angle_portal(&sprite->m_pos, &wall->player, &point, 1);

	if (wall->angle > 360)
		wall->angle = fmod(wall->angle, 360);
	if (sprite->s_angle > 360)
		sprite->s_angle = fmod(sprite->s_angle, 360);

	angle = wall->angle - sprite->s_angle;
	// printf("angle = %f\n", angle);
	// if (wall->player.y > sprite->m_pos.y)
	// 	angle = 180 + (180 - angle);
	if (angle > 180 || (angle > -180 && angle < 0))
		sprite->inverse = 0;
	else
		sprite->inverse = 1;
	if ((angle >= 0 && angle <= 23) || (angle >= 338 && angle <= 360)
	|| (angle >= -23 && angle <= 0) || (angle >= -360 && angle <= -338))
	{
		sprite->anim = s->stormtrooper.back;
	}
	else if ((angle >= 203 && angle <= 248) || (angle >= -158 && angle <= -113)
		|| (angle >= 113 && angle <= 158) || (angle >= -248 && angle <= -203))
	{
		sprite->anim = s->stormtrooper.prof_face;
		if (sprite->r_dist < STORM_RANGE) //ajouter find intersection pour savoir s'il y a un mur entre nous
		{
			sprite->current = 0;
			sprite->anim = s->stormtrooper.shooting;
			sprite->a_name = shooting;
			printf("true\n");
		}

	}
	else if ((angle >= 248 && angle <= 293) || (angle >= -113 && angle <= -68)
		|| (angle >= 68 && angle <= 113) || (angle >= -293 && angle <= -248))
	{
		sprite->anim = s->stormtrooper.prof;
	}
	else if ((angle >= 23 && angle <= 68) || (angle >= 293 && angle <= 338)
		|| (angle >= -338 && angle <= -293) || (angle >= -68 && angle <= -23))
	{
		sprite->anim = s->stormtrooper.prof_back;
	}
	else if ((angle >= 158 && angle <= 203) || (angle >= -203 && angle <= -158))
	{
		sprite->anim = s->stormtrooper.face;
		if (sprite->r_dist < STORM_RANGE && sprite->a_name != dying) //ajouter find intersection pour savoir s'il y a un mur entre nous
		{
			sprite->current = 0;
			sprite->anim = s->stormtrooper.shooting;
			sprite->a_name = shooting;
			printf("true\n");
		}
	}

}
