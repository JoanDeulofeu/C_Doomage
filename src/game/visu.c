#include "doom.h"

int		ft_find_wall(t_main *s, double angle, Uint32 color)
{
	t_sector	*sct;
	t_vertex	*vtx;
	t_int		*s_vtx;
	t_dpos		wall1;
	t_dpos		wall2;
	t_dpos		i_line; //ligne imaginaire
	int			id = 0;
	int			id_wall = 1;

	sct = s->sector;
	while (s->player.sector != sct->id)
		sct = sct->next;
	s_vtx = sct->vertex;
	while (s_vtx->next)
	{
		id = s_vtx->value;
		vtx = s->vertex;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		wall1.x = vtx->x * s->editor->space + s->editor->decal_x;
		wall1.y = vtx->y * s->editor->space + s->editor->decal_y;

		id = s_vtx->next->value;
		vtx = s->vertex;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		wall2.x = vtx->x * s->editor->space + s->editor->decal_x;
		wall2.y = vtx->y * s->editor->space + s->editor->decal_y;
		i_line.x = s->player.pos.x + cos(to_rad(angle)) * 1000;
		i_line.y = s->player.pos.y - sin(to_rad(angle)) * 1000;

		s->line.x1 = s->player.pos.x;
		s->line.y1 = s->player.pos.y;
		s->line.x2 = i_line.x;
		s->line.y2 = i_line.y;
		// get_line(s, color);

		if (ft_find_intersection(s, wall1, wall2, s->player.pos, i_line) > 0)
			return (id_wall);
		id_wall++;
		s_vtx = s_vtx->next;
	}
	return (id_wall);
}

void	ft_visu_wall(t_main *s, int wall1_id, int wall2_id)
{
	int			nb_walls = wall2_id - wall1_id;
	int			i = 0;
	t_sector	*tmp_sct;
	// t_int		*vertex1_wall1;
	// t_int		*vertex2_wall1;
	t_pos		beg_wall;
	t_pos		end_wall;
	t_pos		player;

	tmp_sct = get_sector_by_id(s, s->player.sector);
	// vertex1_wall1 = (get_t_int_by_id(tmp_sct->vertex, wall1_id))->ptr->x;
	beg_wall.x = (get_t_int_by_id(tmp_sct->vertex, wall1_id)->ptr->x - s->editor->ref.x) * METRE;
	beg_wall.y = (get_t_int_by_id(tmp_sct->vertex, wall1_id)->ptr->y - s->editor->ref.y) * METRE;
	if (get_t_int_by_id(tmp_sct->vertex, wall1_id)->next)
	{
		end_wall.x = (get_t_int_by_id(tmp_sct->vertex, wall1_id)->next->ptr->x - s->editor->ref.x) * METRE;
		end_wall.y = (get_t_int_by_id(tmp_sct->vertex, wall1_id)->next->ptr->y - s->editor->ref.y) * METRE;
	}
	else
	{
		end_wall.x = (tmp_sct->vertex->next->ptr->x - s->editor->ref.x) * METRE;
		end_wall.y = (tmp_sct->vertex->next->ptr->y - s->editor->ref.y) * METRE;
	}
	if (s->player.p_ori.x < 0)
		player.x = (s->player.ori.x - s->editor->ref.x) * METRE - (((double)ft_abs(s->player.p_ori.x) / (double)s->editor->space) * METRE);
	else if(s->player.p_ori.x > 0)
		player.x = (s->player.ori.x - s->editor->ref.x) * METRE + (((double)ft_abs(s->player.p_ori.x) / (double)s->editor->space) * METRE);
	else
		player.x = (s->player.ori.x - s->editor->ref.x) * METRE;
	if (s->player.p_ori.y < 0)
		player.y = (s->player.ori.y - s->editor->ref.y) * METRE - (((double)ft_abs(s->player.p_ori.y) / (double)s->editor->space) * METRE);
	else if(s->player.p_ori.y > 0)
		player.y = (s->player.ori.y - s->editor->ref.y) * METRE + (((double)ft_abs(s->player.p_ori.y) / (double)s->editor->space) * METRE);
	else
		player.y = (s->player.ori.y - s->editor->ref.y) * METRE;

	// printf("player.x = %d, player.y = %d, reelx = %f\n", player.x, player.y, s->player.pos.x);

	// while (i < nb_walls)
	// {
	//
	// 	beg_wall.x = wall1->ptr->x;
	// 	beg_wall.y = wall1->ptr->y;
	// 	printf("wall 1.x = %d, wall1.y = %d\n", beg_wall.x, beg_wall.y);
	// 	//je recupere le repere x du premier vertex.
	// 	//je lui soustrais le repere ori et je le multiplie pa METER.
	//
	// 	i++;
	// }

}


void	ft_visu(t_main *s)
{
	int		mur1;
	int		mur2;
	int		angle;
	Uint32	color = 0x25f902ff; //#25f902

	s->player.sector = ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos));
	angle = s->player.angle - (FOV / 2) < 0 ? 360
	- fabs(s->player.angle - (FOV / 2)) : (s->player.angle - (FOV / 2));
	mur2 = ft_find_wall(s, angle, color);
	s->intersect2.x = s->tmp_intersect.x;
	s->intersect2.y = s->tmp_intersect.y;
	printf("id mur1 = %d, angle = %d\n", mur2, angle);
	s->line.x1 = s->player.pos.x;
	s->line.y1 = s->player.pos.y;
	s->line.x2 = s->intersect2.x;
	s->line.y2 = s->intersect2.y;
	get_line(s, color);

	color = 0xdb00ffff;
	angle = s->player.angle + (FOV / 2);
	if (angle > 360)
		angle -= 360;
	mur1 = ft_find_wall(s, angle, color);
	s->intersect1.x = s->tmp_intersect.x;
	s->intersect1.y = s->tmp_intersect.y;
	printf("id mur2 = %d, angle = %d\n", mur1, angle);
	s->line.x1 = s->player.pos.x;
	s->line.y1 = s->player.pos.y;
	s->line.x2 = s->intersect1.x;
	s->line.y2 = s->intersect1.y;
	get_line(s, color);

	// ft_visu_wall(s, mur1, mur2);
}
