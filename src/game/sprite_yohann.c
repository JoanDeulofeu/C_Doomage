#include "doom.h"

void	set_sprite(t_main *s)
{
	t_sprite *tmp;

	tmp = s->sprite;
	while (tmp)
	{
		tmp->pos = get_px_r_pos(s, tmp->r_pos);
		tmp->m_pos.x = tmp->r_pos.x * METRE;
		tmp->m_pos.y = tmp->r_pos.y * METRE;
		tmp = tmp->next;
	}
}

void 		draw_sprites_ori(t_main *s)
{
	t_sprite *tmp;

	tmp = s->sprite;
	while (tmp)
	{
		draw_anchor(s, tmp->pos, YELLOW);
		tmp = tmp->next;
	}
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
	int			sct_id;

	sprite = NULL;
	if ((sct_id = ft_is_in_sector(s, ft_dpos_to_pos(pos))) == 0)
		return (NULL);
	if (!(sprite = ft_memalloc(sizeof(t_sprite))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void*)sprite, sizeof(t_sprite));
	sprite->sct_id = ft_is_in_sector(s, ft_dpos_to_pos(pos));
	sprite->pos = ft_dpos_to_pos(pos);
	sprite->r_pos.x = pos.x / s->editor->space - s->editor->decal_x;
	sprite->r_pos.y = pos.y / s->editor->space - s->editor->decal_y;
	sprite->r_ori = sprite->r_pos;
	sprite->m_pos.x = sprite->r_pos.x * METRE;
	sprite->m_pos.y = sprite->r_pos.y * METRE;
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
