#include "doom.h"


int   check_exist_sprite(t_main *s, t_pos pos)
{
  t_sprite *cur;
//  double value;
  cur = s->sprite;

  while (cur != NULL)
  {
  //  value = (HEIGHT / (cur->dist)) * (cur->img->w/2);

    // if ((pos.x >= (cur->pos.x -value) && pos.x <= (cur->pos.x +value)) && (pos.y >= (cur->pos.y -value) && pos.y <= (cur->pos.y +value)))

    if ((pos.x >= (cur->pos.x -SPRITE_HITBOX) && pos.x <= (cur->pos.x +SPRITE_HITBOX)) && (pos.y >= (cur->pos.y -SPRITE_HITBOX) && pos.y <= (cur->pos.y +SPRITE_HITBOX)))
    {
      //printf("value =%d\n",value);
      return (cur->id);
    }
    cur = cur->next;
  }
  return (-1);
}
// (HEIGHT / (cur->dist)) * cur->img->w;


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
       break ;
    }
	}
}

// if ((id= found_id_sprite(s,ft_dpos_to_pos(s->player.pos),trace)) != -1)
