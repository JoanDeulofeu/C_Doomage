/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:20 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 14:36:29 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_player(t_main *s)
{
	s->player.pos = ft_pos_to_dpos(get_px_r_pos(s, s->player.r_pos));
	s->player.m_pos.x = s->player.r_pos.x * METRE;
	s->player.m_pos.y = s->player.r_pos.y * METRE;
	if (!(s->player.pos.x < 0 || s->player.pos.y < 0 || s->player.pos.x > WIDTH
		|| s->player.pos.y > HEIGHT) && s->player.set == 1)
	{
		draw_anchor(s, ft_dpos_to_pos(s->player.pos), BLUE);
		trace_direction(s);
	}
}

void	rotate_player(t_main *s, const Uint8 *keys)
{
	double	angle;

	if (keys[LEFT_NUM] || keys[RIGHT_NUM])
	{
		angle = s->player.angle + (keys[RIGHT_NUM] - keys[LEFT_NUM])
			* ROTATE_SPEED / 10 + 360;
		s->player.angle = (int)angle % 360;
		s->player.abs_angle = (int)(s->player.abs_angle +
				(keys[RIGHT_NUM] - keys[LEFT_NUM])
				* ROTATE_SPEED / 10 + 360) % 360;
	}
}

int		check_wall_security(t_main *s, t_dpos target)
{
	t_dpos		m_target;
	int			wall_id;
	t_sector	*sct;
	t_int		*wall;

	m_target.x = target.x * METRE;
	m_target.y = target.y * METRE;
	if ((wall_id = ft_find_wall(s, s->player.m_pos, m_target,
		s->player.sector_id)) != 0)
	{
		sct = get_sector_by_id(s, s->player.sector_id);
		wall = get_t_int_by_vertex_id(sct->vertex, wall_id);
		if (wall == NULL)
			return (0);
		return (wall->wall_value);
	}
	return (0);
}

int		check_player_collision(t_main *s, t_dpos target, const Uint8 *keys)
{
	int		col;
	int		check;

	if ((col = is_colliding(s, target, s->player.sector_id, target)) == 0)
	{
		if ((check = check_wall_security(s, target)) != 0)
		{
			if (check != -1)
				teleport_player(s, keys);
			return (0);
		}
		if (handle_sector_zero(s))
			return (0);
		s->player.r_pos = target;
		set_player(s);
	}
	if (col > 0)
		teleport_player(s, keys);
	return (1);
}

void	ft_move_player(t_main *s, const Uint8 *keys, int move_speed)
{
	t_dpos	target;
	double	speed;

	if (s->display_mode == save)
		return ;
	speed = move_speed * move_speed * 0.03;
	if ((keys[UP] || keys[DOWN]) && (keys[LEFT] || keys[RIGHT]))
		speed /= 1.5;
	if (keys[SPRINT] && keys[UP])
		speed *= 1.2;
	target = s->player.r_pos;
	target = get_direction(s, keys, speed, target);
	s->col_pos = get_direction(s, keys, speed + 10, s->player.m_pos);
	check_collectible(s);
	check_player_collision(s, target, keys);
}
