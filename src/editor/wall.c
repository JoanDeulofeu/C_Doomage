/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:30:30 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/24 16:11:11 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_close_sector2(t_main *s)
{
	ft_parse_sector(s, s->str_vtx);
	ft_strdel(&s->str_vtx);
	ft_check_validity_last_sector(s);
	ft_reset_color_vertex(s);
}

void	ft_close_sector(t_main *s, int i, int nb_wall, int init)
{
	char	*begin;
	char	*end;

	begin = ft_strdup("sector 0 3 | ");
	end = NULL;
	s->str_vtx = ft_strjoin_free(&begin, &s->str_vtx);
	while (nb_wall > i++)
	{
		if (init)
			init = ft_norm_close_sector(s, 1, end);
		else
			ft_norm_close_sector(s, 2, end);
	}
	i = 0;
	init = 1;
	while (nb_wall > i++)
	{
		if (init)
			init = ft_norm_close_sector2(s, 1, end);
		else
			ft_norm_close_sector2(s, 2, end);
	}
	ft_close_sector2(s);
}

t_pos	ft_get_mouse(t_main *s)
{
	t_pos		mouse;

	mouse = get_abs_pos(s, s->editor->ori);
	mouse.x *= METRE;
	mouse.y *= METRE;
	return (mouse);
}

int		ft_sector_mode(t_main *s)
{
	t_pos		mouse;
	int			id;

	mouse = ft_get_mouse(s);
	if ((id = anchor_exists(s, s->editor->ori))
	&& ft_is_in_sector(s, ft_pos_to_dpos(mouse)) == 0)
	{
		if (s->str_vtx != NULL && ft_atoi(s->str_vtx) == id)
		{
			if ((ft_howmany_char(s->str_vtx, ' ') + 1) > 2)
				ft_close_sector(s, 0, ft_howmany_char(s->str_vtx, ' ') + 1, 1);
			return (2);
		}
		else
		{
			ft_save_sector_vextex(s, id);
			return (1);
		}
	}
	return (1);
}
