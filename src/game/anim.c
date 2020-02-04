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
		if (cur->r_dist < STORM_RANGE && !ft_find_wall2(s, s->player.m_pos, cur->m_pos, YELLOW, s->player.sector_id))
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
			else if (sprite->a_name == shooting && !sprite->destroy)
				sprite_shooting(s, sprite);

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
	double		angle;
	t_dpos		point;

	wall = s->walls;
	while (wall && wall->sct_id != sprite->sct_id)
		wall = wall->next;
	point.x = sprite->m_pos.x + cos(to_rad(sprite->s_angle)) * 2;
	point.y = sprite->m_pos.y - sin(to_rad(sprite->s_angle)) * 2;
	// printf("angle sprite = %f\n", sprite->s_angle);
	angle = ft_find_angle_portal(&sprite->m_pos, &wall->player, &point, 1);
	// printf("angle = %f\n", angle);
	if (wall->player.y > sprite->m_pos.y)
		angle = 180 + (180 - angle);
	if (angle > 202)
		sprite->inverse = 0;
	else
		sprite->inverse = 1;
	if (angle > 337 || angle <= 22)
	{
		sprite->anim = s->stormtrooper.face;
		// printf("face\n");
		if (sprite->r_dist < STORM_RANGE) //ajouter find intersection pour savoir s'il y a un mur entre nous
		{
			sprite->current = 0;
			sprite->anim = s->stormtrooper.shooting;
			sprite->a_name = shooting;
			// sprite_shooting(s, sprite);
		}
	}
	else if ((angle > 22 && angle <= 67) || (angle > 292 && angle <= 337))
	{
		// printf("3/4 face");
		// if (sprite->inverse)
		// 	printf (" droite\n");
		// else
		// 	printf("\n");
		sprite->anim = s->stormtrooper.prof_face;
		if (sprite->r_dist < STORM_RANGE) //ajouter find intersection pour savoir s'il y a un mur entre nous
		{
			sprite->current = 0;
			sprite->anim = s->stormtrooper.shooting;
			sprite->a_name = shooting;
			// sprite_shooting(s, sprite);
		}

	}

	else if ((angle > 67 && angle <= 112) || (angle > 247 && angle <= 292))
	{
		// printf("prof");
		// if (sprite->inverse)
		// 	// printf (" droite\n");
		// else
		// 	printf("\n");
		sprite->anim = s->stormtrooper.prof;
	}
	else if ((angle > 112 && angle <= 157) || (angle > 202 && angle <= 247))
	{
		// printf("3/4 dos");
		// if (sprite->inverse)
		// 	printf (" droite\n");
		// else
		// 	printf("\n");
		sprite->anim = s->stormtrooper.prof_back;
	}
	else if (angle > 157 && angle <= 202)
	{
		// printf("dos\n");
		sprite->anim = s->stormtrooper.back;
	}

}
