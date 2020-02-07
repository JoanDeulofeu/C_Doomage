#include "doom.h"

void 	unset_sprites(t_main *s)
{
	t_sprite *sprite;

	if ((sprite = s->sprite) == NULL)
		return ;
	while (sprite)
	{
		sprite->dist = sprite->r_dist * METRE;
		sprite->set = 0;
		sprite->displayed = 0;
		sprite = sprite->next;
	}
}


void 	get_sprite_x(t_main *s, t_visu *vs, t_sprite *sprite)
{
	float		per;
	t_4dpos		pos;

	per = 0;
	pos.pos1 = vs->left_plan;
	pos.pos2 = vs->right_plan;
	pos.pos3 = vs->player;
	pos.pos4 = sprite->m_pos;
	ft_find_intersection(s, pos, 1);
	per = ft_dist_t_dpos(pos.pos1, s->tmp_intersect)
	* 100 / ft_dist_t_dpos(pos.pos1, pos.pos2);
	sprite->x = per * WIDTH / 100;

}

void 	set_visible_sprites2(t_main *s, t_visu *vs, t_lsprite *liste)
{
	liste->sprite->r_dist = ft_dist_t_dpos(vs->player, liste->sprite->m_pos) / METRE;
	liste->sprite->l_dist = ft_dist_t_dpos(vs->player, s->tmp_intersect);
	get_sprite_x(s, vs, liste->sprite);
	liste->sprite->angle = ft_find_angle_portal(&vs->player, &liste->sprite->m_pos, NULL, 1);
	if (liste->sprite->m_pos.y > vs->player.y)
		liste->sprite->angle = 180 + (180 - liste->sprite->angle);
	liste->sprite->angle = (angle_mod(liste->sprite->angle - vs->angle));
	liste->sprite->set = 1;
	liste->sprite->displayed = 1;
}

int		set_visible_sprites3(t_main *s, t_visu *vs, t_int *wall, t_4dpos *pos)
{
	wall = vs->vtx_gauche;
	pos->pos3 = vs->player;
	while (wall->id != vs->vtx_droite->next->id)
	{
		pos->pos1 = wall->ptr->m_pos;
		pos->pos2 = wall->next->ptr->m_pos;
		if (wall->wall_value == -1 && ft_find_intersection(s, *pos, 1))
			return (1);
		wall = wall->next;
	}
	pos->pos1 = vs->left_plan;
	pos->pos2 = vs->right_plan;
	return (0);
}

void 	set_visible_sprites(t_main *s, t_visu *vs, int inter)
{
	t_lsprite 	*liste;
	t_int		*wall;
	t_4dpos		pos;

	liste = vs->sct->liste;
	if(!liste)
		return ;
	wall = vs->vtx_gauche;
	if (wall == NULL || vs->vtx_droite == NULL)
		return ;
	while (liste)
	{
		pos.pos4 = liste->sprite->m_pos;
		inter = set_visible_sprites3(s, vs, wall, &pos);
		if (inter == 0 && ft_find_intersection(s, pos, 1))
			set_visible_sprites2(s, vs, liste);
		else
			liste->sprite->set = 0;
		liste = liste->next;
	}
}
