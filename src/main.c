/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:20:59 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 18:15:25 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ending(t_main *s, int key)
{
	t_pos coord;

	coord.x = 0;
	coord.y = 0;
	draw_plain_sprite(0, coord, s->cinematic.image[4], s->sdl->game);
	update_image(s, s->sdl->game);
	while (1)
	{
		SDL_WaitEvent(&s->sdl->event);
		if (s->sdl->event.type == SDL_QUIT)
			handle_error(s, 0);
		else if (s->sdl->event.type == SDL_KEYDOWN)
		{
			key = s->sdl->event.key.keysym.sym;
			if (key == SDLK_RETURN
				|| s->sdl->event.key.keysym.sym == SDLK_KP_ENTER)
				break ;
			else if (key == SDLK_ESCAPE)
				handle_error(s, 0);
		}
	}
	reset(s);
}

void	reset2(t_main *s)
{
	t_sector *sct;

	s->block_move = 0;
	s->player.r_pos = s->player.r_ori;
	set_player(s);
	s->player.sector_id = ft_is_in_sector(s, s->player.m_pos);
	sct = get_sector_by_id(s, s->player.sector_id);
	s->player.jump_height = 0;
	s->player.foot_height = sct->floor + s->player.jump_height;
	s->player.health = 100;
	s->player.armor = 100;
	s->player.dead = 0;
	s->player.wp_wheel[gun] = 0;
	s->player.wp_wheel[shotgun] = 0;
	s->player.wp_name = kick;
	s->player.jetpack = 0;
	s->time->jetpack_reserve = JET_TIME;
	s->player.fly = 0;
	s->player.foot_height = -1;
	s->cinematic.current = 0;
	s->skybox.current = 0;
	s->time->explosion_ms = 0;
	select_weapon_anim(s);
	set_weapon_range(s);
	reset_statue(s);
}

void	reset(t_main *s)
{
	t_sprite *sprite;

	reset2(s);
	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->destroy == 1 && sprite->name == storm)
			add_sprite_to_sector(s, sprite);
		if (sprite->name == storm)
		{
			sprite->a_name = walking;
			sprite->anim = s->stormtrooper.face;
		}
		sprite->destroy = 0;
		sprite->life = 100;
		sprite->r_pos = sprite->r_ori;
		sprite->angle = 0;
		sprite->r_dist = 100;
		sprite->set = 0;
		sprite->displayed = 0;
		sprite = sprite->next;
	}
	set_sprite(s);
}

int		main(int argc, char **argv)
{
	t_main *s;

	(void)argc;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
		== -1)
		ft_putstr(Mix_GetError());
	if (!argv[1])
		s = initialize_main(NULL);
	else
		s = initialize_main(argv[1]);
	SDL_ShowCursor(1);
	ft_parsing(s, 0);
	s->wall_fk_id = 0;
	while (handle_menu(s))
		;
	free_program(s);
}
