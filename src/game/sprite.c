#include "doom.h"
#define HITBOX 2

double		in_field(t_main *s, t_dpos player, int dist)
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
		  if ((ret.x >= (s->sprites.pos.x -HITBOX) && ret.x <= (s->sprites.pos.x +HITBOX)) //DEFINIR HITBOX
		  	&& (ret.y >= (s->sprites.pos.y -HITBOX) && ret.y <= (s->sprites.pos.y +HITBOX)))
		  {
			//printf("ret= (%d,%d)\n",ret.x,ret.y);
			// printf("angle = %d\n",angle);

			draw_anchor(s, ft_dpos_to_pos(s->sprites.pos), PINK);
			//set le sprite a 1
		 	return(-angle);
		 }
		 angle+=1;
	 }

	//printf("ret= (%d,%d)\n",ret.x,ret.y);
	return (0);
}


void 	draw_sprite(t_main *s)
{
	t_dpos distance;
	double dist;
	double angle;

	angle = 0;
	s->sprites.pos.x = 400;
	s->sprites.pos.y = 200;

	draw_anchor(s, ft_dpos_to_pos(s->sprites.pos), GREEN);

	distance.x =  s->sprites.pos.x - s->player.pos.x;
	distance.y =  s->sprites.pos.y - s->player.pos.y;
	dist = (distance.x * distance.x) + (distance.y * distance.y);
	dist = sqrt(dist);
	//printf("distance = (%f,%f)\n",distance.x,distance.y);
	//printf("\ndist = (%f)\n",dist);
	if (!(s->player.pos.x == s->sprites.pos.x && s->player.pos.y == s->sprites.pos.y) && ((angle = in_field(s,s->player.pos, dist)) != 0))
	{
		angle += 40;
		//angle *= 10;
		//printf("angle = %f\n",angle);
		display_sprite(s,angle,0,dist);
	}
}


void display_sprite(t_main *s,int angle, int j, int dist)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	int value;
	int 		i;



	i = 0;
	value =9000;//valuer pour grossir sprite
	coord.x = 0;
	coord.y = 0;
	wp = s->sprites.img;
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
			coord.y += HEIGHT/2;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
}
