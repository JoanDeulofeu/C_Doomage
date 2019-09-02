#include "doom.h"


int   check_exist_sprite(t_main *s, t_pos pos)
{
  t_sprite *cur;
  double value;
  double ret;
  double dist;
  int i;
  int id;

  i = 0;
  id = -1;
  cur = s->sprite;
  dist = -1;
  while (cur != NULL)
  {
    // value = HEIGHT / (cur->dist);
    value = (HEIGHT / (cur->r_dist)) / 30;

    i = 0;
    while (i < (cur->img->w) * value)
    {
      ret = i;
      ret += cur->angle * (double)(WIDTH/80) - ((cur->img->w *value)/2);
      // printf("ret =%d\n",(int)ret);
      // printf("save =%d\n",(int)save);
      if ((int)ret == (WIDTH/2) )
      {
		  if (cur->r_dist < dist || dist == -1)
		  {
			  dist = cur->r_dist;
			  id = cur->id;
		  }
        // return (cur->id);
      }
      i++;
    }
    cur = cur->next;
  }
  return (id);
}


void	fire(t_main *s)
{
	t_dpos	target;
  t_pos trace;
  int i;
  t_pos start;
  t_pos end;
  int id;
  i = -1;

  id = -1;
	target.x = s->player.pos.x;
	target.y = s->player.pos.y;
	//printf("sector = %d\n",ft_is_in_sector(s, ft_dpos_to_pos(target)));
	while ( ++i != 1000 &&ft_is_in_sector(s, ft_dpos_to_pos(target)) != 0)
	{
    target.x += cos(to_rad(s->player.angle));// * speed;
    target.y -= sin(to_rad(s->player.angle));// * speed;
	trace.x = target.x;
	trace.y = target.y;
    set_pixel(s->sdl->editor, BLUE, trace);
    if ((id= check_exist_sprite(s,trace)) != -1)
    {
       remove_sprite_by_id(s,id);
       // printf("ok\n");
       break ;
    }
	}
}

// if ((id= found_id_sprite(s,ft_dpos_to_pos(s->player.pos),trace)) != -1)
