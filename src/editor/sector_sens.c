/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_sens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:57:39 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/06 17:57:43 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ft_verify_sens(t_sector *sct, t_4double score)
{
	int	i;
	int	nb_secur;

	i = 0;
	nb_secur = (sct->vertex->prev->id == 3) ? 2 : 3;
	if (score.d1 > 0)
		i++;
	if (score.d2 > 0)
		i++;
	if (score.d3 > 0)
		i++;
	if (score.d4 > 0)
		i++;
	if (i >= nb_secur)
		return (0);
	return (1);
}

int		ft_check_sector_sens(t_sector *sct, int i)
{
	t_pos		center;
	t_4double	score;
	t_int		*wall;

	center = ft_find_polygon_center(sct);
	wall = sct->vertex;
	ft_bzero((void *)(&score), sizeof(t_4double));
	while (i++ < sct->vertex->prev->id)
	{
		score = ft_check_sector_sens2(wall, score, center);
		wall = wall->next;
	}
	return (ft_verify_sens(sct, score));
}
