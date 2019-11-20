#include "doom.h"

void		teleport_player(t_main *s, const unsigned char *keys)
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
	// printf("x = %f, y = %f\n", s->col_pos.x, s->col_pos.y);
	player_haut = s->col_pos;
	player_bas = s->col_pos;
	//col_pos est calcule dans player.c, quand le joueur bouge
	// printf("hey\n\n\n");
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
		printf("true\n");
		if (wall->next->vtx_dest != NULL) // Au cas où find intersection ne renvoie pas le bon mur, on check lequel a coté est un portail
		{
			printf("vertex suivant");
			wall = wall->next;
		}
		else if (wall->prev->vtx_dest != NULL)
		{
			printf("vertex precedent\n");
			wall = wall->prev;
		}
		else
			printf("fuck...\n");
	}
	if (wall == NULL)
		printf("ptr_id = %d\n", ptr_id);
	//On teleporte le player
	// printf("wall->ptr->id = %d\n", wall->ptr->id);
	// printf("s->col_pos.x = %f, s->col_pos.y = %f, player.r_pos.x = %f\nplayer.r_pos.y = %f\n", s->col_pos.x, s->col_pos.y, s->player.r_pos.x, s->player.r_pos.y);
	s->player.m_pos = ft_get_fake_player(s, s->col_pos, wall, &s->player.angle);
	s->player.r_pos.x = s->player.m_pos.x / METRE;
	s->player.r_pos.y = s->player.m_pos.y / METRE;
	set_player(s);
	// printf("s->col_pos.x = %f, s->col_pos.y = %f\n", s->col_pos.x, s->col_pos.y);
	// printf("Nouveau ==> player.r_pos.x = %f\nNouveau ==> player.r_pos.y = %f\n\n\n", s->player.r_pos.x, s->player.r_pos.y);
	//changer secteur en fonction de la teleportation
	s->player.sector_id = wall->sct_dest;
	s->portal_nb = 0;
	// printf("test\n");
	// if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
	// 	s->player.pos = get_direction(s, keys, 1, s->player.pos);
	//On le bouge legerement et on verifie qu'il n'est pas coince
	// if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
	// 	ft_move_player(s, keys, 1);
	handle_sector_zero(s);
	// printf("sortie\n");
}
