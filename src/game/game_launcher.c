/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_launcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:54:14 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 14:26:14 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	handle_game_mouse_move(t_main *s)
{
	if (s->sdl->event.type == SDL_MOUSEMOTION && !s->block_move)
	{
		s->ft_mouse.x = s->sdl->event.motion.x;
		s->ft_mouse.y = s->sdl->event.motion.y;
		rotate_mouse(s);
	}
}

void	handle_game_click(t_main *s)
{
	if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (s->sdl->event.button.button == SDL_BUTTON_LEFT &&
			!s->player.dead && !s->block_move)
		{
			if ((s->player.wp_name == gun && s->player.mun_gun > 0)
			|| (s->player.wp_name == shotgun && s->player.mun_shotgun > 0)
			|| s->player.wp_name == kick)
				shoot(s);
		}
	}
}

void	handle_game_wheel(t_main *s)
{
	if (s->sdl->event.type == SDL_MOUSEWHEEL &&
		!s->player.dead && !s->block_move)
	{
		if (s->sdl->event.wheel.y > 0)
			change_weapon(s, 1);
		if (s->sdl->event.wheel.y < 0)
			change_weapon(s, 0);
	}
}

void	game_handler(t_main *s)
{
	int			ingame;

	ingame = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	s->display_mode = game;
	s->play_or_editor = 0;
	while (ingame)
	{
		s->time->time_ms = SDL_GetTicks();
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			handle_game_mouse_move(s);
			if (s->sdl->event.type == SDL_QUIT)
				ingame = 0;
			handle_game_click(s);
			handle_game_wheel(s);
			if (s->sdl->event.type == SDL_KEYDOWN)
			{
				if (s->sdl->event.key.keysym.sym == SDLK_ESCAPE)
					ingame = 0;
			}
		}
		handle_game_keys(s);
	}
}

void	launch_game(t_main *s)
{
	display_map(s);
	game_handler(s);
}
