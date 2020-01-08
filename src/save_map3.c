#include "doom.h"

void	ft_add_letter_to_savemap(t_main *s, int key)
{
	int i;

	i = 0;
	s->savemap->error_msg = 0;
	while (s->savemap->str[i] != '\0')
	{
		i++;
		if (i == 41)
			return ;
	}
	s->savemap->str[i] = (key == MINUS || key == 32) ? '_' : key;
}

void	ft_del_letter_to_savemap(t_main *s)
{
	int i;

	i = 0;
	s->savemap->error_msg = 0;
	if (s->savemap->str[0] == '\0')
		return ;
	while (s->savemap->str[i] != '\0')
		i++;
	s->savemap->str[i - 1] = '\0';
}
