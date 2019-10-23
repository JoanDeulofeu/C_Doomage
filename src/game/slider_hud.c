#include "doom.h"

void		set_pixel_slider(t_texture *text, Uint32 color, int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		text->content[x + y * WIDTH] = color;
	}
}

void		draw_slider(t_main *s, t_slider slider)
{
	int			tmp;
	float		diff;

	tmp = slider.start.x;
	while (slider.start.y < slider.end.y)
	{
		slider.start.x = tmp;
		diff = slider.end.x - slider.start.x;
		while (slider.start.x < slider.end.x)
		{
			if (((1.0f - ((slider.end.x - slider.start.x) / diff)) * 100)
			< slider.value)
				set_pixel_slider(s->sdl->game, slider.color_one,
					slider.start.x, slider.start.y);
			else
				set_pixel_slider(s->sdl->game, slider.color_two,
					slider.start.x, slider.start.y);
			++slider.start.x;
		}
		++slider.start.y;
	}
}

void		print_hp(t_main *s)
{
	s->slider.start.x = 750;
	s->slider.end.x = 850;
	s->slider.start.y = 700;
	s->slider.end.y = 725;
	s->slider.color_two = 0xFF568203;
	s->slider.color_one = 0xFFDB1702;
	s->slider.value = s->player.health;
	draw_slider(s, s->slider);
}
