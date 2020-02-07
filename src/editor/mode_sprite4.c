/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_sprite4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:53:33 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 13:53:35 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_limit_sprite(t_main *s, int sct_id, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*sct_sprite;
	int			counter;

	sct = get_sector_by_id(s, sct_id);
	if (sct == NULL)
		return (0);
	counter = 0;
	sct_sprite = sct->liste;
	while (sct_sprite)
	{
		if (sct_sprite->sprite->type == sprite->type)
			counter++;
		sct_sprite = sct_sprite->next;
	}
	if (counter >= 5)
		return (0);
	return (1);
}

void	remove_sprite_from_sector(t_main *s, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*temp;
	t_lsprite	*del;

	sct = get_sector_by_id(s, sprite->sct_id);
	if (!sct)
		return ;
	temp = sct->liste;
	if (!temp)
		return ;
	if (temp->sprite->id == sprite->id)
	{
		sct->liste = temp->next;
		ft_memdel((void **)&temp);
	}
	else
	{
		while (temp->next->sprite->id != sprite->id)
			temp = temp->next;
		del = temp->next;
		temp->next = temp->next->next;
		ft_memdel((void **)&del);
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
		ft_memdel((void *)&temp);
		return ;
	}
	while (temp->next)
	{
		if (temp->next->id == id)
		{
			sprite = temp->next;
			remove_sprite_from_sector(s, sprite);
			temp->next = sprite->next;
			ft_memdel((void *)&sprite);
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
			remove_sprite(s, sprite->id);
			deselect_sprite(s);
			return ;
		}
		sprite = sprite->next;
	}
}
