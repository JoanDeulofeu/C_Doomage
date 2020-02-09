/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:21:04 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 20:21:06 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_sprite_hitbox(t_main *s)
{
	t_sprite 	*sprite;
	t_dpos		init1;
	t_dpos		dest1;
	double 		pct;
	double		height;
	double		width;
	double 		diff_height_pxl;
	int			bottom;

	// diff_height_pxl = ft_get_sprite_height_pxl(s, sprite, height);
	// coord.y = (HEIGHT* 0.5) - height + s->player.y_eye + diff_height_pxl;
	// bottom = (HEIGHT* 0.5) + s->player.y_eye + diff_height_pxl;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->set == 1)
		{
			pct = (sprite->r_dist * METRE * 100) / sprite->l_dist;
			height = HEIGHT / ((pct * 0.001) * 4) * sprite->size * HEIGHT_MULT;
			pct = (100 * sprite->anim.image[sprite->current]->w) / sprite->anim.image[sprite->current]->h;
			width = (pct * height)* 0.01;
			diff_height_pxl = ft_get_sprite_height_pxl(s, sprite, height);
			bottom = (HEIGHT* 0.5) + s->player.y_eye + diff_height_pxl;
			init1.y = (HEIGHT* 0.5) - height + s->player.y_eye + diff_height_pxl;
			init1.x = sprite->x - (width * 0.5);
			dest1.y = bottom;
			dest1.x = sprite->x +  (width * 0.5);
			draw_rect(s->sdl->game, init1, dest1, 0x622b2bff);
		}
		sprite = sprite->next;
	}
}

void print_wall_list(t_main *s)
{
  t_walls *tmp;
  int     i;

  tmp = s->walls;
  i = 1;
  while (tmp)
  {
	if (tmp->wall_or_portal == 'p')
	{
		printf("\033[33mPORTAIL\n");
		printf("portail[%d].portal_value = %d\n", i, tmp->portal_value);
	}
	  if (tmp->wall_or_portal == 'w')
	  {
	      printf("\033[0m==========\n");
	      printf("MUR[%d]\n", i);
	      printf("----------\n");
	      printf("mur[%d].nb_tex = %d\n", i, tmp->nb_tex);
	      printf("mur[%d].l_dist = %f\n", i, tmp->l_dist);
	      printf("mur[%d].b_dist = %f\n", i, tmp->b_dist);
	      printf("mur[%d].x = %d\n", i, tmp->x);
	      printf("mur[%d].player.x = %f\n", i, tmp->player.x);
	      printf("mur[%d].player.y = %f\n", i, tmp->player.y);
	      printf("mur[%d].left.x = %f\n", i, tmp->left.x);
	      printf("mur[%d].left.y = %f\n", i, tmp->left.y);
	      printf("mur[%d].right.x = %f\n", i, tmp->right.x);
	      printf("mur[%d].right.y = %f\n", i, tmp->right.y);
	      printf("mur[%d].l_plan.x = %f\n", i, tmp->l_plan.x);
	      printf("mur[%d].l_plan.y = %f\n", i, tmp->l_plan.y);
	      printf("mur[%d].r_plan.x = %f\n", i, tmp->r_plan.x);
	      printf("mur[%d].r_plan.y = %f\n\n", i, tmp->r_plan.y);
	      i++;
	  }

    tmp = tmp->next;
  }
}

void print_player_values(t_main *s)
{
	printf("r_pos = x(%f) y(%f)\n", s->player.r_pos.x, s->player.r_pos.y);
	printf("pos = x(%f) y(%f)\n", s->player.pos.x, s->player.pos.y);
	printf("m_pos = x(%f) y(%f)\n", s->player.m_pos.x, s->player.m_pos.y);
	printf("sector_id = %d\n", s->player.sector_id);
	printf("eyesight = %f\n", s->player.eyesight);
	printf("y_eye = %d\n", s->player.y_eye);
	printf("angle = %f\n", s->player.angle);
}

