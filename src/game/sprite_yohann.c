#include "doom.h"

void get_sprite_x(t_main *s, t_visu *vs, t_sprite *sprite)
{
	float	per;
	t_dpos	inter;

	per = 0;
	ft_find_intersection(s, vs->left_plan, vs->right_plan,
		vs->player, sprite->m_pos, 1);
	inter = s->tmp_intersect;
	per = ft_dist_t_dpos(vs->player, sprite->m_pos) * 100 / ft_dist_t_dpos(vs->left_plan, vs->right_plan);

	//calculer ratio sur widthplan


}

void 	unset_sprites(t_main *s)
{
	t_sprite *sprite;

	sprite = s->sprite;
	while (sprite)
	{
		sprite->set = 0;
		sprite = sprite->next;
	}
}

void 	set_visible_sprites(t_main *s, t_visu *vs)
{
	t_lsprite 	*liste;
	t_int		*wall;
	int			inter;
	t_dpos		wall1;
	t_dpos		wall2;


	liste = vs->sct->liste;
	if(!liste)
	{
		return ;
	}

	wall = vs->vtx_gauche;
	if (wall == NULL || vs->vtx_droite == NULL)
		return ;
	while (liste)
	{
		inter = 0;
		while (wall->id != vs->vtx_droite->next->id)
		{
			wall1.x = wall->ptr->x * METRE;
			wall1.y = wall->ptr->y * METRE;
			wall2.x = wall->next->ptr->x * METRE;
			wall2.y = wall->next->ptr->y * METRE;
			if (ft_find_intersection(s, wall1, wall2, vs->player, liste->sprite->m_pos, 1))
			{
				// printf("inter\n");
				inter = 1;;
				break;
			}
			wall = wall->next;
		}
		if (inter == 0 && ft_find_intersection(s, vs->left_plan, vs->right_plan,
			vs->player, liste->sprite->m_pos, 1))
		{
			liste->sprite->x = (ft_dist_t_dpos(vs->left_plan, liste->sprite->m_pos) / WIDTHPLAN) * WIDTH;
			liste->sprite->set = 1;
			// printf("sprite set\n");
		}

		else
		{
			liste->sprite->set = 0;
			// printf("nop\n");
		}

		liste = liste->next;
	}
}

void 	display_sprites(t_main *s)
{
	t_sprite *sprite;

	sprite = s->sprite;
	if (!sprite)
		return ;
	while (sprite)
	{
		// printf("boucle\n");
		if (sprite->set == 1 && sprite->destroy == 0)
		{
			// printf("sprite ok\n");
			sprite->r_dist = calc_sprite_r_dist(s, sprite->r_pos);
			draw_sprite(s, sprite->angle, sprite);
		}
		sprite = sprite->next;
	}
}

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
	sprite->set = 0;
	// sprite->next = NULL;
	sprite->anim = s->stormtrooper.face;
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
