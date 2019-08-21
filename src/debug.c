#include "doom.h"

void print_wall_list(t_main *s)
{
  t_walls *tmp;
  int     i;

  tmp = s->walls;
  i = 1;
  while (tmp)
  {
    printf("==========\n");
    printf("MUR[%d]\n", i);
    printf("----------\n");
    printf("mur[%d].distance = %f\n", i, tmp->distance);
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
    tmp = tmp->next;
  }
}
