#include "doom.h"

int		in_field(t_main *s, t_dpos player, int dist)
{
	t_dpos	ctr_l;
	int  angle;
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
		// set_pixel(s->sdl->editor, BLUE, ret);
		  if ((ret.x >= (s->sprites.pos.x -10) && ret.x <= (s->sprites.pos.x +10))
		  	&& (ret.y >= (s->sprites.pos.y -10) && ret.y <= (s->sprites.pos.y +10)))
		  {
			//printf("ret= (%d,%d)\n",ret.x,ret.y);
			draw_anchor(s, ft_dpos_to_pos(s->sprites.pos), PINK);
			//set le sprite a 1
		 	return(1);
		 }
		 angle++;
	 }

	//printf("ret= (%d,%d)\n",ret.x,ret.y);
	return (0);
}


void 	draw_sprite(t_main *s)
{
	t_dpos distance;
	double dist;

	s->sprites.pos.x = 300;
	s->sprites.pos.y = 300;

	draw_anchor(s, ft_dpos_to_pos(s->sprites.pos), GREEN);

	distance.x =  s->sprites.pos.x - s->player.pos.x;
	distance.y =  s->sprites.pos.y - s->player.pos.y;
	dist = (distance.x * distance.x) + (distance.y * distance.y);
	dist = sqrt(dist);
	//printf("distance = (%f,%f)\n",distance.x,distance.y);
	//printf("\ndist = (%f)\n",dist);
	if (!(s->player.pos.x == s->sprites.pos.x && s->player.pos.y == s->sprites.pos.y)
		&& in_field(s,s->player.pos, dist) == 1)
		display_sprite(s,0,0,dist);

}


void display_sprite(t_main *s,int cor, int j, int dist)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	int value;
	int 		i;



	i = 0;
	value = 5000;//valuer pour grossir sprite
	coord.x = 0;
	coord.y = 0;
	wp = s->sprites.img;
	//coord.x = WIDTH / 2 - (wp->w / 2);
	while (i < (wp->w / dist) + value/ dist )
	{
		j = 0;//dont touch
		coord.x = i ;
		perx = (double)coord.x / (((double)wp->w / dist) + value/ dist);
		coord.x += (WIDTH /2) + (-cor);
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
