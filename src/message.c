#include "doom.h"

void	ft_init_msg(t_main *s)
{
	s->msg->r = 255;
	s->msg->g = 255;
	s->msg->b = 255;
	s->msg->duration = 1000;
	s->msg->message = NULL;
}

void	ft_create_message(t_main *s, int color, int duration, char *str)
{
	if (str == NULL)
		return ;
	if (color == 1) //vert
	{
		s->msg->r = 0;
		s->msg->g = 255;
		s->msg->b = 0;
	}
	else if (color == 2) //rouge
	{
		s->msg->r = 255;
		s->msg->g = 0;
		s->msg->b = 0;
	}
	if (duration > 999 && duration < 5001)
		s->msg->duration = duration;
	else
		s->msg->duration = 2000;
	s->msg->message = ft_strdup(str);
	s->time->msg_tmp_ms = s->time->time_ms;
}

void	ft_display_message(t_main *s)
{
	t_ttf		ttf;

	if (!s->msg->message)
		return ;
	if (s->time->msg_tmp_ms + s->msg->duration > s->time->time_ms)
	{
		ttf.r = s->msg->r;
		ttf.g = s->msg->g;
		ttf.b = s->msg->b;
		ttf.pos.x = 50;
		ttf.pos.y = 700;
		ttf.str = s->msg->message;
		ft_create_ttf(ttf, s, s->font->press_start25);
	}
	else
	{
		s->msg->r = 255;
		s->msg->g = 255;
		s->msg->b = 255;
		s->msg->duration = 1000;
		s->time->msg_tmp_ms = 0;
		ft_memdel((void **)&s->msg->message);
	}
}
