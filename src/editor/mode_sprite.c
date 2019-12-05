#include "doom.h"

void	remove_sprite_from_sector(t_main *s, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*temp;
	t_lsprite	*del;

	sct = get_sector_by_id(s, sprite->sct_id);
	temp = sct->liste;
	// printf("sprite a supprimer = %d\n", sprite->id);
	// printf("secteur du sprite a supprimer = %d\n", sct->id);
	// ft_print_sectors_sprites(s);

	if (!temp)
		return ;
	if (temp->sprite->id == sprite->id)
	{
		sct->liste = temp->next;
		// ft_memdel((void *)temp);
		free(temp);
		temp = NULL;
	}

	else
	{
		while (temp->next->sprite->id != sprite->id)
			temp = temp->next;
		del = temp->next;
		temp->next = temp->next->next;
		free(del);
		del = NULL;
		// ft_memdel((void *)del);
	}

}

void	remove_sprite(t_main *s, int id)
{
	t_sprite	*temp;
	t_sprite	*sprite;

	temp = s->sprite;
	if (temp->id == id)
	{
		s->sprite = temp->next;
		remove_sprite_from_sector(s, temp);
		// ft_memdel((void *)&temp);
		free(temp);
		temp = NULL;
		// s->sprite = NULL;
		return ;
	}
	while (temp->next)
	{
		if (temp->next->id == id)
		{
			sprite = temp->next;
			remove_sprite_from_sector(s, sprite);
			temp->next = sprite->next;
			// ft_memdel((void *)&sprite);
			free(sprite);
			sprite = NULL;
			return ;
		}
		temp = temp->next;
	}
}

void	remove_selected_sprite(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->selected == 1)
		{
			// printf("sprite a supprimer %d\n", sprite->id);
			remove_sprite(s, sprite->id);
			ft_print_sectors_sprites(s);
			return ;
		}
		sprite = sprite->next;
	}
}

void 		draw_sprites_ori(t_main *s)
{
	t_sprite	*tmp;
	t_dpos		pos;

	tmp = s->sprite;
	while (tmp)
	{
		pos.x = tmp->r_ori.x * METRE;
		pos.y = tmp->r_ori.y * METRE;
		draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, pos)), YELLOW);
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
	ft_print_sectors_sprites(s);
}

t_sprite	*create_new_sprite(t_main *s, t_type type, t_dpos r_pos)
{
	t_sprite	*sprite;
	t_sprite	*temp;
	int			sct_id;
	t_dpos		pos;

	sprite = NULL;
	pos = ft_pos_to_dpos(get_px_r_pos(s, r_pos));
	if ((sct_id = ft_is_in_sector(s, ft_dpos_to_pos(pos))) == 0)
		return (NULL);
	if (!(sprite = ft_memalloc(sizeof(t_sprite))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void*)sprite, sizeof(t_sprite));
	sprite->sct_id = ft_is_in_sector(s, ft_dpos_to_pos(pos));
	sprite->r_pos = r_pos;
	sprite->size = 2;
	sprite->pos = ft_dpos_to_pos(pos);
	sprite->r_ori = sprite->r_pos;
	sprite->m_pos.x = sprite->r_pos.x * METRE;
	sprite->m_pos.y = sprite->r_pos.y * METRE;
	sprite->type = type;
	sprite->life = 100;
	sprite->set = 0;
	sprite->anim = s->stormtrooper.face;
	if (!s->sprite)
	{
		s->sprite = sprite;
		s->sprite->id = 1;
		add_sprite_to_sector(s, sprite);
		return (sprite);
	}
	temp = s->sprite;
	while (temp->next)
		temp = temp->next;
	temp->next = sprite;
	sprite->id = temp->id + 1;
	add_sprite_to_sector(s, sprite);
	return (sprite);
}
