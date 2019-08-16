#include "doom.h"

void  	ft_zoom(t_main *s, t_pos mouse, int space)
{
	t_pos ori;
	t_pos p_ori;
	t_pos diff;
	t_dpos 		r_pos;
	t_editor 	*edi;

	edi = s->editor;
	ori.x = arround(s->editor->space, mouse.x - (s->editor->decal_x % s->editor->space));
	ori.y = arround(s->editor->space, mouse.y - (s->editor->decal_y % s->editor->space));
	p_ori.x = mouse.x - ori.x;
	p_ori.y = mouse.y - ori.y;
	ori = get_abs_pos(s,ori);
	r_pos.x = (double)ori.x + ((double)p_ori.x / edi->space);
	r_pos.y = (double)ori.y + ((double)p_ori.y / edi->space);
	s->player.pos.x -= s->editor->decal_x;
	s->player.pos.y -= s->editor->decal_y;
	s->player.pos.x /= (double)(s->editor->space);
	s->player.pos.y /= (double)(s->editor->space);
	s->editor->space += space;
	s->player.pos.x *= (double)(s->editor->space);
	s->player.pos.y *= (double)(s->editor->space);
	diff.x = r_pos.x * (-space);
	diff.y = r_pos.y * (-space);
	s->editor->decal_x += diff.x;
	s->editor->decal_y += diff.y;
	s->player.pos.x += s->editor->decal_x;
	s->player.pos.y += s->editor->decal_y;
}

void 	crouch(t_main *s, int press)
{
	struct timeval tv;
    long            curr_time;
	char            v0id[32];

	gettimeofday(&tv, (void *)v0id);
	curr_time = tv.tv_sec * 1000000 + tv.tv_usec;
	//printf("curr tine =%ld\n",curr_time);
	if (press == 1 && s->player.fin_time < curr_time)
	{
		s->player.fin_time = curr_time + 500000;
		s->player.tmp_time = curr_time;
	}
	if (s->player.fin_time > curr_time && s->player.tmp_time != curr_time && ((press == 1) && (s->player.i != 5)))
	{
		s->player.eyesight -=10;
		s->player.tmp_time++;
		s->player.i++;
	}
	if (s->player.eyesight < EYESIGHT && press == -1)
	{
		s->player.eyesight +=10;
		s->player.tmp_time++;
		s->player.i--;
	}
}

void 	jump(t_main *s, int press)
{
	struct timeval tv;
    long            curr_time;
	char            v0id[32];


	gettimeofday(&tv, (void *)v0id);
	curr_time = tv.tv_sec * 1000000 + tv.tv_usec;
	if (press == 1 && s->player.set_jump == 0)
	{
		s->player.j_fin_time = curr_time + 150000;
		s->player.set_jump = 1;
	}
	if (s->player.j_fin_time > curr_time && s->player.set_jump == 1)
		s->player.eyesight += 10;
	else if (s->player.eyesight > EYESIGHT && s->player.set_jump == 1)
		s->player.eyesight -= 10;
	if (s->player.eyesight == EYESIGHT)
		s->player.set_jump = 0;

}

void  	rotate_mouse(t_main *s)
{
	double angle;

	angle = s->player.angle + (-s->sdl->event.motion.xrel) * ROTATE_SPEED / 20 + 360;
	s->player.angle = (int)angle % 360;
	s->player.y_eye = (s->player.y_eye + (-s->sdl->event.motion.yrel) * ROTATE_SPEED / 3);
	if (s->player.y_eye > 1000)
		s->player.y_eye = 1000;
	else if (s->player.y_eye < -1000)
		s->player.y_eye = -1000;
}
