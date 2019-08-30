#include "doom.h"

t_dpos	get_sprite_direction(t_main *s, const Uint8 *keys, double speed, t_dpos target)
{
	if (keys[UP])
	{
		target.x += cos(to_rad(s->player.angle)) * speed;
		target.y -= sin(to_rad(s->player.angle)) * speed;
	}
	if (keys[DOWN])
	{
		target.x -= cos(to_rad(s->player.angle * -1)) * speed;
		target.y -= sin(to_rad(s->player.angle * -1)) * speed;
	}
	if (keys[LEFT])
	{
		target.x += cos(to_rad(s->player.angle + 90)) * speed;
		target.y -= sin(to_rad(s->player.angle + 90)) * speed;
	}
	if (keys[RIGHT])
	{
		target.x += cos(to_rad(s->player.angle - 90)) * speed;
		target.y -= sin(to_rad(s->player.angle - 90)) * speed;
	}
	return (target);
}


void    sprite_move(t_main *s)
{
  t_sprite *cur;
  t_dpos	target;
  t_pos	  trace;
	double	speed;
  int     move_speed;

  cur = s->sprite;
  move_speed = 4;
	speed = move_speed * 0.5;
	speed /= 1.5;
  while (cur != NULL)
  {
    target.x = cur->pos.x;
  	target.y = cur->pos.y;

    target.x += s->player.pos.x/100;  //TODO doit se deplacer vers le joueur
    target.y += s->player.pos.y/100;

    printf("cur->pos (%d,%d)\n",cur->pos.x,cur->pos.y);
    printf("target (%f,%f)\n\n",target.x,target.y);
    if (ft_is_in_sector(s, ft_dpos_to_pos(target)) != 0)
  	{
      cur->r_pos = get_abs_r_pos(s,ft_dpos_to_pos(target));
  	}
    cur = cur->next;
  }
}
