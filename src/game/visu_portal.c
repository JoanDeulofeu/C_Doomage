/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:15:36 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 17:16:47 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		add_portal_to_list(t_main *s, t_sector *sct, t_visu vs)
{
	int			x;
	t_int		*vtx;
	int			new_x;

	x = 0;
	new_x = 0;
	s->portal_nb++;
	vtx = sct->vertex;
	vs.begin_wall_id = ft_find_wall(s, vs.begin, vs.left_point, vs.sct_id);
	if (vs.begin_wall_id == 0 || s->count_wall % 2 == 0)
	{
		vs.begin_wall_id = vs.vtx_gauche->ptr->id;
		vs.begin = vs.vtx_gauche->ptr->m_pos;
	}
	vs.begin_wall = get_t_int_by_vertex_id(vtx, vs.begin_wall_id);
	vs.end_wall_id = ft_find_wall(s, vs.end, vs.right_point, vs.sct_id);
	if (vs.end_wall_id == 0 || s->count_wall % 2 == 0)
		vs.end_wall_id = vs.vtx_droite->prev->ptr->id;
	else
		vs.end = s->tmp_intersect;
	vtx = vs.begin_wall;
	create_all_walls(s, vtx, &vs, 1);
	s->portal_nb--;
	set_visible_sprites(s, &vs);
}

t_dpos		ft_get_fake_player(t_main *s, t_dpos player, t_int *vtx, double *a)
{
	double		fake_angle;
	double		angle_prtl_in;
	double		angle_portal_out;
	t_dpos		lwall;
	t_dpos		rwall;

	lwall = vtx->ptr->m_pos;
	rwall = vtx->next->ptr->m_pos;
	if (!vtx || !vtx->vtx_dest)
		handle_error(s, POINTER_ERROR);
	fake_angle = ft_find_angle_portal(&lwall, &player, NULL, 1);
	fake_angle = (lwall.y < player.y) ? 360 - fake_angle : fake_angle;
	angle_prtl_in = ft_find_angle_portal(&lwall, &rwall, NULL, 1);
	angle_prtl_in = (rwall.y > lwall.y) ? 360 - angle_prtl_in : angle_prtl_in;
	angle_portal_out = ft_find_angle_portal(&vtx->vtx_dest->next->ptr->m_pos,
		&vtx->vtx_dest->ptr->m_pos, NULL, 1);
	if (vtx->vtx_dest->ptr->m_pos.y > vtx->vtx_dest->next->ptr->m_pos.y)
		angle_portal_out = 360 - angle_portal_out;
	fake_angle -= (angle_prtl_in - angle_portal_out);
	rwall.x = vtx->vtx_dest->next->ptr->m_pos.x
	+ cos(to_rad(fake_angle)) * ft_dist_t_dpos(player, lwall);
	rwall.y = vtx->vtx_dest->next->ptr->m_pos.y
	- sin(to_rad(fake_angle)) * ft_dist_t_dpos(player, lwall);
	*a -= (angle_prtl_in - angle_portal_out);
	return (rwall);
}
