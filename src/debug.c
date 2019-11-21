#include "doom.h"

void print_wall_list(t_main *s)
{
  t_walls *tmp;
  int     i;

  tmp = s->walls;
  i = 1;
  while (tmp)
  {
	  if (tmp->wall_or_portal == 'p')
	  	printf("\033[33mPORTAIL\n");
	  if (tmp->wall_or_portal == 'w')
	  {
	      printf("\033[0m==========\n");
	      printf("MUR[%d]\n", i);
	      printf("----------\n");
	      printf("mur[%d].l_dist = %f\n", i, tmp->l_dist);
	      printf("mur[%d].b_dist = %f\n", i, tmp->b_dist);
	      printf("mur[%d].x = %d\n", i, tmp->x);
	      printf("mur[%d].player.x = %f\n", i, tmp->player.x);
	      printf("mur[%d].player.y = %f\n", i, tmp->player.y);
	      printf("mur[%d].left.x = %f\n", i, tmp->left.x);
	      printf("mur[%d].left.y = %f\n", i, tmp->left.y);
	      printf("mur[%d].right.x = %f\n", i, tmp->right.x);
	      printf("mur[%d].right.y = %f\n", i, tmp->right.y);
	      printf("mur[%d].l_plan.x = %f\n", i, tmp->l_plan.x);
	      printf("mur[%d].l_plan.y = %f\n", i, tmp->l_plan.y);
	      printf("mur[%d].r_plan.x = %f\n", i, tmp->r_plan.x);
	      printf("mur[%d].r_plan.y = %f\n\n", i, tmp->r_plan.y);
	      i++;
	  }

    tmp = tmp->next;
  }
}

void print_player_values(t_main *s)
{
	printf("r_pos = x(%f) y(%f)\n", s->player.r_pos.x, s->player.r_pos.y);
	printf("pos = x(%f) y(%f)\n", s->player.pos.x, s->player.pos.y);
	printf("m_pos = x(%f) y(%f)\n", s->player.m_pos.x, s->player.m_pos.y);
	printf("sector_id = %d\n", s->player.sector_id);
	printf("eyesight = %d\n", s->player.eyesight);
	printf("y_eye = %d\n", s->player.y_eye);
	printf("angle = %f\n", s->player.angle);
	printf("height = %d\n", s->player.height);
}
