#include "doom.h"

void 	reset(t_main *s)
{
	t_sprite *sprite;

	s->player.r_pos = s->player.r_ori;
	set_player(s);
	s->player.health = 100;
	s->player.armor = 100;
	s->player.dead = 0;
	s->player.wp_wheel[gun] = 0;
	s->player.wp_wheel[shotgun] = 0;
	s->player.wp_name = kick;
	select_weapon_anim(s);
	set_weapon_range(s);
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


		sprite = sprite->next;
	}
	set_sprite(s);
}

void	draw_player(t_main *s, t_dpos p_pos)
{
	t_dpos p_size;

	p_size.x = p_pos.x + 20;
	p_size.y = p_pos.y + 20;
	draw_rect(s->sdl->game, p_pos, p_size, s->sdl->game->color_tmp);
}

int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_main *s;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
		== -1)
		ft_putstr(Mix_GetError());
	if (!argv[1])
		s = initialize_main(NULL);
	else
		s = initialize_main(argv[1]);
	s->p_pos.x = 500;
	s->p_pos.y = 330;
	draw_player(s, s->p_pos);
	SDL_ShowCursor(1);
	ft_parsing(s, 0);
	// get_grid_tab(s);
	s->wall_fk_id = 0;
	while (handle_menu(s));
	// display_map(s);
	// ft_test_float();
	// editor_handler(s);
	Mix_HaltMusic();
	Mix_CloseAudio();
	SDL_Quit();
	free_program(s);
	// event_handler(s);
}
