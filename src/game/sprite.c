#include "doom.h"

int 			calc_angle(double angle, int range)
{
	int ret;

	ret = (angle + range);
	if (ret > 360)
		ret = ret - 360;
	if (ret < 0)
		ret = 360 + ret;

	return (ret);
}

void 			set_img(t_main *s,t_sprite *cur, int id, int orientation)
{
	t_lsprite *lst;
	int i;
	int current;

	i = -1;
	current = 0;
	lst	= s->lsprite;
	while (++i != id && lst != NULL)
		lst = lst->next;
//	printf("id = %d\n",lst->id);
	// printf("current = %d\n",lst->anim->current);

	if (lst->anim != NULL)
	{
		cur->orientation = orientation;
		current = cur->anim->current;
		cur->anim = lst->anim;
		cur->anim->current = current;
		cur->img = cur->anim->image[cur->anim->current];
	}
}



void 			set_orientation(t_main *s, t_sprite *cur)
{
	int i;
	int angle;

	i = -1;
	while (++i != 360)
	{
		angle = calc_angle(cur->s_angle,i);
		if (angle == (int)s->player.angle)
			break ;
	}
	if ( (i >= 0 && i <= 22) || (i >= 337 && i <= 360))
		set_img(s,cur,1,0);
	if (i >= 23 && i <= 67)
		set_img(s,cur,3,1);
	if (i >= 68 && i <= 112)
		set_img(s,cur,2,1);
	if (i >= 113 && i <= 157)
		set_img(s,cur,4,1);
	if (i >= 158 && i <= 202)
		set_img(s,cur,0,0);
	if (i >= 203 && i <= 247)
		set_img(s,cur,4,0);
	if (i >= 248 && i <= 292)
		set_img(s,cur,2,0);
	if (i >= 293 && i <= 337)
		set_img(s,cur,3,0);



}

void 			sprite_orientation(t_main *s)
{
		t_sprite *cur;

		cur = s->sprite;
		while (cur != NULL)
		{
			// if (cur->anim != NULL)
				set_orientation(s,cur);
			cur = cur->next;
		}
}

double		in_field(t_main *s, t_dpos player, int dist, t_sprite *cur)
{
	t_dpos	ctr_l;
	double  angle;
	t_pos ret;

	angle = -50;
	ctr_l.x = player.x + cos(to_rad(s->player.angle + angle)) * dist;
	ctr_l.y = player.y - sin(to_rad(s->player.angle + angle)) * dist;
//	draw_anchor(s, ft_dpos_to_pos(ctr_l), GREEN);
	 while ( angle <= 50)
	 {
		 ctr_l.x = player.x + cos(to_rad(s->player.angle+ angle)) * dist;
	 	 ctr_l.y = player.y - sin(to_rad(s->player.angle+ angle)) * dist;
		 ret = ft_dpos_to_pos(ctr_l);
	//	 set_pixel(s->sdl->editor, BLUE, ret);
		  if ((ret.x >= (cur->pos.x -HITBOX) && ret.x <= (cur->pos.x +HITBOX)) //DEFINIR HITBOX
		  	&& (ret.y >= (cur->pos.y -HITBOX) && ret.y <= (cur->pos.y +HITBOX)))
		  {
				//draw_anchor(s,cur->pos, PINK);
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
	if (cur->orientation == 0)
		display_sprite(s,cur->angle,cur);
	else
		display_sprite_inverse(s,cur->angle,cur);
}

int 	found_closer(t_main *s)
{
	t_sprite *cur;
	int id;
	int dist;

	cur = s->sprite;
	id = -1;
	dist = MAX_SPRITE_DIST;
	while (cur != NULL)
	{
		if (cur->dist < dist)// && cur->set == 1)
		{
			dist = cur->dist;
			id = cur->id;
		}
		cur = cur->next;
	}
	return (id);
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

int 	check_is_on_sector(t_main *s,t_sprite *cur)
{
		if (ft_is_in_sector(s, get_px_r_pos(s,cur->r_pos)))
		 	return (1);
		return (-1);
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

	dist = 0;
	if (s->sprite == NULL)
		return ;
	cur = s->sprite;
	while(cur != NULL)
	{
		if (check_is_on_sector(s,cur) == 1)
		{
			if (!(s->player.pos.x == cur->pos.x && s->player.pos.y == cur->pos.y) && ((angle = in_field(s,s->player.pos, cur->dist, cur)) != 0) && cur->dist < MAX_SPRITE_DIST)
			{
				cur->set = 1;
				cur->angle = angle+40;
			}
		}
		cur = cur->next;
	}
	found_sprite(s);
}

void display_sprite(t_main *s,double angle, t_sprite *cur)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	double value;
	int 		i;
	int j;

	wp = cur->img;
	i = 0;

	value = ( HEIGHT / (cur->r_dist)) /60;

	coord.x = 0;
	coord.y = 0;
	// printf("w = %d\n",wp->w);
	// printf("h = %d\n",wp->h);
	// printf("value = %f\n",value);
	//  printf("angle = %f\n",angle);
	// printf("cur->dist = %f\n",cur->r_dist);
	// printf("dist = %d\n",dist);
	while (i < (wp->w) * value)
	{
		j = 0;
		coord.x = i;
		perx = (double)i/ (((double)wp->w) * value);
		coord.x += angle * (double)(WIDTH/80) - ((wp->w *value) /2);
		// printf("coord (%d,%d)\n\n",coord.x,coord.y);

		while (j < (wp->h) * value)
		{
			coord.y = j++;
			pery = (double)j / (((double)wp->h) * value);
			coord.y += HEIGHT/2 + s->player.y_eye + s->player.eyesight - (((wp->h *value))/3.5);
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 65280)
				set_pixel(s->sdl->game, wp->tex[px], coord);
		}
		i++;
	}
}


void display_sprite_inverse(t_main *s,double angle, t_sprite *cur)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
	double value;
	int 		i;
	int j;

	wp = cur->img;
	i = 0;

	value = ( HEIGHT / (cur->r_dist)) /60;

	coord.x = 0;
	coord.y = 0;
	  // printf("value = %f\n",value);
	 // printf("angle = %f\n",angle);
	 // printf("cur->dist = %f\n",cur->dist);
	// printf("dist = %d\n",dist);
	while (i < (wp->w) * value)
	{
		j = 0;
		coord.x = i;
		perx = (double)i/ (((double)wp->w) * value);
		coord.x += angle * (double)(WIDTH/80) - ((wp->w *value)/2);
		// printf("coord (%d,%d)\n\n",coord.x,coord.y);

		while (j < (wp->h) * value)
		{
			coord.y = j;
			pery = (double)j / (((double)wp->h) * value);
			coord.y += HEIGHT/2 + s->player.y_eye + s->player.eyesight - (((wp->h *value)/3.5));
			px = (int)(pery * (double)wp->h) * wp->w - (int)(perx * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 65280)
				set_pixel(s->sdl->game, wp->tex[px], coord);
			j++;
		}
		i++;
	}
}
