#include "doom.h"

int		check_walls_lenght(t_int *wall1, t_int *wall2)
{
	t_dpos beg1;
	t_dpos beg2;
	t_dpos end1;
	t_dpos end2;

	end1 = ft_pos_to_dpos(wall1->next->ptr->pos);
	end2 = ft_pos_to_dpos(wall2->next->ptr->pos);
	beg1 = ft_pos_to_dpos(wall1->ptr->pos);
	beg2 = ft_pos_to_dpos(wall2->ptr->pos);
	if (ft_dist_t_dpos(beg1, end1) == ft_dist_t_dpos(beg2, end2))
		return (1);
	else
		return (0);
}

//fonction qui revoie l'angle du point needed, 1 pour left, 2 pour right, 3 pour third
int		ft_find_angle_portal(t_dpos *left, t_dpos *right, t_dpos *third, int needed)
{
	//third est le troisieme point pour trouver l'angle si besoin;
	int angle = 0;
	int left_right_dist;
	int right_third_dist;
	int left_third_dist;
	t_dpos	tmp_third;

	if (third == NULL)
	{
		third = &tmp_third;
		third->x = left->x + 100;
		third->y = left->y;
	}

	left_third_dist = ft_dist_t_dpos(*third, *left);
	right_third_dist = ft_dist_t_dpos(*third, *right);
	left_right_dist = ft_dist_t_dpos(*left, *right);
	//ft_find_angle_plan peut etre un probleme de precision car int et pas float en entrée...
	if (needed == 1)
		angle = ft_find_angle_plan(left_third_dist, left_right_dist, right_third_dist);
	else if (needed == 2)
		angle = ft_find_angle_plan(left_right_dist, right_third_dist, left_third_dist);
	else if (needed == 3)
		angle = ft_find_angle_plan(left_third_dist, right_third_dist, left_right_dist);
	return (angle);
}

int		ft_print_portal(t_main *s, int x, t_dpos player, t_dpos lwall, t_dpos rwall, t_dpos lplan, t_dpos rplan, t_int *vtx)
{
	(void)s;
	int		id_sector_out;
	int		angle_player;
	int		angle_portal_in;
	int		angle_portal_out;
	t_dpos	l_portal;
	t_dpos	r_portal;

	//trouver le sector dans lequel amene le portail et les coordonees des vtx du portal
	id_sector_out = vtx->sct_dest;
	l_portal.x = vtx->vtx_dest->ptr->x;
	l_portal.y = vtx->vtx_dest->ptr->y;
	r_portal.x = vtx->vtx_dest->next->ptr->x;
	r_portal.y = vtx->vtx_dest->next->ptr->y;

	//placer et orienter le fake joueur (modif player)
	angle_player = ft_find_angle_portal(&lwall, &rwall, &player, 1);

	//trouver langle du portail d'entree
	angle_portal_in = ft_find_angle_portal(&lwall, &rwall, NULL, 1);
	if (rwall.y > lwall.y)
		angle_portal_in += 180;

	//trouver langle du portail de sortie
	angle_portal_out = ft_find_angle_portal(&l_portal, &r_portal, NULL, 1);
	if (r_portal.y > l_portal.y)
		angle_portal_out += 180;

	printf("angle IN  (%d)\n",angle_portal_in);
	printf("angle OUT (%d)\n\n",angle_portal_out);

	double	pct_plan; // temporaire
	double	width_wall; // temporaire
	pct_plan = (ft_dist_t_dpos(lplan, rplan) * 100.0) / WIDTHPLAN; // temporaire
	width_wall = (WIDTH * pct_plan) / 100; // temporaire
	return ((int)width_wall + x);
}
