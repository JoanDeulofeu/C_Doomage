#include "doom.h"

void		handle_game_keys(t_main *s)
{
	const Uint8	*keys;

	s->player.sector_id = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos));
	keys = SDL_GetKeyboardState(NULL);
	if ((keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN] || keys[SPRINT])
		&& (s->player.sector_id != 0))
		ft_move_player(s, keys, 2);
	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
		rotate_player(s, keys);
	ft_reset_color_screen(s->sdl->game->content, WIDTH * HEIGHT);
	display_sky(s);
	if (s->skybox.current != 0 && s->skybox.current < 17)
		destroy_planet(s);
	display_map(s);
	handle_sector_zero(s);
	unset_sprites(s);
	if (s->player.jump_height == 0)
		ft_crouch(s, keys);
	if (s->player.size == PLAYER_SIZE)
		ft_jump(s, keys);
	ft_visu_joan(s, keys);
	// play_anim(s);
	//	sprite_move(s);
	health(s);
	display_sprites(s);
	draw_hud(s);
	clear_wall_list(s);
	// print_hp(s);
	// ft_nul(s);
	update_image(s, s->sdl->game);
}

void		game_handler(t_main *s)
{
	int			ingame;

	ingame = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	s->display_mode = game;
	// draw_interface(s);
	while (ingame)
	{
		s->time->time_ms = SDL_GetTicks();
		ft_fps(s);
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			if (s->sdl->event.type == SDL_MOUSEMOTION)
			{
				s->ft_mouse.x = s->sdl->event.motion.x;
				s->ft_mouse.y = s->sdl->event.motion.y;
				rotate_mouse(s);
			}
			if (s->sdl->event.type == SDL_QUIT)
				ingame = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (s->sdl->event.button.button == SDL_BUTTON_LEFT)
				{
						// shoot(s,1);
						if (s->skybox.current < 17 && s->player.abs_angle > 62
							&& s->player.abs_angle < 82 && s->player.y_eye >= 376
							&& s->player.y_eye <= 782)
						{
							destroy_planet(s);
						}

				}
			}
			if (s->sdl->event.type == SDL_MOUSEWHEEL)
			{

			}
			if (s->sdl->event.type == SDL_KEYDOWN)
				if (s->sdl->event.key.keysym.sym == SDLK_ESCAPE)
					ingame = 0;
				// if (key_controls_game(s, s->sdl->event.key.keysym.sym) == 0)
				// 		ingame = 0;
		}
		// printf("current = %d\n", s->player.weapon.current);
		handle_game_keys(s);
	}
}

void launch_game(t_main *s)
{
	display_map(s);
	game_handler(s);
}
