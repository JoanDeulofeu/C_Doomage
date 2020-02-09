/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:21:11 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 20:21:13 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_set_time(t_main *s)
{
	ft_bzero((void *)s->time, sizeof(t_timer));
	s->time->time_ms = SDL_GetTicks();
	s->time->tmp_sec_fps = s->time->time_ms * 0.001;
}

void	ft_fps(t_main *s)
{
	int		time;

	time = s->time->time_ms * 0.001;
	if (time == s->time->tmp_sec_fps)
		s->time->count_fps++;
	else
	{
		s->time->tmp_sec_fps = time;
		s->time->fps = s->time->count_fps;
		s->time->count_fps = 0;
	}
}