void	ft_print_sprite_list(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	if (s->sprite == NULL)
		return ;
	while (sprite)
	{
		printf("------SPRITE %d------\n", sprite->id);
		printf("s_angle = %f\n", sprite->s_angle);
		printf("r_ori x(%.2f) y(%.2f)\n", sprite->r_ori.x, sprite->r_ori.y);
		printf("type = %d\n",  sprite->type);
		printf("name = %d\n",  sprite->name);
		printf("life = %d\n",  sprite->life);
		printf("set = %d\n",  sprite->set);
		printf("destroy = %d\n\n",  sprite->destroy);
		sprite = sprite->next;
	}
}

void	ft_print_sectors_sprites(t_main *s)
{
	t_sector	*sct;
	t_lsprite	*liste;

	sct = s->sector;
	if (s->sprite == NULL)
		return ;
	while (sct)
	{
		liste = sct->liste;
		printf("------SECTOR %d------\n", sct->id);
		while (liste)
		{
			if (liste->sprite)
			{
				printf("SPRITE %d\n", liste->sprite->id);
				printf("secteur du sprite = %d\n", liste->sprite->sct_id);
			}

			else
				printf("/!\\sprite free\n");
			liste = liste->next;
		}
		sct = sct->next;
	}
	printf("\n\n");
}

void		ft_test_chainlist(t_main *s)
{
	t_vertex	*v_tmp;
	t_sector	*s_tmp;
	t_int		*i_tmp;
	int			i;
	int 		j;
	t_lsprite	*sp_tmp;

	printf("\n\n\n\033[32m------VERTEX------\033[0m\n");
	v_tmp = s->vertex;
	s_tmp = s->sector;
	if (s->vertex != NULL)
	{
		while (v_tmp->next != NULL)
		{
			printf("Vertex[%d] =   X %d   |   Y %d\n", v_tmp->id, v_tmp->x, v_tmp->y);
			v_tmp = v_tmp->next;
		}
		printf("Vertex[%d] =   X %d   |   Y %d\n\n", v_tmp->id, v_tmp->x, v_tmp->y);
	}

	printf("\033[32m------SECTOR------\033[0m\n");
	if (s->sector != NULL)
	{
		while (s_tmp != NULL)
		{
			j = 0;
			sp_tmp = s_tmp->liste;
			while (sp_tmp)
			{
				j++;
				sp_tmp = sp_tmp->next;
			}
			printf ("\033[31mCe secteur contient %d sprites\n", j);
			printf("\033[36mSector[%d] =  sol %d  |  plafond %d\033[0m\n-------------\n", s_tmp->id, s_tmp->floor, s_tmp->ceiling);
			if (s_tmp->vertex != NULL)
			{
				i = 0;
				i_tmp = s_tmp->vertex;
				while (i < s_tmp->vertex->prev->id)
				{
					printf("--   vertex[%d] = %d\n", i_tmp->id, i_tmp->value);
					printf("--  ptr vertex = %p\n",i_tmp->ptr);
					printf("--  vertex x y = x(%d) y(%d)\n",i_tmp->ptr->x, i_tmp->ptr->y);
					printf("--  vertex pos = x(%d) y(%d)\n",i_tmp->ptr->pos.x, i_tmp->ptr->pos.y);
					printf("--  vertex m_pos = x(%.2f) y(%.2f)\n",i_tmp->ptr->m_pos.x, i_tmp->ptr->m_pos.y);
					if (i_tmp->wall_value != -1)
						printf("\033[33m--     wall[%d] =", i_tmp->id);
					else
						printf("--     wall[%d] =", i_tmp->id);
					printf(" %d \033[0m \n", i_tmp->wall_value);
					printf("--  texture nb = %d \n", i_tmp->tex_nb);
					printf("--  sct actuel = %d\n",i_tmp->sct);
					if (i_tmp->sct_dest != 0)
						printf("--  sector_dest = %d\n",i_tmp->sct_dest);
					i_tmp = i_tmp->next;
					i++;
					printf("-------------\n");
				}
			}
			s_tmp = s_tmp->next;
			printf("\n");
		}
	}
}
