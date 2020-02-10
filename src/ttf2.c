/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:21:20 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 22:05:59 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_draw_ttf_play5(t_main *s, t_ttf ttf, char *str)
{
	(void)str;
	ttf.r = 0;
	ttf.g = 140;
	ttf.b = 0;
	if (s->player.wp_name == kick)
		ttf.g = 250;
	ttf.pos.x = 290;
	ttf.pos.y = 715;
	ttf.str = ft_strdup("Weapon 1 : Kick");
	ft_create_ttf(ttf, s, s->font->digit);
}

void	ft_draw_ttf_play4(t_main *s, t_ttf ttf)
{
	if (s->player.wp_wheel[gun] == 1)
	{
		ttf.g = 140;
		if (s->player.wp_name == gun)
			ttf.g = 255;
		ttf.pos.y = 737;
		ttf.str = ft_strdup("Weapon 2 : Gun");
		ft_create_ttf(ttf, s, s->font->digit);
	}
	if (s->player.wp_wheel[shotgun] == 1)
	{
		ttf.g = 140;
		if (s->player.wp_name == shotgun)
			ttf.g = 250;
		ttf.pos.y = 759;
		ttf.str = ft_strdup("Weapon 3 : Shotgun");
		ft_create_ttf(ttf, s, s->font->digit);
	}
}

void	ft_draw_ttf_play3(t_main *s, t_ttf ttf, char *str)
{
	ttf.pos.x = 896;
	str = ft_itoa(s->player.keys);
	ttf.str = ft_strdup(str);
	ft_create_ttf(ttf, s, s->font->digit42);
	ft_memdel((void **)&str);
	ttf.pos.x = 732;
	if (s->player.jetpack)
	{
		ttf.str = get_jetpack_value(s);
		ttf.r = 0;
		ttf.b = 0;
		ttf.g = 250;
		ft_create_ttf(ttf, s, s->font->digit);
	}
	else
	{
		ttf.str = ft_strdup("Empty");
		ft_create_ttf(ttf, s, s->font->digit42);
	}
	ft_memdel((void **)&str);
}

void	ft_draw_ttf_play2(t_main *s, t_ttf ttf, char *str)
{
	ttf.pos.x = 163;
	str = ft_itoa(s->player.armor);
	ttf.str = ft_strdup(str);
	ft_create_ttf(ttf, s, s->font->digit42);
	ft_memdel((void **)&str);
	ttf.pos.x = 630;
	if (s->player.wp_name == kick)
	{
		ttf.str = ft_strdup("inf");
	}
	else if (s->player.wp_name == gun && s->player.wp_wheel[gun] == 1)
	{
		str = ft_itoa(s->player.mun_gun);
		ttf.str = ft_strdup_free(&str);
	}
	else if (s->player.wp_name == shotgun && s->player.wp_wheel[shotgun] == 1)
	{
		str = ft_itoa(s->player.mun_shotgun);
		ttf.str = ft_strdup_free(&str);
	}
	ft_create_ttf(ttf, s, s->font->digit42);
}

void	ft_draw_ttf_play(t_main *s)
{
	t_ttf		ttf;
	char		*str;

	if (s->skybox.current >= 17)
		return ;
	ft_display_message(s);
	ttf.r = 210;
	ttf.g = 0;
	ttf.b = 0;
	ttf.pos.x = 57;
	ttf.pos.y = 730;
	str = ft_itoa(s->player.health);
	ttf.str = ft_strdup(str);
	ft_create_ttf(ttf, s, s->font->digit42);
	ft_memdel((void **)&str);
	ft_draw_ttf_play2(s, ttf, str);
	ft_draw_ttf_play3(s, ttf, str);
	ttf.pos.x = 290;
	ft_draw_ttf_play4(s, ttf);
	ft_draw_ttf_play5(s, ttf, str);
}
