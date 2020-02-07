/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:30:28 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 20:34:00 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	change_wall_texture(t_main *s, int up)
{
	t_int		*wall;
	t_dpos		pos;
	t_sector	*sct;
	int			ptr_id;

	sct = get_sector_by_id(s, s->player.sector_id);
	if (sct == NULL)
		return ;
	pos = get_direction(s, NULL, 1000, s->player.m_pos);
	ptr_id = ft_find_wall(s, s->player.m_pos, pos, sct->id);
	wall = get_t_int_by_vertex_id(sct->vertex, ptr_id);
	if (wall == NULL)
		return ;
	if (up == 1)
	{
		wall->tex_nb += 1;
		if (s->editor->all_texture.image[wall->tex_nb] == NULL)
			wall->tex_nb = 0;
	}
	else if (up == 0)
	{
		if ((wall->tex_nb -= 1) == -1)
			wall->tex_nb = MAX_TEXTURES;
	}
	wall->image = s->editor->all_texture.image[wall->tex_nb];
}

Uint32	ft_color_trump(t_main *s, t_int *s_vtx)
{
	if (s_vtx->wall_value != -1)
		return (0xddd241ff);
	if (s_vtx->selected == 2)
		return (0xddd241ff);
	if (s->editor->wall2 == NULL && s->editor->wall && s_vtx == s->editor->wall)
		return (0xddd241ff);
	else if (s->editor->wall2 && s->editor->wall2->selected == 3
		&& s_vtx == s->editor->wall2)
		return (GREEN);
	else if (s->editor->wall2 && s->editor->wall2->selected == 4
		&& s_vtx == s->editor->wall2)
		return (S_RED);
	else
		return (0xff7062FF);
}

void	ft_trump(t_main *s, t_int *s_vtx)
{
	Uint32		color;
	t_vertex	*vtx;

	color = ft_color_trump(s, s_vtx);
	vtx = s_vtx->ptr;
	s->line.x1 = vtx->pos.x + s->editor->decal_x;
	s->line.y1 = vtx->pos.y + s->editor->decal_y;
	vtx = s_vtx->next->ptr;
	s->line.x2 = vtx->pos.x + s->editor->decal_x;
	s->line.y2 = vtx->pos.y + s->editor->decal_y;
	get_line(s, color);
}

void	ft_draw_all_wall(t_main *s)
{
	t_int			*vtx;
	t_sector		*sct;
	int				i;

	sct = s->sector;
	vtx = NULL;
	while (sct)
	{
		i = 0;
		if (s->editor->mode_floor == 1 && sct->floor != s->editor->dply_floor)
		{
			sct = sct->next;
			continue;
		}
		vtx = sct->vertex;
		while (i++ < sct->vertex->prev->id)
		{
			ft_trump(s, vtx);
			vtx = vtx->next;
		}
		sct = sct->next;
	}
}
