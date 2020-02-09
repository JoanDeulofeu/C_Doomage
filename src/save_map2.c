/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <jgehin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:20:50 by jgehin            #+#    #+#             */
/*   Updated: 2020/02/07 20:20:52 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_write_file_sprite(t_main *s, FILE *fichier)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	if (!sprite)
		return ;
	while (sprite)
	{
		fprintf(fichier, "Ennemi %d | ", sprite->type);
		fprintf(fichier, "%ld ", (long)(sprite->r_ori.x * 100));
		fprintf(fichier, "%ld | ", (long)(sprite->r_ori.y * 100));
		fprintf(fichier, "%d | ", (int)sprite->s_angle);
		fprintf(fichier, "%d\n", sprite->name);
		sprite = sprite->next;
	}
}

void	ft_write_file_norm(FILE *fichier, t_sector *sct, t_int *wall, int end)
{
	fprintf(fichier, "Sector %d %d", sct->floor, sct->ceiling);
	fprintf(fichier, " | ");
	end = wall->prev->id;
	while (wall->id != end)
	{
		fprintf(fichier, "%d ", wall->value);
		wall = wall->next;
	}
	fprintf(fichier, "%d | ", wall->value);
	wall = wall->next;
	while (wall->id != end)
	{
		fprintf(fichier, "%d ", wall->wall_value);
		wall = wall->next;
	}
	fprintf(fichier, "%d | ", wall->wall_value);
	wall = wall->next;
	while (wall->id != end)
	{
		fprintf(fichier, "%d ", wall->tex_nb);
		wall = wall->next;
	}
	fprintf(fichier, "%d\n", wall->tex_nb);
}

void	ft_write_file_norm2(t_main *s, FILE *fichier)
{
	fprintf(fichier, "\n\n");
	ft_write_file_sprite(s, fichier);
	fprintf(fichier, "\n\n");
	fprintf(fichier, "Player %d %d\n", (int)(s->player.r_pos.y * METRE),
	(int)(s->player.r_pos.x * METRE));
	fprintf(fichier, "Angle %d\n", (int)s->player.angle);
	fclose(fichier);
	ft_bzero(s->savemap->str, 41);
	ft_save_msg(s, 2);
}

void	ft_write_file(t_main *s)
{
	FILE		*fichier;
	t_vertex	*vtx;
	t_sector	*sct;
	char		*str;

	fichier = NULL;
	vtx = s->vertex;
	sct = s->sector;
	str = ft_strjoin(s->savemap->str, ".map");
	fichier = fopen(str, "w+");
	ft_strdel(&str);
	fprintf(fichier, "Map : %s\n\n", s->savemap->str);
	while (vtx)
	{
		fprintf(fichier, "Vertex %d\t\t%d\n", vtx->y, vtx->x);
		vtx = vtx->next;
	}
	fprintf(fichier, "\n\n");
	while (sct)
	{
		ft_write_file_norm(fichier, sct, sct->vertex, 0);
		sct = sct->next;
	}
	ft_write_file_norm2(s, fichier);
}

void	ft_save_msg(t_main *s, int error)
{
	if (error == 1)
		s->savemap->error_msg = 1;
	else if (error == 2)
		s->savemap->error_msg = 2;
}
