/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:53:39 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 19:53:46 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	*ft_draw_wall(void *void_mt)
{
	t_multithread	*mt;

	mt = (t_multithread *)void_mt;
	while ((mt->avcm_x = mt->i++) <= mt->limit_thread)
	{
		mt->pct_avcm = (100 * (double)mt->i) / (double)mt->width_wall;
		if (mt->l_height_wall < mt->r_height_wall)
			mt->hw = mt->l_height_wall + (mt->diff_wall
				* mt->pct_avcm) * 0.01;
		else if (mt->l_height_wall > mt->r_height_wall)
			mt->hw = mt->l_height_wall - (mt->diff_wall
				* mt->pct_avcm) * 0.01;
		else
			mt->hw = mt->l_height_wall;
		mt->wall_height_tmp = mt->hw;
		mt->dhp = ft_get_diff_height_pxl(mt->s->player.foot_height
			- mt->wall->floor_height + mt->s->player.size,
			mt->wall->ceiling_height, mt->wall->floor_height, mt->hw);
		mt->coord.y = (HEIGHT * 0.5) - (mt->hw) + mt->s->player.y_eye + mt->dhp;
		mt->bottom = (HEIGHT * 0.5) + mt->s->player.y_eye + mt->dhp;
		if (mt->coord.x > 0 && mt->coord.x < WIDTH)
			ft_draw_column(mt->coord, mt->bottom, mt);
		mt->coord.x++;
	}
	pthread_exit(NULL);
}

void	ft_fill_mt(t_multithread *mt, int i, int width_wall)
{
	mt->width_wall = width_wall;
	if (i == 0)
	{
		mt->limit_thread = mt->width_wall * 0.25;
		mt->i = 0;
	}
	else if (i == 1)
	{
		mt->limit_thread = mt->width_wall * 0.5;
		mt->i = mt->width_wall * 0.25;
	}
	else if (i == 2)
	{
		mt->limit_thread = (mt->width_wall * 0.25) * 3;
		mt->i = mt->width_wall * 0.5;
	}
	else if (i == 3)
	{
		mt->limit_thread = mt->width_wall;
		mt->i = (mt->width_wall * 0.25) * 3;
	}
}

void	ft_multi_threading(t_main *s, t_walls *wall, double l_height_wall,
	double r_height_wall)
{
	int				i;
	t_multithread	mt[4];
	pthread_t		thread[4];

	i = -1;
	get_total_w_wall(wall);
	while (++i < 4)
	{
		mt[i].s = s;
		mt[i].wall = wall;
		mt[i].l_height_wall = l_height_wall;
		mt[i].r_height_wall = r_height_wall;
		mt[i].diff_wall = fabs(mt[i].l_height_wall - mt[i].r_height_wall);
		ft_fill_mt(&mt[i], i, wall->screen_width_wall);
		mt[i].coord.x = mt[i].wall->x + mt[i].i;
		if (pthread_create(&thread[i], NULL, ft_draw_wall,
			(void *)(&mt[i])) == -1)
			perror("thread creation");
	}
	i = 0;
	while (i < 4)
		if (pthread_join(thread[i++], NULL) == -1)
			perror("thread join");
}
