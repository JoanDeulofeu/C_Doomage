#include "doom.h"

void	display_croix_rouge(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	int			stopi = i + s->savemap->croix_rouge->w;
	int			stopj = j + s->savemap->croix_rouge->h;

	coord.x = 0;
	coord.y = 0;
	while (i < stopi)
	{
		j = 0;
		coord.x = i;
		perx = (double)coord.x / (double)stopi;
		while (j < stopj)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)stopj;
			px = (int)(pery * (double)s->savemap->croix_rouge->h) * s->savemap->croix_rouge->w + (int)
			(perx * (double)s->savemap->croix_rouge->w);
			if (px >= 0 && px < s->savemap->croix_rouge->w * s->savemap->croix_rouge->h)
				set_pixel(s->sdl->save, s->savemap->croix_rouge->tex[px], coord);
		}
		i++;
	}
	// update_image(s, s->sdl->save);
}

void	ft_click_save(t_main *s)
{
	if ((s->ft_mouse.x > 0 && s->ft_mouse.x < s->savemap->croix_rouge->w)
	&& (s->ft_mouse.y > 0 && s->ft_mouse.y < s->savemap->croix_rouge->h))
	{
		s->display_mode = 0;
		change_mode(s, MOVE);
	}
}

void	ft_draw_rect_text(t_main *s)
{
	t_pos		coord;
	int			stopx;
	int			stopy;

	coord.x = 230;
	coord.y = 450;
	stopx = coord.x + 500;
	stopy = coord.y + 40;
	while (coord.y <= stopy)
	{
		while (coord.x <= stopx)
		{
			if ((coord.x == 230 || coord.x == stopx) || (coord.y == 450 || coord.y == stopy))
				set_pixel(s->sdl->save, 0xd23b3bff, coord); //#d23b3b
			else
				set_pixel(s->sdl->save, 0x606060ff, coord); //#606060
			coord.x++;
		}
		coord.y++;
		coord.x = 230;
	}


}

void	ft_add_letter_to_savemap(t_main *s, int key)
{
	int i = 0;

	s->savemap->error_msg = 0;
	while (s->savemap->str[i] != '\0')
	{
		i++;
		if (i == 41)
			return ;
	}
	s->savemap->str[i] = (key == MINUS || key == 32) ? '_' : key;
	// printf("str = %s\n", s->savemap->str);
}

void	ft_del_letter_to_savemap(t_main *s)
{
	int i = 0;

	s->savemap->error_msg = 0;
	if (s->savemap->str[0] == '\0')
		return ;
	while (s->savemap->str[i] != '\0')
		i++;
	s->savemap->str[i - 1] = '\0';
	// printf("str = %s\n", s->savemap->str);
}

void	ft_draw_write_bar(t_main *s)
{
	int		lg;
	t_pos	coord;
	int		x_end;
	int		y_end;

	lg = ft_strlen(s->savemap->str);
	coord.x = 240 + (lg * 10);
	x_end = coord.x + 3;
	coord.y = 457;
	y_end = coord.y + 25;

	while (coord.x++ < x_end)
	{
		while (coord.y++ < y_end)
		{
			set_pixel(s->sdl->save, 0x45d6daff, coord); //#45d6da
		}
		coord.y = 457;
	}
}

void	ft_save_map(t_main *s)
{
	struct timeval	tv;
	double 			mill;
	long			sec;

	gettimeofday(&tv, NULL);

	mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	sec = mill;
	// printf("millisec = %f\nsec = %ld\n", time_in_mill, sec);
	display_croix_rouge(s, 20, 20);
	ft_draw_rect_text(s);
	if (sec % 800 < 400)
		ft_draw_write_bar(s);
}

void	ft_write_file_sprite(t_main *s, FILE *fichier)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	if (!sprite)
		return ;
	while (sprite)
	{
		fprintf(fichier, "Ennemi %d | ", sprite->id);
		fprintf(fichier, "%d | ", (int)sprite->s_angle);
		fprintf(fichier, "%ld ", (long)(sprite->r_ori.x * 100));
		fprintf(fichier, "%ld | ", (long)(sprite->r_ori.y * 100));
		fprintf(fichier, "%d | ", sprite->type);
		fprintf(fichier, "%d\n", sprite->name);
		sprite = sprite->next;
	}
}

void	ft_write_file(t_main *s)
{
	FILE		*fichier = NULL;
	t_vertex	*vtx;
	t_sector	*sct;
	t_int		*wall;
	int			end_id;

	vtx = s->vertex;
	sct = s->sector;
	fichier = fopen(ft_strjoin(s->savemap->str, ".map"), "w+");
	fprintf(fichier, "Map : %s\n\n", s->savemap->str);
	while (vtx)
	{
		fprintf(fichier, "Vertex %d\t\t%d\n", vtx->y, vtx->x);
		vtx = vtx->next;
	}
	fprintf(fichier, "\n\n");
	while (sct)
	{
		wall = sct->vertex;
		fprintf(fichier, "Sector %d %d", sct->floor, sct->ceiling);
		fprintf(fichier, " | ");
		end_id = wall->prev->id;
		while (wall->id != end_id)
		{
			fprintf(fichier, "%d ", wall->value);
			wall = wall->next;
		}
		fprintf(fichier, "%d | ", wall->value);
		wall = wall->next;
		while (wall->id != end_id)
		{
			fprintf(fichier, "%d ", wall->wall_value);
			wall = wall->next;
		}
		fprintf(fichier, "%d\n", wall->wall_value);
		sct = sct->next;
	}
	fprintf(fichier, "\n\n");
	ft_write_file_sprite(s, fichier);
	fprintf(fichier, "\n\n");
	fprintf(fichier, "Player %d %d\n", (int)(s->player.r_pos.y * METRE), (int)(s->player.r_pos.x * METRE));
	fprintf(fichier, "Angle %d\n", (int)s->player.angle);
	fclose(fichier);
	bzero(s->savemap->str, 41);
	ft_save_msg(s, 2);
}

void	ft_save_msg(t_main *s, int error)
{
	if (error == 1)
		s->savemap->error_msg = 1;
	else if (error == 2)
		s->savemap->error_msg = 2;
}
