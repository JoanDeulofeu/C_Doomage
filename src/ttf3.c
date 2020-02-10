/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:21:25 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/10 22:07:19 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_draw_ttf_editor3(t_main *s, t_ttf ttf)
{
	if (s->savemap->error_msg == 1)
	{
		ttf.r = 255;
		ttf.g = 0;
		ttf.b = 0;
		ttf.pos.x = 300;
		ttf.pos.y = 620;
		ttf.str = ft_strdup("ERROR : File name -> min 3 caracteres");
		ft_create_ttf(ttf, s, s->font->roboto);
	}
	else if (s->savemap->error_msg == 2)
	{
		ttf.r = 0;
		ttf.g = 255;
		ttf.b = 0;
		ttf.pos.x = 350;
		ttf.pos.y = 620;
		ttf.str = ft_strdup("Sauvegarde de la map reussi.");
		ft_create_ttf(ttf, s, s->font->roboto);
	}
}

void	ft_draw_ttf_editor2(t_main *s, t_ttf ttf)
{
	ttf.r = 255;
	ttf.g = 0;
	ttf.b = 0;
	ttf.pos.x = 200;
	ttf.pos.y = 200;
	ttf.str = ft_strdup("SAUVEGARDE");
	ft_create_ttf(ttf, s, s->font->stylish100);
	ttf.r = 255;
	ttf.g = 255;
	ttf.b = 255;
	ttf.pos.x = 240;
	ttf.pos.y = 400;
	ttf.str = ft_strdup("Veuillez entrer le nom de la map a sauvegarder :");
	ft_create_ttf(ttf, s, s->font->press_start);
	if (s->savemap->str[0] != '\0')
	{
		ttf.r = 255;
		ttf.g = 255;
		ttf.b = 255;
		ttf.pos.x = 240;
		ttf.pos.y = 465;
		ttf.str = ft_strdup(s->savemap->str);
		ft_create_ttf(ttf, s, s->font->press_start);
	}
	ft_draw_ttf_editor3(s, ttf);
}

void	ft_draw_ttf_editor(t_main *s)
{
	t_ttf		ttf;

	ttf.r = 0;
	ttf.g = 0;
	ttf.b = 0;
	ttf.pos.x = 0;
	ttf.pos.y = 0;
	ft_display_message(s);
	if (s->display_mode == save)
		ft_draw_ttf_editor2(s, ttf);
}
