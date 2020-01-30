#include "doom.h"

void	ft_set_time(t_main *s)
{
	s->time->time_ms = SDL_GetTicks();
	s->time->tmp_sec_fps = s->time->time_ms * 0.001;
	s->time->count_fps = 0;
	s->time->fps = 0;
	s->time->msg_tmp_ms = 0;
	s->time->explosion_ms = 0;
	s->time->crouch_ms = 0;
	s->time->jump_ms = 0;
}

void	ft_fps(t_main* s)
{
	int		time;

	time = s->time->time_ms * 0.001;
	if (time == s->time->tmp_sec_fps)
		s->time->count_fps++;
	else
	{
		s->time->tmp_sec_fps = time;
		s->time->fps = s->time->count_fps;
		s->time->count_fps = 0;
	}
}
