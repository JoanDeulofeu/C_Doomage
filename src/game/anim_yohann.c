#include "doom.h"

void 	select_anim(t_main *s, t_sprite *sprite)
{
	t_walls 	*wall;
	double		angle;
	t_dpos		point;

	wall = s->walls;
	while (wall->sct_id != sprite->sct_id)
		wall = wall->next;
	point.x = sprite->m_pos.x + cos(to_rad(sprite->s_angle)) * 2;
	point.y = sprite->m_pos.y - sin(to_rad(sprite->s_angle)) * 2;
	angle = ft_find_angle_portal(&sprite->m_pos, &wall->player, &point, 1);
	if (wall->player.y > sprite->m_pos.y)
		angle = 180 + (180 - angle);
	if (angle > 202)
		sprite->inverse = 1;
	else
		sprite->inverse = 0;
	if (angle > 337 || angle <= 22)
		sprite->anim = s->stormtrooper.face;
	else if ((angle > 22 && angle <= 67) || (angle > 292 && angle <= 337))
		sprite->anim = s->stormtrooper.prof_face;
	else if ((angle > 67 && angle <= 112) || (angle > 247 && angle <= 292))
		sprite->anim = s->stormtrooper.prof;
	else if ((angle > 112 && angle <= 157) || (angle > 202 && angle <= 247))
		sprite->anim = s->stormtrooper.prof_back;
	else if (angle > 157 && angle <= 202)
		sprite->anim = s->stormtrooper.back;



	// angle = (angle - (int)sprite->s_angle) % 360 ;
	// if (angle > 215 && angle <= 250)
	// 	sprite->anim = s->stormtrooper.face;
	// else if (angle > 45 && angle <= 135)
	// 	sprite->anim = s->stormtrooper.prof;
	// else
	// 	sprite->anim = s->stormtrooper.back;
	// printf("angle = %f\n",angle);
	// else if (angle > 45 && angle <= 90)
	// 	sprite->anim = s->stormtrooper.prof;
	// else if (angle == 2)
	// 	sprite->anim = s->stormtrooper.prof_back;
	// else if (angle == 2)
	// 	sprite->anim = s->stormtrooper.prof_face;
}
