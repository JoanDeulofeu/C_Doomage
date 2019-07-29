#include "doom.h"

void	ft_find_tmp_point(t_dpos *tmp, int avcm, t_dpos point1, t_dpos point2, double div)
{
	double	avc_pct;
	t_dpos dist;

	avc_pct = (avcm * 100) / div;
	dist.x = fabs(point1.x - point2.x);
	dist.y = fabs(point1.y - point2.y);
	tmp->x = point2.x > point1.x ?
	point1.x + ((dist.x * avc_pct) / 100) : point1.x - ((dist.x * avc_pct) / 100);
	tmp->y = point2.y > point1.y ?
	point1.y + ((dist.y * avc_pct) / 100) : point1.y - ((dist.y * avc_pct) / 100);
}


double	ft_find_tmp_pct(int avcm, double l_big_dist, double r_big_dist, double width_wall)
{
	double	big_dist;
	double	smallest_dist;
	double	biggest_dist;
	double	avc_pct;

	avc_pct = (avcm * 100) / width_wall;
	smallest_dist = l_big_dist > r_big_dist ? r_big_dist : l_big_dist;
	biggest_dist = l_big_dist > r_big_dist ? l_big_dist : r_big_dist;
	big_dist = ((avc_pct * (biggest_dist - smallest_dist)) / 100) + smallest_dist;

	// printf(", big dist = %.3f       ", big_dist);
	return ((big_dist * 100.0));
}

void	ft_print_wall(t_main *s, t_dpos player, t_dpos lwall, t_dpos rwall, t_dpos lplan, t_dpos rplan)
{
	(void)s;
	double	dist_plan;
	double	pct_plan;

	double	tmp_pct;
	double	tmp_small_dist;
	double	tmp_big_dist;

	double	l_big_dist;
	double	r_big_dist;
	double	l_small_dist;
	double	r_small_dist;

	double	width_wall;

	double	l_pct;
	double	r_pct;

	double i = 0;
	double block = 0;

	t_pos coord;

	t_dpos tmp_plan;
	t_dpos tmp_wall;

	int stop = 0;
	double avcm = ((double)WIDTHPLAN * (100.0 / WIDTH)) / 100;
	double iter_avcm = avcm;

	double height_wall = 0;

	dist_plan = ft_dist_t_dpos(lplan, rplan);
	pct_plan = (dist_plan * 100.0) / WIDTHPLAN;
	// printf("pourcentage plan = %.3f\n",pct_plan);

	l_big_dist = ft_dist_t_dpos(player, lwall);
	r_big_dist = ft_dist_t_dpos(player, rwall);
	l_small_dist = ft_dist_t_dpos(player, lplan);
	r_small_dist = ft_dist_t_dpos(player, rplan);
	l_pct = (l_big_dist * 100.0) / l_small_dist;
	r_pct = (r_big_dist * 100.0) / r_small_dist;
	// printf("pourcentage wall (left/right) = (%.3f, %.3f)\n\n",l_pct, r_pct);

	width_wall = ft_dist_t_dpos(lwall, rwall);
	printf("test ww = %.3f    wp = %.3f\n",width_wall, (double)WIDTHPLAN);
	double avcm_wall = (width_wall * (100.0 / WIDTH)) / 100;
	double iter_avcm_wall = avcm_wall;


	block = (WIDTH * pct_plan) / 100;
	coord.x = 0;
	tmp_big_dist = l_big_dist;
	tmp_small_dist = l_small_dist;
	tmp_pct = (tmp_big_dist * 100.0) / tmp_small_dist;
	// printf("pct dist = %.3f\n", tmp_pct);
	printf("dist plan y = %.3f et avcmnt = %.3f\n", fabs(lplan.y - rplan.y), avcm);
	printf("------ FIRST coord plan (%.3f, %.3f)\n",lplan.x, lplan.y);
	printf("------ FIRST coord wall (%.3f, %.3f)\n",lwall.x, lwall.y);
	while (i++ < block)
	{
		height_wall = HEIGHT / ((tmp_pct * 0.001)*4);
		// height_wall = (HEIGHT * tmp_pct) * 0.01;
		printf("high_wall %.3f   ", height_wall);
		coord.y = (HEIGHT / 2) - height_wall / 2;
		stop = (HEIGHT / 2) + height_wall / 2;
		// printf("y = %d,  stop = %d\n", coord.y, stop);
		while (coord.y < stop)
		{
			set_pixel(s->sdl->game, 0xffa800ff, coord);
			coord.y++;
		}
		coord.x++;
		avcm += iter_avcm;
		avcm_wall += iter_avcm_wall;
		ft_find_tmp_point(&tmp_plan, avcm, lplan, rplan, WIDTHPLAN); // find point plan
		printf("PLAN (%.3f, %.3f)     ",tmp_plan.x, tmp_plan.y);
		ft_find_tmp_point(&tmp_wall, avcm_wall, lwall, rwall, width_wall); // find point wall
		printf("WALL (%.3f, %.3f)       avcm(%.3f)  avcmwall(%.3f)    ",tmp_wall.x, tmp_wall.y, avcm, avcm_wall);

		tmp_small_dist = ft_dist_t_dpos(player, tmp_plan); //calc dist plan player
		tmp_big_dist = ft_dist_t_dpos(player, tmp_wall); //merde
		tmp_pct = (tmp_big_dist * 100.0) / tmp_small_dist; //merde
		// tmp_pct = (ft_find_tmp_pct(avcm, l_big_dist, r_big_dist, width_wall) / tmp_small_dist) *10; // calc pct dist
		printf("pct = %.3f\n", tmp_pct);
	}
	printf("------ END coord plan (%.3f, %.3f)\n",rplan.x, rplan.y);
	printf("------ END coord wall (%.3f, %.3f)\n",rwall.x, rwall.y);
	printf("\n\n");
}

void	ft_draw_visu(t_main *s, t_dpos player, t_visu *vs)
{
	t_dpos		plan_efw;
	t_sector	*sct;
	t_int		*vtx;

	sct = s->sector;
	while (s->player.sector_id != sct->id)
		sct = sct->next;
	vtx = sct->vertex;
	while (vtx->id != vs->begin_wall + 1) // trouver le deuxieme vertex du premier mur
	{
		vtx = vtx->next;
		if (vtx == NULL)
		{
			vtx = sct->vertex;
			break ;
		}
	}
	s->visu.tmp_wall.x = vtx->ptr->x * METRE;
	s->visu.tmp_wall.y = vtx->ptr->y * METRE;
	ft_find_intersection(s, s->visu.tmp_wall, player, s->visu.left_plan, s->visu.right_plan);
	plan_efw.x = s->tmp_intersect.x;
	plan_efw.y = s->tmp_intersect.y;
	// printf("wall n%d et vertex du mur = %d\n", vs->begin_wall, vtx->id);
	// printf("coordonees du vertex (%.2f, %.2f)\n",s->visu.tmp_wall.x, s->visu.tmp_wall.y);
	// printf("coordonees de l'intersect sur plan (%.2f, %.2f)\n", plan_efw.x, plan_efw.y);

	// s->line.x1 = s->visu.tmp_wall.x + s->editor->decal_x;
	// s->line.y1 = s->visu.tmp_wall.y + s->editor->decal_y;
	// s->line.x2 = plan_efw.x + s->editor->decal_x;
	// s->line.y2 = plan_efw.y + s->editor->decal_y;
	// get_line(s, 0xea7cfcff);

	ft_print_wall(s, player, s->visu.begin, s->visu.tmp_wall, s->visu.left_plan, plan_efw);

}
