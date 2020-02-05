/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:53:55 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/05 15:57:37 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_reset_color_screen(Uint32 *str, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		str[i] = 0x13131dFF;
}

t_dpos		ft_pos_to_dpos(t_pos pos)
{
	t_dpos	dpos;

	dpos.x = (float)pos.x;
	dpos.y = (float)pos.y;
	return (dpos);
}

t_pos		ft_dpos_to_pos(t_dpos dpos)
{
	t_pos	pos;

	pos.x = (int)dpos.x;
	pos.y = (int)dpos.y;
	return (pos);
}

t_pos		get_px_pos(t_main *s, t_pos ref)
{
	t_pos		pos;
	t_editor	*edi;
	int			correc;

	correc = 0;
	edi = s->editor;
	if (edi->decal_x <= 0)
		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.x = (ref.x - edi->ref.x + correc) * edi->space
		+ (edi->decal_x % edi->space);
	if (edi->decal_y <= 0)
		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (ref.y - edi->ref.y + correc) * edi->space
		+ (edi->decal_y % edi->space);
	return (pos);
}

t_dpos		get_abs_r_pos(t_main *s, t_pos ori)
{
	t_dpos		res;
	t_editor	*edi;

	edi = s->editor;
	res.x = 0;
	res.y = 0;
	res.x = ori.x - edi->decal_x;
	res.x = (res.x / edi->space);
	res.y = ori.y - edi->decal_y;
	res.y = (res.y / edi->space);
	return (res);
}
