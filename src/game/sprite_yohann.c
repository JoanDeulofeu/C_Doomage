#include "doom.h"

t_sprite	*create_new_sprite(t_main *s, t_type type, t_dpos pos)
{
	t_sprite	*sprite;
	t_sprite	*temp;

	sprite = NULL;
	if (!(sprite = ft_memalloc(sizeof(t_sprite))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void*)sprite, sizeof(t_sprite));
	sprite->r_pos = pos;
	sprite->pos = get_px_r_pos(s, pos);
	sprite->type = type;
	sprite->life = 100;
	if (!s->sprite)
		s->sprite = sprite;
	else
	{
		temp = s->sprite;
		while (temp->next)
			temp = temp->next;
	}
	temp->next = sprite;
	return (sprite);
}
