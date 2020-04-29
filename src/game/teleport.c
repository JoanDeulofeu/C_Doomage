/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:33:57 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 14:08:13 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ft_check_high_coll(t_main *s, t_int *wall)
{
	t_sector	*sct_dest;

	sct_dest = get_sector_by_id(s, wall->sct_dest);
	if (s->player.foot_height < (double)sct_dest->floor)
		return (0);
	if ((double)sct_dest->ceiling < s->player.foot_height + s->player.size)
		return (0);
	return (1);
}

int		test_portal_collisions(t_main *s, t_4dpos player, int ptr_id, int nb)
{
	int	sct_id;

	sct_id = s->player.sector_id;
	if ((ptr_id = ft_find_wall(s, player.pos2, player.pos1, sct_id)) == 0)
	{
		player.pos1 = s->col_pos;
		player.pos2 = s->col_pos;
		player.pos1.x += nb;
		player.pos2.x -= nb;
		if ((ptr_id = ft_find_wall(s, player.pos2, player.pos1, sct_id)) == 0)
		{
			player.pos1.y += nb;
			player.pos2.y -= nb;
			if ((ptr_id = ft_find_wall(s, player.pos2, player.pos1,
				sct_id)) == 0)
			{
				player.pos1.x += nb * 2;
				player.pos2.x -= nb * 2;
				ptr_id = ft_find_wall(s, player.pos2, player.pos1, sct_id);
			}
		}
	}
	return (ptr_id);
}

int		get_wall_to_teleport(t_main *s)
{
	int			ptr_id;
	t_4dpos		player;
	int			nb;

	ptr_id = 0;
	nb = 10;
	player.pos1 = s->col_pos;
	player.pos2 = s->col_pos;
	player.pos1.y += nb;
	player.pos2.y -= nb;
	while (ptr_id == 0 && nb++ < 5000)
	{
		player.pos1 = s->col_pos;
		player.pos2 = s->col_pos;
		player.pos1.y += nb;
		player.pos2.y -= nb;
		ptr_id = test_portal_collisions(s, player, ptr_id, nb);
	}
	return (ptr_id);
}

void	teleport_to_wall(t_main *s, t_int *wall)
{
	t_sector *sct;

	s->player.m_pos = ft_get_fake_player(s, s->col_pos, wall, &s->player.angle);
	s->player.r_pos.x = s->player.m_pos.x / METRE;
	s->player.r_pos.y = s->player.m_pos.y / METRE;
	set_player(s);
	s->player.sector_id = wall->sct_dest;
	sct = get_sector_by_id(s, s->player.sector_id);
	if (s->player.foot_height > (double)sct->floor + 0.01)
	{
		s->player.jump_height += s->player.floor_height - (double)sct->floor;
		s->player.prev_jump_height = s->player.jump_height;
		if (s->player.jump == 0 && s->player.fly == 0)
			s->player.jump = 3;
	}
	s->portal_nb = 0;
	handle_sector_zero(s);
}

void	teleport_player(t_main *s)
{
	int			ptr_id;
	t_int		*wall;

	ptr_id = get_wall_to_teleport(s);
	if (ptr_id == 0)
	{
		handle_sector_zero(s);
		return ;
	}
	wall = get_t_int_by_vertex_id(get_sector_by_id(s,
		s->player.sector_id)->vertex, ptr_id);
	if (wall->vtx_dest == NULL)
	{
		if (wall->next->vtx_dest != NULL)
			wall = wall->next;
		else if (wall->prev->vtx_dest != NULL)
			wall = wall->prev;
	}
	if (ft_check_high_coll(s, wall) == 0)
		return ;
	teleport_to_wall(s, wall);
}
