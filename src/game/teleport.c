#include "doom.h"

int		ft_check_high_coll(t_main *s, t_int *wall)
{
	t_sector	*sct_player;
	t_sector	*sct_dest;

	sct_player = get_sector_by_id(s, s->player.sector_id);
	sct_dest = get_sector_by_id(s, wall->sct_dest);
	// printf("if %.2f < %d\n", s->player.foot_height, sct_dest->floor);
	if (s->player.foot_height < (double)sct_dest->floor)
		return (0);
	// printf("%d > %.1f + %.1f\n", sct_dest->ceiling, s->player.foot_height ,s->player.size);
	if ((double)sct_dest->ceiling < s->player.foot_height + s->player.size)
		return (0);
	// printf("TP ACCEPTER\n");
	return (1);
}

void	teleport_player(t_main *s, const unsigned char *keys)
{
	t_dpos	player_haut;
	t_dpos	player_bas;
	int		ptr_id;
	int		sct_id;
	t_int	*wall;
	int		nb;

	(void)keys;
	// printf("ENTREE\n");
	nb = 10;
	ptr_id = 0;
	player_haut = s->col_pos;
	player_bas = s->col_pos;
	//col_pos est calcule dans player.c, quand le joueur bouge
	player_haut.y += nb;
	player_bas.y -= nb;
	sct_id = s->player.sector_id;
	if (sct_id == 0)
		printf ("FUUUUUUUUU\n");
	//on trouve le portail que touche col_pos
	while (ptr_id == 0 && nb < 5000)
	{
		// printf ("test\n");
		player_haut = s->col_pos;
		player_bas = s->col_pos;
		player_haut.y += nb;
		player_bas.y -= nb;
		if ((ptr_id = ft_find_wall2(s, player_bas, player_haut, BLUE, sct_id)) == 0)
		{
			player_haut = s->col_pos;
			player_bas = s->col_pos;
			player_haut.x += nb;
			player_bas.x -= nb;
			if ((ptr_id = ft_find_wall2(s, player_bas, player_haut, BLUE, sct_id)) == 0)
			{
				player_haut.y += nb;
				player_bas.y -= nb;
				if ((ptr_id = ft_find_wall2(s, player_bas, player_haut, BLUE, sct_id)) == 0)
				{
					player_haut.x += nb * 2;
					player_bas.x -= nb * 2;
					ptr_id = ft_find_wall2(s, player_bas, player_haut, BLUE, sct_id);
				}
			}
		}
		nb++;
		// printf("teleport_player : nb = %d\n", nb);
	}
	if (ptr_id == 0)
	{
		handle_sector_zero(s);
		return ;
	}
	else
		// printf("point de teleport trouvé !\n");
	wall = get_t_int_by_vertex_id(get_sector_by_id(s, sct_id)->vertex, ptr_id);
	if (wall->vtx_dest == NULL)
	{
		// printf("true\n");
		if (wall->next->vtx_dest != NULL) // Au cas où find intersection ne renvoie pas le bon mur, on check lequel a coté est un portail
		{
			// printf("vertex suivant");
			wall = wall->next;
		}
		else if (wall->prev->vtx_dest != NULL)
		{
			// printf("vertex precedent\n");
			wall = wall->prev;
		}
		else
			printf("fuck...\n");
	}
	if (wall == NULL)
		printf("ptr_id = %d\n", ptr_id);
	if (ft_check_high_coll(s, wall) == 0)
	{
		// printf("TP INTERDIT\n");
		return ;
	}
	s->player.m_pos = ft_get_fake_player(s, s->col_pos, wall, &s->player.angle, s->player.angle);
	s->player.r_pos.x = s->player.m_pos.x / METRE;
	s->player.r_pos.y = s->player.m_pos.y / METRE;
	set_player(s);
	s->player.sector_id = wall->sct_dest;
	s->portal_nb = 0;
	handle_sector_zero(s);
}
