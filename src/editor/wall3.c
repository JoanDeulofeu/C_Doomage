/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:35:19 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/09 15:24:20 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ft_howmany_char(char *str, char c)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			res++;
	}
	return (res);
}

int		ft_nb_is_in_str(char *str, int nb)
{
	int	i;
	int	tmp;
	int	strlg;

	i = 0;
	tmp = 0;
	strlg = ft_strlen(str);
	while (i <= strlg)
	{
		while ((str[i] < 48 || str[i] > 57) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (0);
		tmp = ft_atoi(&str[i]);
		if (tmp == nb)
			return (1);
		i += ft_longlen(tmp) + 1;
	}
	return (0);
}

void	ft_save_sector_vextex(t_main *s, int id_vtx)
{
	char	*tmp;
	char	*space;

	tmp = ft_itoa(id_vtx);
	if (s->str_vtx == NULL)
		s->str_vtx = ft_strdup(tmp);
	else if ((ft_nb_is_in_str(s->str_vtx, id_vtx)) == 0)
	{
		if (!(space = (char*)malloc(sizeof(char) * 2)))
			handle_error(s, MALLOC_ERROR);
		space[0] = ' ';
		space[1] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &space);
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &tmp);
	}
	ft_memdel((void **)&tmp);
}

int		ft_norm_close_sector(t_main *s, int part, char *end)
{
	if (part == 1)
	{
		if (!(end = (char*)malloc(sizeof(char) * 6)))
			handle_error(s, MALLOC_ERROR);
		end[0] = ' ';
		end[1] = '|';
		end[2] = ' ';
		end[3] = '-';
		end[4] = '1';
		end[5] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
	}
	else
	{
		if (!(end = (char*)malloc(sizeof(char) * 4)))
			handle_error(s, MALLOC_ERROR);
		end[0] = ' ';
		end[1] = '-';
		end[2] = '1';
		end[3] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
	}
	return (0);
}

int		ft_norm_close_sector2(t_main *s, int part, char *end)
{
	if (part == 1)
	{
		if (!(end = (char*)malloc(sizeof(char) * 5)))
			handle_error(s, MALLOC_ERROR);
		end[0] = ' ';
		end[1] = '|';
		end[2] = ' ';
		end[3] = '0';
		end[4] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
	}
	else
	{
		if (!(end = (char*)malloc(sizeof(char) * 3)))
			handle_error(s, MALLOC_ERROR);
		end[0] = ' ';
		end[1] = '0';
		end[2] = '\0';
		s->str_vtx = ft_strjoin_free(&s->str_vtx, &end);
	}
	return (0);
}
