#include "doom.h"

void	*ft_assign_wall(void *s_void)
{
	// printf("---entree dans ft_assign_wall---\n");
	static pthread_mutex_t	mutex_stock = PTHREAD_MUTEX_INITIALIZER;
	t_main					*s;
	t_walls					*wall;
	t_walls					*wall_tmp;
	int						found;
	int						secur;

	s = (t_main *)s_void;
	pthread_mutex_lock(&mutex_stock);
	wall = s->walls;
	wall_tmp = NULL;
	found = 1;
	secur = 0;
	while (wall && wall->occuped != 0) //javance jusqua trouver un mur non occupé
	{
		// printf("-wall_id %d ", wall->id);
		wall = wall->next;
	}
	// printf("\n");
	if (!wall)
	{
		// printf("\033[31msortie prematuré\033[0m\n");
		pthread_mutex_unlock(&mutex_stock);
		pthread_exit(NULL);
	}
	// printf("WALL imprimé %d\n", wall->id);
	pthread_mutex_unlock(&mutex_stock);
	if (wall != s->walls)
		while (found && !wall_tmp)
		{
			// printf("WALL ID %d\n", wall->id);
			secur++;
			wall_tmp = s->walls;
			while (wall_tmp)
			{
				//si les murs n'interfere pas entre eux et que wall_tmp nest pas occupé
				if (((wall->x + wall->screen_width_wall < wall_tmp->x) || (wall->x > wall_tmp->x + wall_tmp->screen_width_wall)) && wall_tmp->occuped != 1)
					found = 0;
				else
					found = 1;
				wall_tmp = wall_tmp->next;
			}
			// if (found)
			// 	printf("Wall %d en attente\n", wall->id);
			if (secur == 100000)
			{
				// printf("\n\033[31msortie prematuré 2\033[0m\n");
				// exit(0);
				pthread_mutex_unlock(&mutex_stock);
				pthread_exit(NULL);
			}
		}
	wall->occuped = 1; //mur en cours d'impression
	ft_print_wall(s, wall);
	wall->occuped = 2; //mur fini d'imprimé
	pthread_exit(NULL);
	// printf("---sortie de ft_assign_wall---\n");
}

void	ft_fucking_threading(t_main *s)
{
	t_walls	*wall;


	s->pthread = -1;
	wall = s->walls;
	while (wall)
	{
		// printf("wall_id %d \n", wall->id);
		// printf("limit left %d      limit right %d\n", wall->x, wall->x + wall->screen_width_wall);
		if (wall->id > s->pthread)
			s->pthread = wall->id;
		wall = wall->next;
	}
	// printf("fini---------------------\n");


	// printf("\033[33m-entree dans ft_fucking_threading-\033[0m\n");
	pthread_t	thread[s->pthread];
	// printf("nombre de thread  =  %d\n", s->pthread);
	int			i;

	i = 0;
	// s->pthread = 8;
	while (i < s->pthread)
	{
		if (pthread_create(&thread[i++], NULL, ft_assign_wall, (void *)(s)) == -1)
			perror("thread creation");
	}
	i = 0;
	while (i < s->pthread)
		if (pthread_join(thread[i++], NULL) == -1)
			perror("thread join");
	// printf("-sortie de ft_fucking_threading-\n");
}

/*
verifier que toutes les variables ne soit pas modifier par les thread en meme temps,
notamment celle qui definissent les quatres coins dun mur.
verifier quil ny a pas de double mur quand il doit ny en avoir quun
mettre la texture sous mutex
*/
