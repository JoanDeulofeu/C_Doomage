#include "doom.h"

void 		draw_sprites_ori(t_main *s)
{
	// while (s->sprite)
	// {
	//
	// }
}

void 		add_sprite_to_sector(t_main *s, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*tmp;
	t_lsprite	*liste;

	sct = get_sector_by_id(s, sprite->sct_id);
	if ((liste = malloc(sizeof(t_lsprite))) == NULL)
		handle_error(s, MALLOC_ERROR);
	liste->sprite = sprite;
	liste->next = NULL;
	if (sct->liste == NULL)
		sct->liste = liste;
	else
	{
		tmp = sct->liste;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = liste;
	}
}

t_sprite	*create_new_sprite(t_main *s, t_type type, t_dpos pos)
{
	t_sprite	*sprite;
	t_sprite	*temp;

	sprite = NULL;
	if (!(sprite = ft_memalloc(sizeof(t_sprite))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void*)sprite, sizeof(t_sprite));
	sprite->sct_id = ft_is_in_sector(s, ft_dpos_to_pos(pos));
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
		temp->next = sprite;
	}
	add_sprite_to_sector(s, sprite);
	ft_test_chainlist(s);
	return (sprite);
}
