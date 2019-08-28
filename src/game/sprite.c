#include "doom.h"
#define HITBOX 2

double		in_field(t_main *s, t_dpos player, int dist, t_sprite *cur)
{
	t_dpos	ctr_l;
	double  angle;
	t_pos ret;

	angle = -40;
	ctr_l.x = player.x + cos(to_rad(s->player.angle + angle)) * dist;
	ctr_l.y = player.y - sin(to_rad(s->player.angle + angle)) * dist;
	//draw_anchor(s, ft_dpos_to_pos(ctr_l), GREEN);
	 while ( angle <=  40)
	 {
		 ctr_l.x = player.x + cos(to_rad(s->player.angle+ angle)) * dist;
	 	 ctr_l.y = player.y - sin(to_rad(s->player.angle+ angle)) * dist;
		 ret = ft_dpos_to_pos(ctr_l);
		 set_pixel(s->sdl->editor, BLUE, ret);
		  if ((ret.x >= (cur->pos.x -HITBOX) && ret.x <= (cur->pos.x +HITBOX)) //DEFINIR HITBOX
		  	&& (ret.y >= (cur->pos.y -HITBOX) && ret.y <= (cur->pos.y +HITBOX)))
		  {
				draw_anchor(s,cur->pos, PINK);
		 		return(-angle);
		 	}
		 angle+=0.1;
	 }
	return (0);
}

void 	display_by_id(t_main *s, int id)
{
	t_sprite *cur;

	cur = s->sprite;
	while (cur->id != id && cur->next != NULL)
		cur = cur->next;
	cur->set = 0;
	display_sprite(s,cur->angle,cur->dist,cur);
}

int 	found_farther(t_main *s)
{
	t_sprite *cur;
	int id;
	int dist;

	cur = s->sprite;
	id = -1;
	dist = 0;
	while (cur != NULL)
	{
		if (cur->dist > dist && cur->set == 1)
		{
			dist = cur->dist;
			id = cur->id;
		}
		cur = cur->next;
	}
	return (id);
}

void  found_sprite(t_main *s)
{
	t_sprite *cur;
	int 			id;
	int 			dist;
	int 			i;

	id = -1;
	dist = 0;
	i = 0;
	cur = s->sprite;
	while (cur != NULL)
	{
		if (cur->set == 1)
			i++;
		cur = cur->next;
	}
	cur = s->sprite;
	while (i != 0 && cur != NULL)
	{
		if ((id = found_farther(s)) != -1)
		{
			display_by_id(s,id);
			i--;
		}
		cur = cur->next;
	}
}

void 	draw_sprite(t_main *s)
{
	t_sprite *cur;
	double dist;
	double angle;
	//int id;

	//id = -1;
	dist = 0;
	cur = s->sprite;
	while(cur != NULL)
	{
		if (!(s->player.pos.x == cur->pos.x && s->player.pos.y == cur->pos.y) && ((angle = in_field(s,s->player.pos, cur->dist, cur)) != 0) && cur->dist < MAX_SPRITE_DIST)
		{
			cur->set = 1;
			cur->angle = angle + 40;
			// display_sprite(s,angle,cur->dist,cur);
		}
		cur = cur->next;
	}

	found_sprite(s);
}

void display_sprite(t_main *s,int angle, int dist, t_sprite *cur)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	double value;
	int 		i;
	int j;


	i = 0;
	value =200/(cur->dist /2 );//valuer pour grossir sprite
	coord.x = 0;
	coord.y = 0;

	wp = cur->img;
	// printf("value = %f\n",value);
	// printf("cur->dist = %f\n",cur->dist);
	// printf("dist = %d\n",dist);
	while (i < (wp->w) * value)
	{
		j = 0;
		coord.x = i ;
		perx = (double)coord.x / (((double)wp->w) * value);// / dist));// + value/ dist);
		coord.x += angle * (WIDTH/80);
		while (j < (wp->h)* value)// / dist))
		{
			coord.y = j++;
			pery = (double)coord.y / (((double)wp->h) * value);// / dist));// + value/ dist);
			coord.y += HEIGHT/2 + s->player.y_eye + s->player.eyesight;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
			//printf("tx = %d\n",wp->tex[px]);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 65280)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
}
