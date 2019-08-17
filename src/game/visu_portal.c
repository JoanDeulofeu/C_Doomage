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
double		ft_find_angle_portal(t_dpos *left, t_dpos *right, t_dpos *third, int needed)
{
	//third est le troisieme point pour trouver l'angle si besoin;
	double	angle = 0;
	double	left_right_dist;
	double	right_third_dist;
	double	left_third_dist;
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
	// (void)s;
	int			id_sector_out;
	double		angle_player;
	double		angle_portal_in;
	double		angle_portal_out;
	t_dpos		l_portal;
	t_dpos		r_portal;
	t_pos		fake_player;
	double		dist_player;

	//trouver le sector dans lequel amene le portail et les coordonees des vtx du portal
	id_sector_out = vtx->sct_dest;
	l_portal.x = vtx->vtx_dest->ptr->x * METRE;
	l_portal.y = vtx->vtx_dest->ptr->y * METRE;
	r_portal.x = vtx->vtx_dest->next->ptr->x * METRE;
	r_portal.y = vtx->vtx_dest->next->ptr->y * METRE;

	//placer et orienter le fake joueur (modif player)
	angle_player = ft_find_angle_portal(&lwall, &rwall, &player, 1);

	//trouver langle du portail d'entree
	angle_portal_in = ft_find_angle_portal(&lwall, &rwall, NULL, 1);
	if (rwall.y > lwall.y)
		angle_portal_in = 180 + (180 - angle_portal_in);

	//trouver langle du portail de sortie
	angle_portal_out = ft_find_angle_portal(&l_portal, &r_portal, NULL, 1);
	if (r_portal.y > l_portal.y)
		angle_portal_out = 180 + (180 - angle_portal_out);

	// printf("angle PLAYER  (%f)\n",angle_player);
	// printf("angle IN      (%f)\n",angle_portal_in);
	// printf("angle OUT     (%f)\n\n",angle_portal_out);

	//application de la difference d'angle des deux portail sur angle player
	angle_player = angle_portal_in - angle_player - fabs(angle_portal_in - angle_portal_out);

	// printf("New Angle Player (%f)\n\n",angle_player);

	//trouver la distance entre joueur et le point gauche du portail initial
	dist_player = ft_dist_t_dpos(player, lwall);

	//Tentative de placement du fake player
	fake_player.x = r_portal.x + cos(to_rad(angle_player)) * dist_player + s->editor->decal_x;
	fake_player.y = r_portal.y - sin(to_rad(angle_player)) * dist_player + s->editor->decal_y;
	//ATTENTION !!!! jai ajouter le decal_x pour que le point saffiche a lecran pour mes tests.

	// printf("coord r_portal (%.1f,%.1f)\n\n",r_portal.x, r_portal.y);
	// printf("coord player (%d,%d)\n\n",fake_player.x, fake_player.y);
	draw_anchor(s, fake_player, 0xfa00ffff); //juste pour tester la pos du fake_player

	/*
	biensur il faut retirer le decal_x pour faire les calculs suivants.
	sinon la position du joueur DEVRAIT etre bonne. Faut test si ca marche
	toujours avec des angles differents.

	jai laissé mes printfs si jamais tu veux comprendre ce que je fais mais tu
	peux les supprimer sil te gene.
	*/










	double	pct_plan; // temporaire
	double	width_wall; // temporaire
	pct_plan = (ft_dist_t_dpos(lplan, rplan) * 100.0) / WIDTHPLAN; // temporaire
	width_wall = (WIDTH * pct_plan) / 100; // temporaire
	return ((int)width_wall + x);
}
