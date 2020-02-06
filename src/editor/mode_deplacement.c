/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_deplacement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 01:46:47 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/05 18:03:10 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	mouse_grid(t_main *s, t_pos save)
{
	if (s->editor->decal_x + save.x > INT_MIN && s->editor->decal_x +
		save.x < INT_MAX)
		s->editor->decal_x += save.x;
	if (s->editor->decal_y + save.y > INT_MIN && s->editor->decal_y +
		save.y < INT_MAX)
		s->editor->decal_y += save.y;
}

void	move_editor(t_main *s, const Uint8 *keys)
{
	if (keys[RIGHT_AR] && (s->editor->decal_x < INT_MAX)
		&& (s->player.pos.x < INT_MAX))
		s->editor->decal_x += 5;
	if (keys[LEFT_AR] && (s->editor->decal_x > INT_MIN)
		&& (s->player.pos.x > INT_MIN))
		s->editor->decal_x -= 5;
	if (keys[UP_AR] && (s->editor->decal_y > INT_MIN)
		&& (s->player.pos.y > INT_MIN))
		s->editor->decal_y -= 5;
	if (keys[DOWN_AR] && (s->editor->decal_y < INT_MAX)
		&& (s->player.pos.y < INT_MAX))
		s->editor->decal_y += 5;
}
