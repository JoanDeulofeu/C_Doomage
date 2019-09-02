#include "doom.h"

int   check_exist(t_main *s,t_dpos target, int id)
{
  t_sprite *cur;
  int hitbox;


  hitbox = 20;
  cur = s->sprite;
  while (cur != NULL)
  {
    // value = HEIGHT / (cur->dist);
    if ((target.x >= (cur->pos.x -hitbox) && target.x <= (cur->pos.x + hitbox)) && (target.y >= (cur->pos.y -hitbox) && target.y <= (cur->pos.y + hitbox)) && cur->id != id)
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
	ctr_l.x = cur->pos.x + cos(to_rad(cur->s_angle)) * cur->dist;
	ctr_l.y = cur->pos.y - sin(to_rad(cur->s_angle)) * cur->dist;
	 while ( angle <= 360)
	 {
    ctr_l.x = cur->pos.x + cos(to_rad(cur->s_angle + angle)) * cur->dist;
   	ctr_l.y = cur->pos.y - sin(to_rad(cur->s_angle + angle)) * cur->dist;
    ret = ft_dpos_to_pos(ctr_l);
		 set_pixel(s->sdl->editor, BLUE, ret);
		  if ((ret.x >= (s->player.pos.x -HITBOX) && ret.x <= (s->player.pos.x +HITBOX)) //DEFINIR HITBOX
		  	&& (ret.y >= (s->player.pos.y -HITBOX) && ret.y <= (s->player.pos.y +HITBOX)))
		  {
        break ;
		 	}
		 angle+=0.1;
	 }
   return (angle);

}

void    sprite_move(t_main *s)
{
  t_sprite *cur;
  t_dpos	target;
	double	speed;
  double angle;

  cur = s->sprite;
	speed = 3;
  while (cur != NULL)
  {
    target.x = cur->pos.x;
  	target.y = cur->pos.y;
    angle = found_player(s,cur);
    target.x += cos(to_rad(angle)) * speed;
    target.y -= sin(to_rad(angle)) * speed;
    // printf("angle =%f\n",angle);
    // printf("cur->pos (%d,%d)\n",cur->pos.x,cur->pos.y);
    // printf("target (%f,%f)\n\n",target.x,target.y);
    if (ft_is_in_sector(s, ft_dpos_to_pos(target)) != 0 && cur->dist > 100 && check_exist(s,target,cur->id) == -1)
  	{
        cur->r_pos = get_abs_r_pos(s,ft_dpos_to_pos(target));
    }
    cur = cur->next;
  }
}
