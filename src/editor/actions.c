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
		s->player.eyesight -=1;
		s->player.tmp_time++;
		s->player.i++;
	}
	if (s->player.eyesight != EYESIGHT && press == -1)
	{
		s->player.eyesight +=1;
		s->player.tmp_time++;
		s->player.i--;
	}
}

void 	jump(t_main *s)
{
	(void)s;
	//s->player.eyesight +=1;


}


void  	rotate_mouse(t_main *s, t_pos mouse, t_pos mouse_save)
{
	double angle;
	int dir;

	if (mouse.x >= mouse_save.x && mouse.x != 0)
		dir = 1;
	else
		dir = -1;
	angle = s->player.angle + dir * ROTATE_SPEED / 10 + 360;
	s->player.angle = (int)angle % 360;
	if (mouse.y >= mouse_save.y && mouse.y != 0)
		dir = 1;
	else
		dir = -1;
	//s->player.eyesight += 1;




}
