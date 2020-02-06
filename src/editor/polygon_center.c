/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:48:40 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 17:48:43 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double		ft_find_signed_area(t_sector *sct)
{
	double	somme;
	t_int	*wall;
	int		i;

	wall = sct->vertex;
	i = 0;
	somme = 0.0;
	while (i++ < sct->vertex->prev->id)
	{
		somme += (wall->ptr->m_pos.x * wall->next->ptr->m_pos.y)
		- (wall->next->ptr->m_pos.x * wall->ptr->m_pos.y);
		wall = wall->next;
	}
	return (0.5 * somme);
}

t_pos		ft_find_polygon_center(t_sector *sct)
{
	double	a;
	t_int	*wall;
	int		i;
	t_pos	center;
	t_dpos	somme;

	a = ft_find_signed_area(sct);
	wall = sct->vertex;
	i = 0;
	somme.x = 0.0;
	somme.y = 0.0;
	while (i++ < sct->vertex->prev->id)
	{
		somme.x += (wall->ptr->m_pos.x + wall->next->ptr->m_pos.x)
		* ((wall->ptr->m_pos.x * wall->next->ptr->m_pos.y)
		- (wall->next->ptr->m_pos.x * wall->ptr->m_pos.y));
		somme.y += (wall->ptr->m_pos.y + wall->next->ptr->m_pos.y)
		* ((wall->ptr->m_pos.x * wall->next->ptr->m_pos.y)
		- (wall->next->ptr->m_pos.x * wall->ptr->m_pos.y));
		wall = wall->next;
	}
	center.x = (1 / (6 * a)) * somme.x;
	center.y = (1 / (6 * a)) * somme.y;
	return (center);
}
