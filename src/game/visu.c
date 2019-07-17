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
		get_line(s, color);

		if (ft_find_intersection(s, wall1, wall2, s->player.pos, i_line) > 0)
			return (id_wall);
		id_wall++;
		s_vtx = s_vtx->next;
	}
	return (id_wall);
}

void	ft_visu_wall(t_main *s, int wall1, int wall2)
{
	(void)wall1;
	(void)wall2;
	// int		sight = (HEIGHT / 2); //vision
	// int		hp;
	// double	dist;
	// double	dist2;
	double	pasnous;
	fixed_float	intersect;
	fixed_float	player;
	fixed_float	nous;

	// on cherche la distance entre le joueur et l'intersection.
	// (xB−xA)2+(yB−yA)2
	// printf("Pos player (%f, %f)\n",s->player.pos.x, s->player.pos.y);
	// printf("Intersect1 (%f, %f)\n\n",s->intersect1.x, s->intersect1.y);
	pasnous = powf(s->intersect1.x - s->player.pos.x, 2);
	printf("angle (%f)\n", s->player.angle);
	printf("PAS NOUS = %f\n", pasnous);

	intersect = ft_float_to_fixed(s->intersect1.x);
	// printf("test inters     = %f\n", ft_fixed_to_float(intersect));
	player = ft_float_to_fixed(s->player.pos.x);
	// printf("test palyer     = %f\n", ft_fixed_to_float(player));
	intersect -= player;
	// printf("test calcul     = %f\n", ft_fixed_to_float(intersect));


	nous = ft_fixed_mul(intersect, intersect);
	printf("NOUS     = %f\n\n\n", ft_fixed_to_float(nous));
	// ft_test_float();


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
	// printf("id mur1 = %d, angle = %d\n", mur1, angle);

	color = 0xdb00ffff;
	angle = s->player.angle + (FOV / 2);
	if (angle > 360)
		angle -= 360;
	mur1 = ft_find_wall(s, angle, color);
	s->intersect1.x = s->tmp_intersect.x;
	s->intersect1.y = s->tmp_intersect.y;
	// printf("id mur2 = %d, angle = %d\n", mur2, angle);

	// ft_visu_wall(s, mur1, mur2);
}
