/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:20:42 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 14:26:52 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	handle_game_keys_2(t_main *s, const Uint8 *keys)
{
	if (s->player.jump_height == 0 && !s->block_move)
		ft_crouch(s, keys);
	if (s->transition)
		ft_transition(s);
	if (s->time->explosion_ms != 0 && s->time->explosion_ms + 2500
		< s->time->time_ms)
		destroy_planet(s);
	if (s->player.size == PLAYER_SIZE && !s->block_move)
		ft_jump(s, keys);
	ft_reset_color_screen(s->sdl->game->content, WIDTH * HEIGHT);
	display_sky(s, 0, 0, 0);
	if (s->skybox.current != 0)
		destroy_planet(s);
	set_player(s);
	handle_sector_zero(s);
	unset_sprites(s);
	play_sprites_anims(s);
	ft_visu_joan(s);
	if (keys[SDL_SCANCODE_E])
		check_bomb(s);
	fly(s);
	rand_move(s, 0, NULL);
	draw_hud(s);
	animate_weapon(s);
	clear_wall_list(s);
}

void	handle_game_keys(t_main *s)
{
	const Uint8	*keys;

	if (!s->player.dead)
	{
		s->player.sector_id = ft_is_in_sector(s, s->player.m_pos);
		keys = SDL_GetKeyboardState(NULL);
		if ((keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN] ||
			keys[SPRINT]) && (s->player.sector_id != 0 && !s->block_move))
			ft_move_player(s, keys, PLAYER_SPEED);
		if ((keys[LEFT_NUM] || keys[RIGHT_NUM]) && !s->block_move)
			rotate_player(s, keys);
		if (s->player.jetpack && keys[SDL_SCANCODE_SPACE] && !s->block_move)
			s->player.fly = 1;
		else if (s->player.jetpack == 1)
		{
			s->player.fly = 0;
			s->player.jump = 2;
		}
		handle_game_keys_2(s, keys);
	}
	else
		play_g_o_anim(s);
	update_image(s, s->sdl->game);
}
