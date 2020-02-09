/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_initialize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:41:31 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 20:37:23 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double		get_demi_fov(t_dpos player, double angle)
{
	t_dpos	plan;
	double	demi_fov;

	plan.x = player.x + cos(to_rad(angle)) * METRE;
	plan.x = plan.x + cos(to_rad(angle + 90)) * WIDTHPLAN * 0.5;
	plan.y = player.y - sin(to_rad(angle)) * METRE;
	plan.y = plan.y - sin(to_rad(angle + 90)) * WIDTHPLAN * 0.5;
	demi_fov = ft_find_angle_plan(ft_dist_t_dpos(player, plan),
	METRE, WIDTHPLAN * 0.5);
	return (demi_fov);
}

void		initialize_editor(t_main *s)
{
	if (!(s->editor = (t_editor*)malloc(sizeof(t_editor))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void *)s->editor, sizeof(t_editor));
	s->editor->space = G_SPACE;
	s->editor->anchor_size = 5;
	s->editor->mode = move;
	s->editor->color_sector = 2;
	s->editor->sprite_selected = storm;
	s->editor->tmp_floor = -1;
}

void		initialize_player(t_main *s)
{
	s->player.set = 1;
	s->player.size = PLAYER_SIZE;
	s->player.foot_height = -1;
	s->player.r_pos.x = 7.5;
	s->player.r_pos.y = 7.3;
	s->player.m_pos.x = s->player.r_pos.x * METRE;
	s->player.m_pos.x = s->player.r_pos.y * METRE;
	s->player.health = 100;
	s->player.armor = 100;
	s->player.eyesight = EYESIGHT;
	s->player.abs_angle = 180;
	s->player.angle = s->player.abs_angle;
	s->player.init_space = s->editor->space;
	s->player.demi_fov = get_demi_fov(s->player.m_pos, s->player.angle);
	s->player.mun_gun = 45;
	s->player.mun_shotgun = 12;
	s->player.weapon = s->wp_anims.kick;
	s->player.wp_name = kick;
	s->player.wp_wheel[gun] = 0;
	s->player.wp_wheel[kick] = 1;
	s->player.wp_wheel[shotgun] = 0;
	s->player.weapon.current = 0;
	s->player.power = 10;
}

void		malloc_main(t_main *s, char *str)
{
	if (!(s->font = (t_font*)malloc(sizeof(t_font))))
		handle_error(s, MALLOC_ERROR);
	if (!(s->savemap = (t_savemap*)malloc(sizeof(t_savemap))))
		handle_error(s, MALLOC_ERROR);
	if (!(s->time = (t_timer*)malloc(sizeof(t_timer))))
		handle_error(s, MALLOC_ERROR);
	if (!(s->msg = (t_msg*)malloc(sizeof(t_msg))))
		handle_error(s, MALLOC_ERROR);
	if (!(s->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void*)s->sdl, sizeof(t_sdl));
	if (str)
		s->map_name = ft_strdup(str);
	else
		s->map_name = ft_strdup(MAP);
	ft_bzero(s->savemap->str, 41);
	s->savemap->error_msg = 0;
}

t_main		*initialize_main(char *str)
{
	t_main		*s;

	if (!(s = (t_main*)malloc(sizeof(t_main))))
		exit(-1);
	ft_bzero((void*)s, sizeof(t_main));
	initialize_editor(s);
	malloc_main(s, str);
	initialize_player(s);
	initialize_editor(s);
	ft_set_time(s);
	ft_init_msg(s);
	s->sct_without_ceiling = 15;
	s->ennemi.damage = -1;
	s->play_or_editor = 2;
	s->time->jetpack_reserve = JET_TIME;
	initialize_sdl(s, s->sdl);
	load_images(s);
	s->save_coord_vtx.x = 0;
	s->save_coord_vtx.y = 0;
	return (s);
}
