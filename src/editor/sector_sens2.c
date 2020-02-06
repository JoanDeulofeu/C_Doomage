/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_sens2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:58:57 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 17:59:00 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_score_se(t_int *wall, double *score_se)
{
	if (wall->ptr->m_pos.x > wall->next->ptr->m_pos.x)
		*score_se += ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
	else if (wall->ptr->m_pos.x < wall->next->ptr->m_pos.x)
		*score_se -= ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
}

void		ft_score_so(t_int *wall, double *score_so)
{
	if (wall->ptr->m_pos.y > wall->next->ptr->m_pos.y)
		*score_so += ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
	else if (wall->ptr->m_pos.y < wall->next->ptr->m_pos.y)
		*score_so -= ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
}

void		ft_score_ne(t_int *wall, double *score_ne)
{
	if (wall->ptr->m_pos.y < wall->next->ptr->m_pos.y)
		*score_ne += ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
	else if (wall->ptr->m_pos.y > wall->next->ptr->m_pos.y)
		*score_ne -= ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
}

void		ft_score_no(t_int *wall, double *score_no)
{
	if (wall->ptr->m_pos.x < wall->next->ptr->m_pos.x)
		*score_no += ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
	else if (wall->ptr->m_pos.x > wall->next->ptr->m_pos.x)
		*score_no -= ft_dist_t_dpos(wall->ptr->m_pos, wall->next->ptr->m_pos);
}

t_4double	ft_check_sector_sens2(t_int *wall, t_4double score, t_pos center)
{
	if (wall->ptr->m_pos.x < center.x)
	{
		if (wall->ptr->m_pos.y < center.y)
			ft_score_no(wall, &score.d1);
		else if (wall->ptr->m_pos.y >= center.y)
			ft_score_so(wall, &score.d3);
	}
	else if (wall->ptr->m_pos.x > center.x)
	{
		if (wall->ptr->m_pos.y <= center.y)
			ft_score_ne(wall, &score.d2);
		else if (wall->ptr->m_pos.y > center.y)
			ft_score_se(wall, &score.d4);
	}
	else if (wall->ptr->m_pos.x == center.x)
	{
		if (wall->ptr->m_pos.y <= center.y)
			ft_score_no(wall, &score.d1);
		else if (wall->ptr->m_pos.y > center.y)
			ft_score_se(wall, &score.d4);
	}
	return (score);
}
