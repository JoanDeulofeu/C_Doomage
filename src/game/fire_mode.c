#include "doom.h"


int   check_exist_sprite(t_main *s)
{
  t_sprite *cur;
  double value;
  t_dpos ret;
  double dist;
  int i;
  int j;
  int id;

  i = 0;
  id = -1;
  cur = s->sprite;
  dist = -1;
  while (cur != NULL)
  {
    value = (WIDTH / (cur->r_dist)) / 60;
    i = 0;
    while (i < (cur->img->w) * value)
    {
      j = 0;
      ret.x = i;
      ret.x += cur->angle * (double)(WIDTH/80) - ((cur->img->w *value)/2);
      while (j < (cur->img->h) * value)
  		{
        ret.y = j++;
  			ret.y += HEIGHT/2 + s->player.y_eye + s->player.eyesight - (((cur->img->h *value)/3.5));
        if ((int)ret.x == (WIDTH/2) && (int)ret.y == (HEIGHT/2))
        {
  		      if (cur->r_dist < dist || dist == -1)
  		      {
  			        dist = cur->r_dist;
  			        id = cur->id;
  		      }
        }
      }
      i++;
    }
    cur = cur->next;
  }
  return (id);
}

void give_damage(t_main *s, int id)
{
  t_sprite *cur;

  cur = s->sprite;
  while (cur != NULL)
  {
    if (cur->id == id && cur->life != 0)
    {
      cur->life = 0;
      cur->current = 0;
      set_img(s,cur,5,0);
      break ;
    }
    cur = cur->next;
  }
}

void	fire(t_main *s)
{
	// t_dpos	target;
  // t_pos trace;
  int i;
  int id;
  i = -1;

  id = -1;
  if ((id = check_exist_sprite(s)) != -1)
  {
    // printf("id =%d\n",id);
      give_damage(s,id);
    //  remove_sprite_by_id(s,id);
  }

}

// if ((id= found_id_sprite(s,ft_dpos_to_pos(s->player.pos),trace)) != -1)
