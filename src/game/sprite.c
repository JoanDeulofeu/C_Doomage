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
			//printf("ret= (%d,%d)\n",ret.x,ret.y);
			//printf("angle = %f\n",angle);

				draw_anchor(s,cur->pos, PINK);
			//set le sprite a 1
		 		return(-angle);
		 	}
		 angle+=0.1;
	 }

	//printf("ret= (%d,%d)\n",ret.x,ret.y);
	return (0);
}


void 	draw_sprite(t_main *s)
{
	t_dpos distance;
	t_sprite *cur;
	double dist;
	double angle;

	cur = s->sprite;
	draw_anchor(s,s->sprite->pos, GREEN);
	draw_anchor(s, s->sprite->next->pos, GREEN);

	//draw_anchor(s, ft_dpos_to_pos(s->sprite->pos), GREEN);
//	draw_anchor(s, ft_dpos_to_pos(s->sprite->next->pos), GREEN);
	while(cur != NULL)
	{
	//	printf("cur.pos = (%f,%f)\n",cur->pos.x,cur->pos.y);

		distance.x =  cur->pos.x - s->player.pos.x;
		distance.y =  cur->pos.y - s->player.pos.y;
		dist = (distance.x * distance.x) + (distance.y * distance.y);
		dist = sqrt(dist);
	//printf("distance = (%f,%f)\n",distance.x,distance.y);
	//printf("\ndist = (%f)\n",dist);

		if (!(s->player.pos.x == cur->pos.x && s->player.pos.y == cur->pos.y) && ((angle = in_field(s,s->player.pos, dist, cur)) != 0))
		{
			angle += 40;
		//ßm	printf("angle = %f\n", angle);
			display_sprite(s,angle,dist,cur);
		}
		cur = cur->next;
	}

}


void display_sprite(t_main *s,int angle, int dist, t_sprite *cur)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	int value;
	int 		i;
	int j;


	i = 0;
	value =9000;//valuer pour grossir sprite
	coord.x = 0;
	coord.y = 0;

	wp = cur->img;
	// printf("\n\n\nok\n\n");

	//coord.x = WIDTH / 2 - (wp->w / 2);
	while (i < (wp->w / dist) + value/ dist )
	{
		j = 0;
		coord.x = i ;
		perx = (double)coord.x / (((double)wp->w / dist) + value/ dist);
		coord.x += angle * (WIDTH/80);
		while (j < (wp->h / dist) + value/ dist)
		{
			coord.y = j++;
			pery = (double)coord.y / (((double)wp->h / dist) + value/ dist);
			coord.y += HEIGHT/2 + s->player.y_eye + s->player.eyesight;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
}
