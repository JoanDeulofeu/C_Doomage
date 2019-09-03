#include "doom.h"
#define ANGLE_MAX 360

void  rand_move(t_main *s, t_sprite *cur)
{
  t_dpos	target;
  double	speed;
  double angle;

   // printf("rand\n\n");
  speed = 0.1;
    // printf("cur->angle =%f\n\n",cur->angle);
  target.x = cur->r_pos.x;
  target.y = cur->r_pos.y;
  //  angle = found_player(s,cur);
  target.x += cos(to_rad(cur->s_angle)) * speed;
  target.y -= sin(to_rad(cur->s_angle)) * speed;
    //target = get_px_r_pos(s,target);

  //   printf("cur->pos (%d,%d)\n",cur->pos.x,cur->pos.y);
    // printf("target (%f,%f)\n\n",target.x,target.y);
  if (ft_is_in_sector(s, get_px_r_pos(s,target)) != 0 && check_exist(s,target,cur->id) == -1)
  {
      cur->r_pos = target;
  }
  else
  {
    angle = (int)(rand() / (double)RAND_MAX * (ANGLE_MAX-1));
      //printf("angle =%f\n",angle);
    cur->s_angle = angle;
      // if (cur->angle > 360)
      //     cur->angle -= 360;
  }
}


int   check_exist(t_main *s,t_dpos target, int id)
{
  t_sprite *cur;
  double hitbox;


  hitbox = 0.5;
  cur = s->sprite;
  // if (id == found_closer(s) && cur->id != id)
  //   return (cur->id);
  while (cur != NULL)
  {
    //cur->id == found_closer(s)
    // value = HEIGHT / (cur->dist);

    if (((target.x >= (cur->r_pos.x -hitbox) && target.x <= (cur->r_pos.x + hitbox)) && (target.y >= (cur->r_pos.y -hitbox))
     && target.y <= (cur->r_pos.y + hitbox)) && cur->id != id)
    {
      return (cur->id);
    }

    cur = cur->next;
  }
  return (-1);
}



double  found_player(t_main *s,t_sprite *cur)
{
  t_dpos	ctr_l;
	double  angle;
	t_pos ret;

	angle = 0;
	ctr_l.x = cur->pos.x + cos(to_rad(angle)) * cur->dist;
	ctr_l.y = cur->pos.y - sin(to_rad(angle)) * cur->dist;
	 while ( angle <= 360)
	 {
    ctr_l.x = cur->pos.x + cos(to_rad(angle)) * cur->dist;
   	ctr_l.y = cur->pos.y - sin(to_rad(angle)) * cur->dist;
    ret = ft_dpos_to_pos(ctr_l);
	//	 set_pixel(s->sdl->editor, BLUE, ret);
		  if ((ret.x >= (s->player.pos.x -HITBOX) && ret.x <= (s->player.pos.x +HITBOX))
		  	&& (ret.y >= (s->player.pos.y -HITBOX) && ret.y <= (s->player.pos.y +HITBOX)))
		  {
        break ;
		 	}
		 angle+=0.1;
	 }
   return (angle);

}

void    sprite_move_on_player(t_main *s, t_sprite *cur)
{
  t_dpos	target;
	double	speed;
  double angle;

	speed = 0.1;
  target.x = cur->r_pos.x;
  target.y = cur->r_pos.y;
  angle = found_player(s,cur);
  target.x += cos(to_rad(angle)) * speed;
  target.y -= sin(to_rad(angle)) * speed;
    //target = get_px_r_pos(s,target);

  //  printf("angle =%f\n",angle);
    // printf("cur->dist =%f\n",cur->dist);
    //
    //  printf("cur->pos (%d,%d)\n",cur->pos.x,cur->pos.y);
    // printf("target (%f,%f)\n\n",target.x,target.y);
  if (ft_is_in_sector(s, get_px_r_pos(s,target)) != 0 && cur->dist > 50 && check_exist(s,target,cur->id) == -1)
  {
      cur->r_pos = target;//sget_abs_r_pos(s,ft_dpos_to_pos(target));
      //cur->s_angle = angle;
  }
}

void  ia(t_main*s)
{
  t_sprite *cur;

  cur = s->sprite;
  while (cur != NULL)
  {
    // printf("cur->id =%d\n",cur->id);
//    printf("cur->r_dist =%f\n",cur->r_dist);
    if (cur->r_dist <= 5)
    {
    //   printf("ok\n\n");
      sprite_move_on_player(s,cur);
    }
    else
      rand_move(s,cur);
    cur = cur->next;
  }

}
