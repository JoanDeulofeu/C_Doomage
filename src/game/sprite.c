#include "doom.h"

void 	draw_sprite(t_main *s)
{
	t_dpos distance;
	t_dpos target;
	double dist;

	s->sprites.pos.x = 300;
	s->sprites.pos.y = 300;

	target.x = s->player.pos.x;
	target.y = s->player.pos.y;
	draw_anchor(s, ft_dpos_to_pos(s->sprites.pos), BLUE);

	distance.x =  s->sprites.pos.x - s->player.pos.x;
	distance.y =  s->sprites.pos.y - s->player.pos.y;
	//distance.x = 100;
	dist = (distance.x * distance.x) + (distance.y * distance.y);
	printf("\ndist = (%f)\n",dist);

	dist = sqrt(dist);
	printf("distance = (%f,%f)\n",distance.x,distance.y);
	printf("dist = (%f)\n",dist);



	target.x = cos(to_rad(s->player.angle));// speed;
	target.y = sin(to_rad(s->player.angle));// * speed;
	printf("target = (%f,%f)\n",target.x,target.y);

	display_sprite(s,0,0,dist);

}

void in_field(t_main *s)
{

}

void display_sprite(t_main *s, int i, int j, int dist)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	int value;


	value = 1000;
	coord.x = 0;
	coord.y = 0;
	wp = s->sprites.img;
	//coord.x = WIDTH / 2 - (wp->w / 2);

	while (i < (wp->w / dist) + value/ dist )
	{
		j = 0;//dont touch
		coord.x = i ;

		perx = (double)coord.x / (((double)wp->w / dist) + value/ dist);
		coord.x += WIDTH/2;

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
